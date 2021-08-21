using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace ServerCore
{
    class Program
    {
        static void Main(string[] args)
        {
            // DNS (Domain Name System)
            string host = Dns.GetHostName();
            IPHostEntry ipHost = Dns.GetHostEntry(host);
            IPAddress ipAddr = ipHost.AddressList[0];
            IPEndPoint endPoint = new IPEndPoint(ipAddr, 7777);

            // ListenSocket 
            Socket listenSocket = new Socket(endPoint.AddressFamily, SocketType.Stream, ProtocolType.Tcp);

           

            try
            {
                // Bind
                listenSocket.Bind(endPoint);

                // Listen
                // backlog: 최대 대기수
                listenSocket.Listen(10);

                while (true)
                {
                    Console.WriteLine("Listeniing...");

                    // Accept
                    Socket clientSocket = listenSocket.Accept();

                    // Recv
                    byte[] recvBuff = new byte[1024];
                    int recvBytes = clientSocket.Receive(recvBuff);  // 몇 바이트 받아왔는지 return
                    string recvData = Encoding.UTF8.GetString(recvBuff, 0, recvBytes);  // 버퍼의 데이터를 문자열로 받기
                    Console.WriteLine($"[From Client] {recvData}");

                    // Send
                    byte[] sendBuff = Encoding.UTF8.GetBytes("Welcome to MMORPG Server!");
                    clientSocket.Send(sendBuff);

                    // Close
                    clientSocket.Shutdown(SocketShutdown.Both);
                    clientSocket.Close();
                }
            }
            catch(Exception e)
            {
                Console.WriteLine(e.ToString());
            }
           
        }
    }
}
