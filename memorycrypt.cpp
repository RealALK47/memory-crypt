#include <windows.h>
#include <iostream>

using namespace std;

void memcrypt(DWORD start_addr, DWORD mem_size)
{
	__asm
	{
		push eax
		push ecx
		mov ecx, start_addr
		add ecx, mem_size
		mov eax, start_addr

		crypt_loop:
		xor byte ptr ds : [eax], 0x4d
			inc eax
			cmp eax, ecx
		jl crypt_loop;
		
		pop ecx
		pop eax
	}
}

DWORD process_size(DWORD *func, DWORD *stub_func)
{
	DWORD func_size = 0, mem_protect;
	DWORD *func_a = 0, *func_b = 0;

	func_a = (DWORD*)func;
	func_b = (DWORD*)stub_func;

	func_size = (func_a - func_b);
	VirtualProtect(func_a, func_size, PAGE_EXECUTE_READWRITE, &mem_protect);
	return func_size;
}
