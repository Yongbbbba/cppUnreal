#pragma once

/* ---------------------
		Crash 
-----------------------*/

// analysis_assume
// crash가 nullptr이 아니라고 가정을 해라.
// 컴파일러를 속이는 것
// 인위적인 크래쉬를 내고 싶을 때.
#define CRASH(cause)						\
{											\
	uint32* crash = nullptr;				\
	__analysis_assume(crash != nullptr);	\
	*crash = 0xDEADBEEF;					\
}

// 조건부 크래쉬
#define ASSERT_CRASH(expr)					\
{											\
	if (!(expr))							\
	{										\
		CRASH("ASSERT_CRASH");				\
		__analysis_assume(expr);			\
	}										\
}