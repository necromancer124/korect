#pragma once
#include "../Common.h"
#include "../Configuration/SettingsManager.h"
class OptionsWindow {
public:
    OptionsWindow(SettingsManager& sm);
    bool Create(HWND owner);
    void Show();
    HWND Hwnd() const { return hwnd_; }
private:
    SettingsManager& sm_;
    HWND hwnd_=nullptr, list_=nullptr, panel_=nullptr;
    int category_=0;
    std::vector<std::wstring> cats_;
    static LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
    static LRESULT CALLBACK PanelProc(HWND,UINT,WPARAM,LPARAM);
    LRESULT Proc(UINT,WPARAM,LPARAM);
    void ApplyCurrentControls();
    void BuildCategory();
    HWND AddCheck(const std::wstring&, bool&, int y);
    HWND AddEdit(const std::wstring&, std::wstring&, int y);
    HWND AddInt(const std::wstring&, int&, int y);
    void SaveAndRefresh();
    void ResetCategory();
    bool ChooseFile(bool save, std::wstring& out, const wchar_t* filter);
};
