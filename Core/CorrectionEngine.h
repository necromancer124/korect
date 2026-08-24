#pragma once
#include "../Common.h"
#include "../Configuration/SettingsManager.h"
enum class IssueType { Spelling, Grammar, Punctuation };
struct CorrectionIssue { long start=0, length=0; IssueType type=IssueType::Spelling; std::wstring message; std::vector<std::wstring> suggestions; std::wstring original; };
class CorrectionEngine {
public:
    CorrectionEngine(SettingsManager& settings);
    std::vector<CorrectionIssue> Check(const std::wstring& text);
    void ReloadPersonalDictionary();
    bool LanguageToolAvailable() const { return ltAvailable_; }
private:
    SettingsManager& settings_; std::set<std::wstring> words_; std::set<std::wstring> personal_; std::mutex cacheMutex_; std::unordered_map<std::wstring,std::vector<CorrectionIssue>> cache_; bool ltAvailable_=false; std::chrono::steady_clock::time_point nextLanguageToolProbe_{};
    void LoadDictionary(); bool TryLanguageTool(const std::wstring& text,std::vector<CorrectionIssue>& out); std::vector<std::wstring> Suggest(const std::wstring& word,int max); bool IgnoredWord(const std::wstring& word); int Distance(const std::wstring&a,const std::wstring&b);
};
