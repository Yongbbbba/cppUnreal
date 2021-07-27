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


int main()
{
	// winsock 초기화 (ws2_32 라이브러리 초기화)
	// 관련 정보가 wsaData에 채워짐
	WSADATA wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) // 초기화 실패
		return 0;

	// ad : Address Family (AF_INET = IPv4, AF_INET6 = IPv6)
	// type: TCP(SOCK_STREAM) vs UDP(SOCK_DGRAM)
	// protocol : 0  (0으로 하면 알아서 골라줌)
	// return : descriptor
	SOCKET listenSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	if (listenSocket == INVALID_SOCKET)
	{
		int32 errCode = ::WSAGetLastError();
		cout << "Socket ErrorCode : " << errCode << endl;
		return 0;
	}

	// 나의 주소는?
	SOCKADDR_IN serverAddr; // IPv4 
	::memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);  // 너가 알아서 해줘
	serverAddr.sin_port = ::htons(7777);

	// 안내원 폰 개통! 식당의 대표 번호
	if (::bind(listenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		int32 errorCode = ::WSAGetLastError();
		cout << "Bind ErrorCode : " << errorCode << endl;
		return 0;
	}

	// 영업 시작!
	if (::listen(listenSocket, 10) == SOCKET_ERROR) // 대기열의 최대 한도
	{
		int32 errCode = ::WSAGetLastError();
		cout << "Listen ErrorCode : " << errCode << endl;
		return 0;
	}

	// ---------------------------------
	while (true)
	{
		SOCKADDR_IN clientAddr; // IPv4
		::memset(&clientAddr, 0, sizeof(clientAddr));
		int32 addrLen = sizeof(clientAddr);
		SOCKET clientSocket = ::accept(listenSocket, (SOCKADDR*)&clientAddr, &addrLen);
		if (clientSocket == INVALID_SOCKET)
		{
			int32 errCode = ::WSAGetLastError();
			cout << "Accept ErrorCode : " << errCode << endl;
			return 0;
		}

		// 손님 입장
		char ipAddress[16];
		::inet_ntop(AF_INET, &clientAddr.sin_addr, ipAddress, sizeof(ipAddress)); // inet_ntop는 빅엔디언 형식의 이진 데이터를 리틀엔디언 형식의 문자열로 바꿔주는 것. inet_ntoa를 확장한 것으로 inet_ntoa를 대체하는 수순.
		cout << "Client Connected! IP = " << ipAddress << endl;

		// TODO
	}

	// ---------------------------------

	

	
	// 윈속 종료
	::WSACleanup();
	
}
