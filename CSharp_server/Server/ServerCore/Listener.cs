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
            _listenSocket = new Socket(endPoint.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
            _onAcceptHandler += onAcceptHandler; // accept가 완료되면 이 함수를 실행하도록 등록

            // Bind
            _listenSocket.Bind(endPoint);

            // Listen
            // backlog: 최대 대기수
            _listenSocket.Listen(10);

            SocketAsyncEventArgs args = new SocketAsyncEventArgs();
            // 비동기 이벤트가 완료되면 이벤트 핸들러에 등록한 함수를 실행시켜라.
            args.Completed += new EventHandler<SocketAsyncEventArgs>(OnAcceptCompleted);
            RegisterAccept(args);
        }

        void RegisterAccept(SocketAsyncEventArgs args)
        {
            args.AcceptSocket = null;

            bool pending = _listenSocket.AcceptAsync(args);
            if (pending == false) // pending 없이 바로 완료된 경우
                OnAcceptCompleted(null, args);
            // pending 됐다면 콜백 방식 등을 통해서 완료된 task를 처리해야함
            // 여기서는 이벤트 핸들러에 등록해서 pending된 것이 완료됐을 경우에 처리
        }
        
        // 이 부분에서 스레드풀에서 worker thread 하나 꺼내와서 여기서 작업을 시작한다.
        // 멀티스레드로 동작하기 때문에 공유자원에 대해서 lock 등의 방법으로 동기화해줘야함
        void OnAcceptCompleted(object sender, SocketAsyncEventArgs args)
        {
            if (args.SocketError == SocketError.Success)
            {
                _onAcceptHandler.Invoke(args.AcceptSocket);
            }
            else
            {
                Console.WriteLine(args.SocketError.ToString()); ;
            }

            // 낚시대를 다시 던지기
            RegisterAccept(args);
        }

        // 동기 함수
        public Socket Accept()
        {
            return _listenSocket.Accept();
        }
    }
}
