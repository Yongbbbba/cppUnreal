#include "pch.h"
#include <iostream>

#include <winsock2.h>
#include <mswsock.h>
#include <ws2tcpip.h>
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
	SOCKET clientSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == INVALID_SOCKET)
	{
		int32 errCode = ::WSAGetLastError();
		cout << "Socket ErrorCode : " << errCode << endl;
		return 0;
	}

	// 연결할 목적지는? (IP 주소 * port) ->  xx아파트 yy호
	SOCKADDR_IN serverAddr; // IPv4로 만드는 구조체
	::memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	//serverAddr.sin_addr.s_addr = ::inet_addr("127.0.0.1");  // 구식 방법
	::inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
	serverAddr.sin_port = ::htons(7777);  // 80 : HTTP, 일부 번호는 고정되어서 사용되는 경우가 있으니 주의
	// host to network short
	// 엔디언 문제 해결하기 위해서 사용. 네트워크는 빅엔디언 방식을 사용
	// Little_Endian vs Big-Endian
	// ex) 0x12345678 4바이트 정수
	// low [0x78] [0x56] [0x34] [0x12] high  < little, 대부분 little endian 사용
	// low [0x12] [0x34] [0x56] [0x78] high < big

	if (::connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		int32 errCode = ::WSAGetLastError();
		cout << "Connect ErrorCode : " << errCode << endl;
		return 0;
	}

	// -------------------------------------
	// 연결 성공. 이제부터 데이터 송수신 가능
	cout << "Connected To Server!" << endl;
	while (true)
	{
		// TODO
		this_thread::sleep_for(1s);
	}
	//--------------------------------------

	// 소켓 리소스 반환
	::closesocket(clientSocket);

	// 윈속 종료
	::WSACleanup();
}

