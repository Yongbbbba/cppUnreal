﻿using System;
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

            SocketAsyncEventArgs args = new SocketAsyncEventArgs();  // 한 번 만들어두면 재사용
            args.Completed += new EventHandler<SocketAsyncEventArgs>(OnAcceptCompleted);
            RegisterAccept(args);
        }

        void RegisterAccept(SocketAsyncEventArgs args)
        {
            args.AcceptSocket = null;

            bool pending = _listenSocket.AcceptAsync(args);
            // 비동기 방식의 경우 패킷이 오건말건 일단 리턴을 한다.
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

            RegisterAccept(args);
        }

        public Socket Accept()
        {
            return _listenSocket.Accept();
        }
    }
}