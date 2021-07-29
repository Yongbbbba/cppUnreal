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

const int32 BUFSIZE = 1000;

// 클라가 서버에 접속하게 되면 session이라는 구조체를 통해 정보를 관리
// 동접자 수만큼 세션이 생겨나게 된다. 각각의 클라이언트를 관리하게 된다.
struct Session
{
	SOCKET socket = INVALID_SOCKET;
	char recvBuffer[BUFSIZE] = {};
	int32 recvBytes = 0; 
	int32 sendBytes = 0;
};

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
	 
	// Select 모델 = (select 함수가 핵심이 되는)
	// 소켓 함수 호출이 성공할 시점을 미리 알 수 있다!
	// 문제 상황)
	// 수신 버퍼에 데이터가 없는데,  read 한다거나! 
	// 송신버퍼가 꽉 찼는데, write 한다거나!
	// 다시 말해서 send할 준비가 안됐는데 send를 계속 해서 루프를 돌면서 호출하는 상황은 비효율적
	// - 블로킹 소켓: 조건이 만족되지 않아서 블로킹되는 상황 예방
	// - 논블로킹 소켓: 조건이 만족되지 않아서 불필요하게 반복 체크하는 상황을 예방

	// socket set
	// 1) 읽기[1 2 3] 쓰기[ ] 예외(OOB)[ ] 관찰 대상 목록
	// OutOfBand는 send() 마지막 인자 MSG_OOB로 보내는 특별한 데이터
	// 받는 쪽에서도 recv OOB 세팅을 해야 해당 데이터를 읽을 수 있음
	// 2) select(readSet, writeSet, excpetSet); -> 관찰시작. 준비가 된 소켓의 갯수를 반환
	// 3) 적어도 하나의 소켓이 준비되면 리턴 -> 낙오자는 알아서 제거됨, 그 다음에 작업을 진행하면 불필요한 반복체크를 안해도됨
	// 4) 남은 소켓 체크해서 진행

	// fd_set read; 
	// 	FD_ZERO: 비운다
	// ex) FD_ZERO(set);
	// FD_SET: set에 소켓 s를 넣는다 
	// ex) FD_SET(s, &set);
	// FD_CLR:  소켓 s를 제거
	// ex FD_CLR(s, &set);
	// FD_ISSET: 소켓 s가 set에 들어있으면 0이 아닌 값을 리턴
	
	vector<Session> sessions;
	sessions.reserve(100);

	// 관찰대상 소켓 셋 만들기(read, write)
	fd_set reads;
	fd_set writes;


	while (true)
	{
		// 소켓 셋 초기화
		FD_ZERO(&reads);
		FD_ZERO(&writes);

		// ListenSocket 등록
		FD_SET(listenSocket, &reads);

		// 소켓 등록
		for (Session& s : sessions)
		{
			// 에코서버니까 보내기 전에 일단 받은 데이터가 있어야함. 그래서 이 경우에는 read
			if (s.recvBytes <= s.sendBytes)
				FD_SET(s.socket, &reads);
			else
				FD_SET(s.socket, &writes);
		}

		// [옵션] 마지막 timeout 인자 설정가능
		/*timeval timeout;
		timeout.tv_sec;
		timeout.tv_usec*/
		int32 retVal = ::select(0, &reads, &writes, nullptr, nullptr);
		if (retVal == SOCKET_ERROR)
			break;

		// Listener 소켓 체크
		if (FD_ISSET(listenSocket, &reads))
		{
			// accpet할 준비가 되었다.
			SOCKADDR_IN clientAddr;
			int32 addrLen = sizeof(clientAddr);
			SOCKET clientSocket = ::accept(listenSocket, (SOCKADDR*)&clientAddr, &addrLen);
			if (clientSocket != INVALID_SOCKET)
			{
				cout << "Client Connected" << endl;
				sessions.push_back(Session{ clientSocket });
			}
		}

		// 나머지 소켓 체크
		for (Session& s : sessions)
		{
			if (FD_ISSET(s.socket, &reads))
			{
				int32 recvLen = ::recv(s.socket, s.recvBuffer, BUFSIZE, 0);
				if (recvLen <= 0)
				{
					// TODO: sessions 제거
					continue;
				}

				s.recvBytes = recvLen;
			}

			// write 체크
			if (FD_ISSET(s.socket, &writes)) // 송신버퍼에 여유 공간이 있어서 송신할 수 있는 상태이다.
			{
				// 블로킹 모드 -> 모든 데이터 다 보냄
				// 논블로킹 모드 -> 일부만 보낼 수 있음 (상대방 수신 버퍼 상황에 따라). 공식문서에서 이렇게 되어있기는 한데 이런 상황이 테스트해보면 거의 발생하지는 않음
				int32 sendLen = ::send(s.socket, &s.recvBuffer[s.sendBytes], s.recvBytes - s.sendBytes, 0);
				if (sendLen == SOCKET_ERROR)
				{
					// TODO: sessions 제거
					continue;
				}
				s.sendBytes += sendLen; // 일부 데이터만 보내졌을 수 있음을 위해 방어 코드 작성

				// 모든 데이터를 다 보냄
				if (s.recvBytes == s.sendBytes)
				{
					s.recvBytes = 0;
					s.sendBytes = 0;
				}
			}
		}
		
	}



	// 윈속 종료
	::WSACleanup();
}
