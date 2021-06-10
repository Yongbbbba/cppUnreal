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
