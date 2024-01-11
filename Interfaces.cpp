#include "Interfaces.hpp"

void Interfaces::Initialize()
{
	Logger::Info("Initializing interfaces.");

	Engine = reinterpret_cast<CEngineClient*>(GetInterface("engine2.dll", "Source2EngineToClient001"));
}

uint8_t* Interfaces::GetCreateInterface(const std::string& moduleName)
{
	const HMODULE moduleHandle = Memory::GetBaseModuleHandle(moduleName);
	uint8_t* createInterface = reinterpret_cast<uint8_t*>(GetProcAddress(moduleHandle, "CreateInterface"));

	if (!createInterface)
		Utility::Error("Failed to get 'CreateInterface' for module '" + moduleName + "'.");

	return createInterface;
}

CInterfaceRegistry* Interfaces::GetInterfaceRegistry(const std::string& moduleName)
{
	uint8_t* createInterface = GetCreateInterface(moduleName);
	CInterfaceRegistry* interfaceRegistry = *reinterpret_cast<CInterfaceRegistry**>(Memory::ResolveRelativeAddress(createInterface, 0x3, 0x7));

	if (!interfaceRegistry)
		Utility::Error("Failed to get interface list for module '" + moduleName + "'.");

	return interfaceRegistry;
}

uintptr_t* Interfaces::GetInterface(const std::string& moduleName, const std::string& interfaceName)
{
	uintptr_t* ret = nullptr;
	CInterfaceRegistry* interfaceRegistry = GetInterfaceRegistry(moduleName);

	for (CInterfaceRegistry* registry = interfaceRegistry; registry != nullptr; registry = registry->Next)
	{
		if (FNV::Hash(interfaceName) == FNV::Hash(registry->Name)) {
			Logger::Debug("Found interface " + moduleName + "->" + registry->Name + ".");
			ret = static_cast<uintptr_t*>(registry->Callback());
			break;
		}
	}

	if (!ret)
		Utility::Error("Failed to get interface " + moduleName + "->" + interfaceName + " from module '" + moduleName + "'.");

	return ret;
}