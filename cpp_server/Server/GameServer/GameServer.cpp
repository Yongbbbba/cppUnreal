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
	WSAOVERLAPPED overlapped = {};
};

void CALLBACK RecvCallback(DWORD error, DWORD recvLen, LPWSAOVERLAPPED overlapped, DWORD flags)
{
	cout << "Data Recv Len Callback = " << recvLen << endl;
	// TODO : 만약 에코 서버를 만든다면 WSASend()
	
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

	cout << "Accept" << endl;

	// Overlapped IO (비동기 + 논블로킹)
	// -Overlapped 함수를 건다 (WSARecv, WSASend)
	// -Overlapped 함수가 성공헀는지 확인 후,
	// -> 성공했으면 결과 얻어서 처리
	// -> 실패했으면 사유를 확인

	// 완료 통지를 크게 두 가지 방식으로 확인할 수 있는데
	// 이벤트 방식과 콜백 방식이 있다.

	// WSASend
	// WSARecv
	// AcceptEx
	// ConnectEx
	

	/*char sendBuffer[100];
	WSABUF wsaBuf;
	wsaBuf.buf = sendBuffer;
	wsaBuf.len = 100;*/

	// WSASend
	// WSARecv
	// 	   파라미터 
	// 1) 비동기 입출력 소켓
	// 2) WSABUF 배열의 시작 주소 + 개수 // Scatter-Gather 기법
	// 3) 보내고/받은 바이트 수
	// 4) 상세 옵션인데 0
	// 5) WSAOVERLAPPED 구조체 주소값
	// 6) 입출력이 완료되면 OS가 호출할 콜백 함수


	// Overlapped 모델 (Completion Routine 콜백 기반)
	// - 비동기 입출력 지원하는 소켓 생성 
	// - 비동기 입출력 함수 호출(완료 루틴의 시작 주소를 넘겨준다)
	// - 비동기 작업이 바로 완료되지 않으면, WSA_IO_PENDING 오류 코드
	// - 비동기 입출력 함수 호출한 쓰레드를 -> Alertable Wait 상태로 만든다.
	// 	   ex) WaitForSingleObjectEx, WaitForMultipleObjectsEx, SleepEx, WSAWaitForMultipleEvents
	// - 비동기 IO 완료되면, 운영체제는 완료 루틴 호출
	// - 완료 루틴 호출이 모두 끝나면, 쓰레드는 Alertable Wait 상태에서 빠져나온다.
	// - WSAWaitForMultipleEvents 함수 호출해서 이벤트 객체의 singal 판별
	// - WSAGetOverlappedResult 호출해서 비동기 입출력 결과 확인 및 데이터 처리

	// 1) 오류 발생시 0 아닌 값
	// 2) 전송 바이트 수
	// 3) 비동기 입출력 함 수 호출시 넘겨준 WSAOVERLAPPED 구조체의 주소값
	// 4) 0
	
	// void CompletionRoutine()

	// Select 모델
	// 	   장점) 윈도우/리눅스 공통.
	// 	   단점) 성능 최하(매번 소켓 등록 비용 발생). 64개 제한. 늘려줄라면 스레드를 늘려야함.
	// WSAAsyncSelect 모델 = 소켓 이벤트를 윈도우 메시지 형태로 처리. (일반 윈도우 메시지랑 소켓에서 오가는 메시지를 같이 처리하니 성능 문제가 있다..)
	// WSAEventSelect 모델
	// 	   장점) 비교적 뛰어난 성능. 클라이언트에서 사용하기 좋음. 서버는 당연히 IOCP.. 끝판왕..
	// 	   단점) 64개 제한
	// Overlapped(이벤트 기반)
	// 	   장점) 성능
	// 	   단점 ) 64개 제한
	// Overlapped(콜백 기반)
	//	   장점) 성능. 성능이 좋으면 왜 IOCP까지 넘어가야하는가?
	// 	   단점) 모든 비동기 소켓 함수에서 사용 가능하진 않음 (accept). 콜백 함수를 인자로 넣어줄 수 없는 함수가 존재
	// 	   단점) 빈번한 Alertable Wait으로 인한 성능 저하
	// IOCP
	// Reactor Pattern (~뒤늦게) 논블로킹 소켓. 소켓 상태 확인 후 -> 뒤늣게 recv send 호출
	// Proactor Pattern (~미리) Overlapped WSA~를 이용해서 일단 미리 호출.

	while (true)
	{
		SOCKADDR_IN clientAddr;
		int32 addrLen = sizeof(clientAddr);

		SOCKET clientSocket;
	
		while (true)
		{
			clientSocket = ::accept(listenSocket, (SOCKADDR*)&clientAddr, &addrLen);
			if (clientSocket != INVALID_SOCKET)
				break;
			if (::WSAGetLastError() == WSAEWOULDBLOCK)
				continue;

			// 문제 있는 상황
			return 0;
		}

		Session session = Session{ clientSocket };
		WSAEVENT wsaEvent = ::WSACreateEvent();

		cout << "Client Connected !" << endl;

		while (true)
		{
			WSABUF wsaBuf;
			wsaBuf.buf = session.recvBuffer;
			wsaBuf.len = BUFSIZE;
			DWORD recvLen = 0;
			DWORD flags = 0;
			if (::WSARecv(clientSocket, &wsaBuf, 1, &recvLen, &flags, &session.overlapped, RecvCallback) == SOCKET_ERROR)
			{
				if (::WSAGetLastError() == WSA_IO_PENDING)
				{
					// Pending
					// Alertable Wait
					::SleepEx(INFINITE, TRUE);  // 비동기 recv를 APC 큐에 넣어놨다가 준비가 되면 콜백 함수를 실행해준다.
					// ::WSAWaitForMultipleEvents(1, &wsaEvent, TRUE, WSA_INFINITE, TRUE); // 마지막 인자를 true로 해주면 alertable_wait 상태로 넘어가게 된다. 
				}
				else
				{
					// TODO: 문제있는 상황
					break;
				}
			}
			else
			{
				cout << "Data Recv Len = " << recvLen << endl;
			}

		}
		::closesocket(session.socket);
		//::WSACloseEvent(wsaEvent);
	}

	// 윈속 종료
	::WSACleanup();
}
