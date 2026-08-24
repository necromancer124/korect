#pragma once
#include "../Common.h"
#include "../Configuration/SettingsManager.h"
#include "../Core/CorrectionEngine.h"
#include "OptionsWindow.h"
class OverlayManager;
class OverlayWindow { public: OverlayWindow(SettingsManager&, CorrectionEngine&, OverlayManager&); bool Create(); void Show(); void Hide(); bool Visible()const{return visible_;} HWND Hwnd()const{return hwnd_;} std::wstring Text() const; void ApplyIssues(const std::vector<CorrectionIssue>& issues); private: SettingsManager& sm_; CorrectionEngine& engine_; OverlayManager& manager_; OptionsWindow options_; HWND hwnd_=nullptr, edit_=nullptr, copy_=nullptr, copyClose_=nullptr, clear_=nullptr, settings_=nullptr; bool visible_=false; std::vector<CorrectionIssue> issues_; std::future<std::vector<CorrectionIssue>> future_; std::mutex issueMutex_; HMENU context_=nullptr; int contextIssue_=-1; static constexpr UINT WM_CORRECTION_DONE=WM_APP+11; static LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM); LRESULT Proc(UINT,WPARAM,LPARAM); void Layout(); void ScheduleCheck(); void StartCheck(); void Copy(bool close); void Clear(); void ReplaceIssue(int idx,const std::wstring& sug); int IssueAtPoint(POINT p); void ShowContextMenu(POINT p); void PaintBackground(HDC hdc); };
