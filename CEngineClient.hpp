#pragma once

#include "Memory.hpp"

class CEngineClient {
public:
	int GetMaxClients()
	{
		return Memory::CallVirtual<int>(this, 31u);
	}

	bool IsInGame()
	{
		return Memory::CallVirtual<bool>(this, 32u);
	}

	bool IsConnected()
	{
		return Memory::CallVirtual<bool>(this, 33u);
	}

	int GetLocalPlayer()
	{
		return Memory::CallVirtual<int>(this, 44u);
	}

	void GetScreenSize(int* width, int* height)
	{
		Memory::CallVirtual(this, 50u, &width, &height);
	}

	const char* GetLevelName()
	{
		return Memory::CallVirtual<const char*>(this, 53u);
	}

	const char* GetLevelNameShort()
	{
		return Memory::CallVirtual<const char*>(this, 54u);
	}

	const char* GetProductVersionString()
	{
		return Memory::CallVirtual<const char*>(this, 77u);
	}
};