#pragma once

/* ---------------------
		Crash 
-----------------------*/

// analysis_assume
// crash�� nullptr�� �ƴ϶�� ������ �ض�.
// �����Ϸ��� ���̴� ��
// �������� ũ������ ���� ���� ��.
#define CRASH(cause)						\
{											\
	uint32* crash = nullptr;				\
	__analysis_assume(crash != nullptr);	\
	*crash = 0xDEADBEEF;					\
}

// ���Ǻ� ũ����
#define ASSERT_CRASH(expr)					\
{											\
	if (!(expr))							\
	{										\
		CRASH("ASSERT_CRASH");				\
		__analysis_assume(expr);			\
	}										\
}