#include "Menu.hpp"

void Menu::Initialize()
{
	ImGui::CreateContext();
}

void Menu::Shutdown()
{
	if (!ImGui::GetCurrentContext())
		return;

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void Menu::Render()
{
	ImGui::BeginMainMenuBar(); {
		if (ImGui::MenuItem("Misc", nullptr, false, false))
			MiscMenu();
		if (ImGui::MenuItem("Skins", nullptr, false, false))
			SkinsMenu();
		if (ImGui::MenuItem("Settings", nullptr, false, false))
			SettingsMenu();
	}; ImGui::EndMainMenuBar();
}

// Misc features/Skin changer
void Menu::MiscMenu()
{
}

// /Skin changer
void Menu::SkinsMenu()
{
}

// Configs/UI Settings/Cheat Settings
void Menu::SettingsMenu()
{
}