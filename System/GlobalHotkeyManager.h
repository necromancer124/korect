#pragma once
#include "../Common.h"
#include "../Configuration/SettingsManager.h"
class GlobalHotkeyManager { HWND hwnd_=nullptr; int id_=1; public: bool Register(HWND hwnd,const HotkeySetting& h,std::wstring& error); void Unregister(); };
