#pragma once

/*-------------
	IocpObject 
--------------*/

class IocpObject
{
public:
	virtual HANDLE GetHandle() abstract;
	virtual void Dispatch(class IocpEvent* iocpEvent, int32 numOfBytes = 0) abstract;
};

/*----------------------
		IocpCore
------------------------*/

class IocpCore
{
public:
	IocpCore();
	~IocpCore();

	HANDLE GetHandle() { return _iocpHandle; }

	bool Register(class IocpObject* iocpObject);
	bool Dispatch(uint32 timeoutMs = INFINITE);  // 워커 스레드들이 IOCP 큐를 확인

private:
	HANDLE _iocpHandle;
};

// TEMP
extern IocpCore GIocpCore;