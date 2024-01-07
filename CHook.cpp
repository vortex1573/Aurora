#include "CHook.hpp"

void CHook::Install(void* target, void* detour)
{
	Logger::Debug("Installing hook " + HookName + ".");

	if (MH_CreateHook(target, detour, reinterpret_cast<void**>(Original)) != MH_OK) {
		Logger::Error("Failed to install hook " + HookName + ".");
		throw std::runtime_error("Failed to install hook " + HookName + ".");
	}

	Target = target;
	Logger::Debug("Installed hook " + HookName + ".");
}

void CHook::Uninstall()
{
	Logger::Debug("Uninstalling hook " + HookName + ".");

	if (MH_RemoveHook(Target) != MH_OK) {
		Logger::Error("Failed to uninstall hook " + HookName + ".");
		throw std::runtime_error("Failed to uninstall hook " + HookName + ".");
	}

	Logger::Debug("Uninstalled hook " + HookName + ".");
}