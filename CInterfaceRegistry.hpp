#pragma once

using InterfaceCallback = void* (*)();

class CInterfaceRegistry {
public:
	InterfaceCallback Callback;
	const char* Name;
	CInterfaceRegistry* Next;
};