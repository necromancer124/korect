#pragma once
#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <commdlg.h>
#include <richedit.h>
#include <shellapi.h>
#include <shlwapi.h>
#include <winhttp.h>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <mutex>
#include <thread>
#include <future>
#include <atomic>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <regex>
#include <chrono>
#include <functional>
#include <iomanip>
#include <cwctype>
#include <cstdlib>
inline std::wstring Widen(const std::string& s){ if(s.empty()) return L""; int n=MultiByteToWideChar(CP_UTF8,0,s.data(),(int)s.size(),nullptr,0); std::wstring w(n,0); MultiByteToWideChar(CP_UTF8,0,s.data(),(int)s.size(),w.data(),n); return w; }
inline std::string Narrow(const std::wstring& w){ if(w.empty()) return ""; int n=WideCharToMultiByte(CP_UTF8,0,w.data(),(int)w.size(),nullptr,0,nullptr,nullptr); std::string s(n,0); WideCharToMultiByte(CP_UTF8,0,w.data(),(int)w.size(),s.data(),n,nullptr,nullptr); return s; }
inline std::wstring AppDir(){ wchar_t path[MAX_PATH]; GetModuleFileNameW(nullptr,path,MAX_PATH); PathRemoveFileSpecW(path); return path; }
inline std::wstring UserConfigDir(){ wchar_t* appdata=nullptr; size_t len=0; _wdupenv_s(&appdata,&len,L"APPDATA"); std::wstring p = appdata ? appdata : AppDir(); if(appdata) free(appdata); p += L"\\korect"; CreateDirectoryW(p.c_str(),nullptr); return p; }
inline std::wstring ReadAllText(const std::wstring& path){ std::ifstream f(Narrow(path), std::ios::binary); if(!f) return L""; std::stringstream ss; ss<<f.rdbuf(); return Widen(ss.str()); }
inline void WriteAllText(const std::wstring& path,const std::wstring& text){ std::ofstream f(Narrow(path), std::ios::binary); auto s=Narrow(text); f.write(s.data(), (std::streamsize)s.size()); }
inline std::wstring Trim(std::wstring s){ while(!s.empty() && iswspace(s.front())) s.erase(s.begin()); while(!s.empty() && iswspace(s.back())) s.pop_back(); return s; }
inline std::wstring Lower(std::wstring s){ std::transform(s.begin(),s.end(),s.begin(),[](wchar_t c){return (wchar_t)towlower(c);}); return s; }
inline bool StartsWith(const std::wstring& s,const std::wstring& p){ return s.rfind(p,0)==0; }
inline COLORREF ParseColor(std::wstring hex, COLORREF fallback){ if(hex.size()==7 && hex[0]==L'#'){ unsigned int r,g,b; if(swscanf(hex.c_str()+1,L"%02x%02x%02x",&r,&g,&b)==3) return RGB(r,g,b);} return fallback; }
