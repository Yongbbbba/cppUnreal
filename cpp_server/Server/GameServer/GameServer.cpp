#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <Windows.h>
#include <future>
#include "ThreadManager.h"

#include <WinSock2.h>
#include <mswsock.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

void HandleError(const char* cause)
{
	int32 errCode = ::WSAGetLastError();
	cout << cause << " ErrorCode : " << errCode << endl;
}

int main()
{
	WSAData wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 0;

	// 블로킹(Blocking)
	//	   accept -> 접속한 클라가 있을 때
	// 	   connect -> 서버 접속 성공했을 때 
	// 	   send, sedto -> 요청한 데이터를 송신 버퍼에 복사했을 때
	// 	   recv, recvfrom  -> 수신 버퍼에 도착한 데이터가 있고, 이를 유저레벨 버퍼에 복사했을 때
	// 
	// 논블로킹(Non-Blocking)

	SOCKET listenSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	if (listenSocket == INVALID_SOCKET)
		return 0;

	u_long on = 1;
	if (::ioctlsocket(listenSocket, FIONBIO, &on) == INVALID_SOCKET)  // 논블로킹소켓 옵션 설정
		return 0;

	SOCKADDR_IN serverAddr;
	::memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = ::htonl(INADDR_ANY);
	serverAddr.sin_port = ::htons(7777);

	if (::bind(listenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
		return 0;

	if (::listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)  // maximum queue length
		return 0;

	cout << "Listen" << endl;
	 
	SOCKADDR_IN clientAddr;
	int32 addrLen = sizeof(clientAddr);


	// 논블록 소켓에서 아래와 같은 식으로 무한루프를 돌면서 무한루프를 돌면서 WSAEWOURLDBLOCK인 경우 체크를 하는 것은 CPU를 낭비하는 비효율적인 상황이다.




	// Accept
	while (true)
	{
		SOCKET clientSocket = ::accept(listenSocket, (SOCKADDR*)&clientAddr, &addrLen);
		if (clientSocket == INVALID_SOCKET)  
		// 앞선 예제에서 블록킹 소켓에서는 여기서 그냥 프로그램을 종료시키는 방법을 사용했지만 
		// 논블록킹 소켓에서는 INVALID_SOCKET이 떴다고 해서 반드시 문제가 되는 것은 아님
		{
			// 원래 블록했어야 했는데... 너가 논블로킹으로 하라며?
			if (::WSAGetLastError() == WSAEWOULDBLOCK)
				continue;

			// Error
			break;
		}
		cout << "Client Connected!" << endl;

		// Recv
		while (true)
		{
			char recvBuffer[1000];
			int32 recvLen = ::recv(clientSocket, recvBuffer, sizeof(recvBuffer), 0);
			if (recvLen == SOCKET_ERROR)
			{
				// 원래 블록했어야 했는데.. 너가 논블로킹으로 하라며? 
				if (::WSAGetLastError() == WSAEWOULDBLOCK)
					continue;

				// Error
				break;
			}
			else if (recvLen == 0)
			{
				// 연결 끊김
				break;
			}

			cout << "Recv Data Len = " << recvLen << endl;

			// 에코 서버
			// Send 
			while (true)
			{
				if (::send(clientSocket, recvBuffer, recvLen, 0) == SOCKET_ERROR)
				{
					// 원래 블록했어야 했는데.. 너가 논블로킹으로 하라며? 
					if (::WSAGetLastError() == WSAEWOULDBLOCK)
						continue;

					// ERROR
					break;
				}
				cout << "Send Data ! Len = " << recvLen << endl;
				break;
			}
		}
		
	}

	// 윈속 종료
	::WSACleanup();
}
