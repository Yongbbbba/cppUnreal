#pragma once
#include "Allocator.h"

template<typename Type, typename... Args>
Type* xnew(Args&&... args)
{
	Type* memory = static_cast<Type*>(xalloc(sizeof(Type)));

	// placement new
	// rvalue 참조의 경우 move, universal 참조의 경우 forward 사용
	new(memory)Type(std::forward<Args>(args)...);
	return memory;
}

template<typename Type>
void xdelete(Type* obj)
{
	obj->~Type();
	xrelease(obj);
	
}