#pragma once
#include "../Common.h"
struct HotkeySetting { UINT modifiers = MOD_CONTROL | MOD_SHIFT | MOD_NOREPEAT; UINT vk = VK_SPACE; };
struct AppSettings {
    HotkeySetting openHotkey;
    bool startWithWindows=false, startMinimized=true, alwaysOnTop=true, closeWithEscape=true, closeOnOutside=false;
    bool autoCloseAfterCopy=false, openAnimation=true, closeAnimation=true;
    int overlayWidth=560, overlayHeight=320, overlayX=-1, overlayY=-1; std::wstring overlayPosition=L"Center";
    std::wstring theme=L"Dark", accent=L"#67E8F9", textColor=L"#E5E7EB", fontFamily=L"Segoe UI", interfaceSize=L"Normal";
    int opacity=238, fontSize=16, uiScale=100, borderRadius=18;
    bool showButtons=true, showTitleBar=true;
    bool spelling=true, grammar=true, punctuation=true, autoLanguage=true, autoBest=false, autoCorrect=false;
    bool ignoreAllCaps=true, ignoreNumbers=true, ignoreUrls=true, ignoreUsernames=true, ignoreTechTerms=true;
    std::wstring defaultLanguage=L"en-US"; int correctionDelayMs=300, suggestionCount=5, maxTextLength=12000;
    bool offlineOnly=true, allowOnline=false, cache=true, engineInBackground=true, startEngineWithWindows=false, keepEngineLoaded=true, reduceCpu=true;
    std::vector<std::wstring> personalDictionary;
};
class SettingsManager {
public:
    SettingsManager(); AppSettings& Settings(){return settings_;} const AppSettings& Settings() const {return settings_;}
    bool Load(); bool Save(); void ResetAll(); bool ImportFrom(const std::wstring& path); bool ExportTo(const std::wstring& path);
    void AddDictionaryWord(const std::wstring& word); void RemoveDictionaryWord(const std::wstring& word); std::wstring ConfigPath() const {return configPath_;}
private:
    AppSettings settings_; std::wstring configPath_; std::wstring Serialize() const; void Parse(const std::wstring& text);
};
