#pragma once
#include "../Common.h"
#include "ForegroundWindowManager.h"
class OverlayWindow;
class OverlayManager { ForegroundWindowManager foreground_; OverlayWindow* overlay_=nullptr; public: void SetOverlay(OverlayWindow* o){overlay_=o;} void Toggle(); void Show(); void Hide(bool restore=true); ForegroundWindowManager& Foreground(){return foreground_;} };
