#pragma once

#include "Memory.hpp"

class IEngineClient {
public:
	bool IsInGame()
	{
		return Memory::CallVirtual<32u, bool>(this);
	}

	bool IsConnected()
	{
		return Memory::CallVirtual<33u, bool>(this);
	}
};