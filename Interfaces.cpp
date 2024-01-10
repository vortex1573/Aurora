#include "Interfaces.hpp"

void Interfaces::Initialize()
{
	Logger::Info("Initializing interfaces.");

	Engine = reinterpret_cast<CEngineClient*>(GetInterface("engine2.dll", "Source2EngineToClient001"));
}

CInterfaceRegistry* Interfaces::GetInterfaceRegistry(const std::string& moduleName, uintptr_t* createInterface)
{
	CInterfaceRegistry* interfaceRegistry = *reinterpret_cast<CInterfaceRegistry**>(Memory::ResolveRelativeAddress(createInterface, 0x3, 0x7));

	if (!interfaceRegistry) {
		Logger::Error("Failed to get interface list for module '" + moduleName + "'.");
		throw std::runtime_error("Failed to get interface list for module '" + moduleName + "'.");
	}

	return interfaceRegistry;
}

uintptr_t* Interfaces::GetInterface(const std::string& moduleName, const std::string& interfaceName)
{
	uintptr_t* ret = nullptr;
	const HMODULE moduleHandle = Memory::GetBaseModuleHandle(moduleName);
	uintptr_t* createInterface = reinterpret_cast<uintptr_t*>(GetProcAddress(moduleHandle, "CreateInterface"));

	if (!createInterface) {
		Logger::Error("Failed to get 'CreateInterface' for module '" + moduleName + "'.");
		throw std::runtime_error("Failed to get 'CreateInterface' for module '" + moduleName + "'.");
	}

	CInterfaceRegistry* interfaceRegistry = GetInterfaceRegistry(moduleName, createInterface);

	for (CInterfaceRegistry* registry = interfaceRegistry; registry != nullptr; registry = registry->Next)
	{
		if (FNV::Hash(interfaceName) == FNV::Hash(registry->Name)) {
			Logger::Debug("Found interface " + moduleName + "->" + registry->Name + ".");
			ret = static_cast<uintptr_t*>(registry->Callback());
			break;
		}
	}

	if (!ret) {
		Logger::Error("Failed to get interface " + moduleName + "->" + interfaceName + " from module '" + moduleName + "'.");
		throw std::runtime_error("Failed to get interface " + moduleName + "->" + interfaceName + " from module '" + moduleName + "'.");
	}

	return ret;
}