# Listener

저번에 만든 서버 코드 부분을 리팩토링 : Listener 부분을 재작성 (<u>이해도가 떨어져서 비동기 방식, 콜백 등에 대해 공부하고 다시 강의를 볼 것</u>)



## 논블록킹 서버의 필요성

기존 서버코어의 코드를 보면

```c#
Socket clientSocket = _listeners.Accept();
```

이 부분이 있다. 그리고 이 이후로 메세지를 보내거나 받는 부분이 있는데, 만약 블록킹 서버라면 연결이 되기 전에는 위 코드의 이후 코드가 동작하지 않는다. return이 있을 때까지 기다리기 때문이다. 그래서 만약 싱글 스레드라면 연결이 있을 때까지 계속 메인 스레드가 일을 쉬는 것 같은 양상이 벌어진다. 그래서 채팅 서버의 경우에 논블록킹 방식으로 구현해줘야할 필요성이 있다. 즉, 연결이 되거나 말거나 일단 return 시켜서 다른 작업을 수행하게 하는 것이다.



## 논블록킹 서버 구현 

논블록킹 상황에서는 소켓이 Listen을 했을 때 패킷이 있건말건 일단 return을 하게 된다. 

```c#
bool pending = _listenSocket.AcceptAsync(args);
```

return 값이 false라는 것은 패킷을 받아서 pending할 필요가 없는 상항, 즉 더 기다릴 필요는 없는 상황이다.

만약 pending 상태라면 나중에 그 함수가 성공적으로 처리가 되는지(상대 패킷이 도달했는지) 확인을 해야하는데 크게 두 가지 방법으로 수행할 수 있다.

1. polling : 주기적으로 우리가 직접 체크
2. event : 이벤트가 발생하면 처음에 걸어놓은 콜백함수가 알아서 호출돼서 처리



### Client

```c#
using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace DummyClient
{
    class Program
    {
        static void Main(string[] args)
        {
            // DNS(Domain Name System)
            string host = Dns.GetHostName();
            IPHostEntry ipHost = Dns.GetHostEntry(host);
            // 구글과 같은 큰 서비스의 경우에는 하나의 Domain name에 대응하는 여러 개의 IP Address가 있을 수 있다.
            IPAddress ipAddr = ipHost.AddressList[0];
            // 엔드포인트 객체를 만들어서 초기화한다. (IP와 Port Number를 mapping)
            IPEndPoint endPoint = new IPEndPoint(ipAddr, 7777);

            while (true)
            {
                // 휴대폰 설정
                Socket socket = new Socket(endPoint.AddressFamily, SocketType.Stream, ProtocolType.Tcp);

                try
                {
                    // 문지기한테 입장 문의
                    socket.Connect(endPoint);
                    Console.WriteLine($"Connected To {socket.RemoteEndPoint.ToString()}");

                    // 보낸다
                    byte[] sendBuff = Encoding.UTF8.GetBytes("Hello World!");
                    int sendBytes = socket.Send(sendBuff);

                    // 받는다
                    byte[] recvBuff = new byte[1024];
                    int recvBytes = socket.Receive(recvBuff);
                    string recvData = Encoding.UTF8.GetString(recvBuff, 0, recvBytes);
                    Console.WriteLine($"[From server] {recvData}");

                    // 나간다
                    socket.Shutdown(SocketShutdown.Both);
                    socket.Close();
                }
                catch (Exception e)
                {
                    Console.WriteLine(e.ToString());
                }

                Thread.Sleep(100);
            }

            
        }
    }
}

```



### Listener

```c#
using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Text;

namespace ServerCore
{
    class Listener
    {
        Socket _listenSocket;
        Action<Socket> _onAcceptHandler;

        public void Init(IPEndPoint endPoint, Action<Socket> onAcceptHandler)
        {
            // 문지기 
            _listenSocket = new Socket(endPoint.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
            _onAcceptHandler += onAcceptHandler;
            // 문지기 교육
            _listenSocket.Bind(endPoint);

            // 영업 시작
            // backlog : 최대 대기수
            _listenSocket.Listen(10);

            // 비동기 작업을 완료하는데 사용되는 이벤트 핸들러 초기화
            SocketAsyncEventArgs args = new SocketAsyncEventArgs();  // 한 번 만들어두면 재사용, 비동기 소켓 작업에 이용
            args.Completed += new EventHandler<SocketAsyncEventArgs>(OnAcceptCompleted);  // 비동기 작업이 완료가 되면 OnAcceptCompleted라는 콜백함수를 실행하도록 이벤트 핸들러에 등록
            RegisterAccept(args);
        }

        void RegisterAccept(SocketAsyncEventArgs args)
        {
            args.AcceptSocket = null;

            bool pending = _listenSocket.AcceptAsync(args);
            // 당장 accept를 완료할 것이라는 보장은 없다.
            // 비동기 방식의 경우 패킷이 오건말건 일단 리턴을 한다. 그리고 원하는 작업이 완료가 되면 콜백 방식을 통해 알려준다.
            // 그런데 return 값이 false라는 것은 패킷을 받아서 pending할 필요가 없는 상항, 즉 더 기다릴 필요는 없는 상황
            if (pending == false)
            {
                OnAcceptCompleted(null, args);
            }
            // 만약 pending 상태라면 나중에 그 함수가 성공적으로 처리가 되는지 확인할 필요가 잆음
            // 크게 두 방식 (1. polling : 주기적으로 우리가 직접 체크, 2: 이벤트 방식(처음에 걸어놓은 콜백함수가 알아서 호출되는 것)
        }

        void OnAcceptCompleted(object sender, SocketAsyncEventArgs args)
        {
            if (args.SocketError == SocketError.Success)
            {
                _onAcceptHandler.Invoke(args.AcceptSocket);
            }
            else
                Console.WriteLine(args.SocketError.ToString());

            // 다음 아이를 위해서 또 한 번 등록을 하는 개념
            RegisterAccept(args);
        }

        public Socket Accept()
        {
            return _listenSocket.Accept();
        }
    }
}

```

### servercore : program

```c#
 using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace ServerCore
{

    class Program
    {
        static Listener _listener = new Listener();

        static void OnAcceptHandler(Socket clientSocket)
        {
            try
            {
                // 받는다 
                byte[] recvBuff = new byte[1024];
                // 몇 바이트 받았는지 리턴
                int recvBytes = clientSocket.Receive(recvBuff);
                string recvData = Encoding.UTF8.GetString(recvBuff, 0, recvBytes);
                Console.WriteLine($"[From Client] {recvData}");

                // 보낸다 
                byte[] sendBuff = Encoding.UTF8.GetBytes("Welcome to MMORPG Server!");
                clientSocket.Send(sendBuff);

                // 쫓아낸다 
                clientSocket.Shutdown(SocketShutdown.Both);
                clientSocket.Close();
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
            }
           
        }
        
        static void Main(string[] args)
        {
            // DNS(Domain Name System)
            string host = Dns.GetHostName();
            IPHostEntry ipHost = Dns.GetHostEntry(host);
            // 구글과 같은 큰 서비스의 경우에는 하나의 Domain name에 대응하는 여러 개의 IP Address가 있을 수 있다.
            IPAddress ipAddr = ipHost.AddressList[0]; 
            // 엔드포인트 객체를 만들어서 초기화한다. (IP와 Port Number를 mapping)
            IPEndPoint endPoint = new IPEndPoint(ipAddr, 7777);
  
            _listener.Init(endPoint, OnAcceptHandler);
               
            while (true)
            {
                // _listener.Init(endPoint, OnAcceptHandler); 이 코드 때문에 어차피 계속 루프를 도는 모양새가 되지만 프로그램 종료를 막기 위하여 무한루프문을 놔둔다.
            }

        }
    }
}

```

