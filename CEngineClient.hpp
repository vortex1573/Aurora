#pragma once

#include "Memory.hpp"

class CEngineClient {
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