using System;
using System.Collections.Generic;
using System.Net.Sockets;
using System.Text;
using System.Threading;

namespace ServerCore
{
    // Receive, Send 구현
    class Session
    {
        Socket _socket;
        int _disconnected = 0;  // 끊겼는지 확인하기 위한 플래그
        object _lock = new object();
        Queue<byte[]> _sendQueue = new Queue<byte[]>();
        List<ArraySegment<byte>> _pendinglist = new List<ArraySegment<byte>>();

        SocketAsyncEventArgs _sendArgs = new SocketAsyncEventArgs();
        SocketAsyncEventArgs _recvArgs = new SocketAsyncEventArgs();

        public void Start(Socket socket)
        {
            _socket = socket;
            _recvArgs.Completed += new EventHandler<SocketAsyncEventArgs>(OnRecvCompleted);
            _recvArgs.SetBuffer(new byte[1024], 0, 1024);
            _sendArgs.Completed += new EventHandler<SocketAsyncEventArgs>(OnSendCompleted);


            RegisterRecv();
        }

        // 하나가 send를 하고 있으면 다른 놈은 못하게 lock을 해줘야한다.
        public void Send(byte[] sendBuff)
        {
            lock (_lock)
            {
                _sendQueue.Enqueue(sendBuff);
                if (_pendinglist.Count == 0)  // 대기중인 애가 하나도 없다.
                    RegisterSend();
            }
        }

        public void Disconnect()
        {
            if (Interlocked.Exchange(ref _disconnected, 1) == 1)
                return;

            // 쫓아낸다 
            _socket.Shutdown(SocketShutdown.Both);
            _socket.Close();

        }

        #region 네크워크 통신

        // send와 recv는 동작하는 방식이 달라진다. send는 언제 보낼지 시점이 정해지지가 않음 
        void RegisterSend()
        {
            while (_sendQueue.Count > 0 )
            {
                byte[] buff = _sendQueue.Dequeue();
                // ArraySegment를 사용하면 새로 배열을 만들지 않으면서 버퍼의 특정 데이터를 참조할 수 있음
                _pendinglist.Add(new ArraySegment<byte>(buff, 0, buff.Length));
            }

            _sendArgs.BufferList = _pendinglist;

            bool pending = _socket.SendAsync(_sendArgs);
            if (pending == false)
            {
                OnSendCompleted(null, _sendArgs);
            }
        }

        void OnSendCompleted(object sender, SocketAsyncEventArgs args)
        {
            lock (_lock)
            {
                if (args.BytesTransferred > 0 && args.SocketError == SocketError.Success)
                {
                    try
                    {
                        _sendArgs.BufferList = null;  // 사실 굳이 넣어줄 필요는 없음. 방어코드?
                        _pendinglist.Clear();

                        Console.WriteLine($"Transferred  bytes: {_sendArgs.BytesTransferred}");

                        // 내가 보내는 동안에 누가 큐에 넣었을 수도 있으니까 다시 확인해보기
                        if (_sendQueue.Count > 0)
                        {
                            RegisterSend();
                        }
                    }
                    catch (Exception e)
                    {
                        Console.WriteLine($"OnSendCompleted Failed {e}");
                    }
                }
                // 에러나면 연결 끊어버리기
                else
                {
                    Disconnect();
                }
            }
        }

        void RegisterRecv()
        {
            bool pending = _socket.ReceiveAsync(_recvArgs);
            if (pending == false)
                OnRecvCompleted(null, _recvArgs);
        }

        void OnRecvCompleted(object sender, SocketAsyncEventArgs args)
        {
            if (args.BytesTransferred > 0 && args.SocketError == SocketError.Success)
            {
                // TODO
                try
                {
                    string recvData = Encoding.UTF8.GetString(args.Buffer, args.Offset, args.BytesTransferred);
                    Console.WriteLine($"[From Client] {recvData}");

                    RegisterRecv();

                }
                catch (Exception e)
                {
                    Console.WriteLine($"OnRecvCompleted Failed {e}");
                }
            }
            else
            {
                Disconnect();
            }
        }
    }
}

#endregion