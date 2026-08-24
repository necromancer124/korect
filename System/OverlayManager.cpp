#include "OverlayManager.h"
#include "../UI/OverlayWindow.h"
void OverlayManager::Toggle(){ if(overlay_ && overlay_->Visible()) Hide(true); else Show(); }
void OverlayManager::Show(){ foreground_.Capture(); if(overlay_) overlay_->Show(); }
void OverlayManager::Hide(bool restore){ if(overlay_) overlay_->Hide(); if(restore) foreground_.Restore(); }
