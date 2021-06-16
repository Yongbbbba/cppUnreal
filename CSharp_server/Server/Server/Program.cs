using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using ServerCore;

namespace Server
{
    class GameSession : Session
    {
        public override void OnConnected(EndPoint endPoint)
        {
            Console.WriteLine($"OnConnected: {endPoint}");

            byte[] sendBuff = Encoding.UTF8.GetBytes("Welcome to MMORPG Server !");
            Send(sendBuff);
            Thread.Sleep(1000);
            Disconnect();

        }

        public override void OnDisconnected(EndPoint endPoint)
        {
            Console.WriteLine($"OnDisconnected: {endPoint}");
        }

        public override void OnRecv(ArraySegment<byte> buffer)
        {
            string recvData = Encoding.UTF8.GetString(buffer.Array, buffer.Offset, buffer.Count);
            Console.WriteLine($"[From Client] {recvData}");
        }

        public override void OnSend(int numOfBytes)
        {
            Console.WriteLine($"Transferred  bytes: {numOfBytes}");

        }
    }

    class Program
    {
        static Listener _listener = new Listener();

        static void Main(string[] args)
        {
            // DNS(Domain Name System)
            string host = Dns.GetHostName();
            IPHostEntry ipHost = Dns.GetHostEntry(host);
            // 구글과 같은 큰 서비스의 경우에는 하나의 Domain name에 대응하는 여러 개의 IP Address가 있을 수 있다.
            IPAddress ipAddr = ipHost.AddressList[0];
            // 엔드포인트 객체를 만들어서 초기화한다. (IP와 Port Number를 mapping)
            IPEndPoint endPoint = new IPEndPoint(ipAddr, 7777);

            _listener.Init(endPoint, () => { return new GameSession(); });

            while (true)
            {
                // _listener.Init(endPoint, OnAcceptHandler); 이 코드 때문에 어차피 계속 루프를 도는 모양새가 되지만 프로그램 종료를 막기 위하여 무한루프문을 놔둔다.
            }

        }
    }
}
