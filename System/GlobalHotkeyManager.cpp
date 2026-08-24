#include "GlobalHotkeyManager.h"
bool GlobalHotkeyManager::Register(HWND hwnd,const HotkeySetting& h,std::wstring& error){ Unregister(); hwnd_=hwnd; if(!RegisterHotKey(hwnd_,id_,h.modifiers,h.vk)){ error=L"Global hotkey is already registered by another application. Open Options > Hotkeys and choose another shortcut."; return false;} return true; }
void GlobalHotkeyManager::Unregister(){ if(hwnd_) UnregisterHotKey(hwnd_,id_); hwnd_=nullptr; }
