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
};

enum IO_TYPE
{
	READ,
	WRITE,
	ACCEPT,
	CONNECT,
};

struct OverlappedEx
{
	WSAOVERLAPPED overlapped = {};
	int32 type = 0; // read, write, accept, connect ... 
};

void WorkerThreadMain(HANDLE iocpHandle)
{
	// cp 핸들을 받아서 완료된 일감이 있는지 체크
	while (true)
	{
		DWORD bytesTransferred = 0;  // 송수신된 데이터의 크기를 확인
		Session* session = nullptr;
		OverlappedEx* overlappedEx = nullptr;

		// 완료된 일감이 있는지 체크. 계속 체크한다고 해서 성능에 부하가 생기는 것은 아님.
		// timeout option을 줄 수 있음.
		// 멀티스레드 환경에서 race condition이 발생할 수 있기 때문에 여기에 lock을 잡아야하는건가 생각할 수 있는데 그럴 필요없다. 내부적으로 처리해줌.
		BOOL ret = ::GetQueuedCompletionStatus(iocpHandle, &bytesTransferred,  
		/*Key*/(ULONG_PTR*)&session, (LPOVERLAPPED*)&overlappedEx, INFINITE);

		if (ret == FALSE || bytesTransferred == 0)
		{
			// TODO: 연결 끊김
			continue;
		}

		ASSERT_CRASH(overlappedEx->type == IO_TYPE::READ);
		cout << "Recv Data IOCP = " << bytesTransferred << endl;

		WSABUF wsaBuf;
		wsaBuf.buf = session->recvBuffer;
		wsaBuf.len = BUFSIZE;

		DWORD recvLen = 0;
		DWORD flags = 0;

		::WSARecv(session->socket, &wsaBuf, 1, &recvLen, &flags, &overlappedEx->overlapped, NULL);
	}
}

int main()
{
	WSAData wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 0;

	SOCKET listenSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	if (listenSocket == INVALID_SOCKET)
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

	// Overlapped 모델 (completion Routine 콜백 기반)
	// - 비동기 입출력 함수 완료되면, 쓰레드마다 있는 APC 큐에 일감이 쌓임.
	// - Alertable Wait 상태로 들어가서 APC 큐를 비우기 (콜백 함수 실행)
	// 단점) APC큐게 쓰레드마다 고유하게 있게 된다. 멀티스레드 환경에서 적절하게 배분하는 문제가 생김.
	// 단점) Alertable Wait 자체도 조금 부담.
	// 단점) 이벤트 방식 소켓: 이벤트 1:1 대응

	// IOCP (completion Port) 모델
	// - APC 대신 Completion Port 사용 (스레드마다 있는건 아니고 1개. 중앙에서 관리하는 APC 큐의 느낌)
	// - Alertable Wait -> CP 결과 처리를 GetQueuedCompletionStatus 사용
	// 쓰레드랑 궁합이 굉장히 좋다. 그래서 멀티스레드 환경에서 사용을 많이 한다.

	// CreateIoCompletionPort -> CP를 만들고, 소켓을 여기에 등록하는 과정을 한 번에 해주는게 이 함수.
	// GetQueuedCompletionStatus

	vector<Session*> sessionManager;

	// CP 생성
	HANDLE iocpHandle = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);

	// WorkerThreads
	// CP를 관찰하면서 입출력 완료된 함수가 있는지 확인.
	for (int32 i = 0; i < 5; i++)
		GThreadManager->Launch([=]() {WorkerThreadMain(iocpHandle); });

	// Main Thread = Accept 담당
	while (true)
	{
		SOCKADDR_IN clientAddr;
		int32 addrLen = sizeof(clientAddr);

		SOCKET clientSocket = ::accept(listenSocket, (SOCKADDR*)&clientAddr, &addrLen);
		if (clientSocket == INVALID_SOCKET)
			return 0;

		Session* session = new Session();
		session->socket = clientSocket;
		sessionManager.push_back(session);

		cout << "Client Connected !" << endl;

		// 소켓을 CP에 등록
		::CreateIoCompletionPort((HANDLE)clientSocket, iocpHandle, /*Key*/(ULONG_PTR)session, 0);  // 마지막 인자에 0을 넣어주면 최대 코어 개수만큼 할당. 물론 스레드 생성을 자동으로 해주는거는 아님.

		WSABUF wsaBuf;
		wsaBuf.buf = session->recvBuffer;
		wsaBuf.len = BUFSIZE;

		OverlappedEx* overlappedEx = new OverlappedEx();
		overlappedEx->type = IO_TYPE::READ;

		// ADD_REF 필요
		DWORD recvLen = 0;
		DWORD flags = 0;

		::WSARecv(clientSocket, &wsaBuf, 1, &recvLen, &flags, &overlappedEx->overlapped, NULL);

		// 만약 클라에서 연결이 끊겼다면? 유저가 게임 종료? 세션 없애줘야하지 않을까?
		//Session* s = sessionManager.back();
		//sessionManager.pop_back();
		//delete s;
	}

	GThreadManager->Join();

	// 윈속 종료
	::WSACleanup();
}
