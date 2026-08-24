#pragma once
#include "../Common.h"
class ForegroundWindowManager { HWND previous_=nullptr; public: void Capture(){ previous_=GetForegroundWindow(); } HWND Previous()const{return previous_;} void Restore(){ if(previous_&&IsWindow(previous_)){ ShowWindow(previous_,SW_SHOW); SetForegroundWindow(previous_); }} };
