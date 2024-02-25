#pragma once

#include <Windows.h>

// Function to update the overlay window
void UpdateOverlay(HWND overlayWindow) {
    HWND targetWindow = GetForegroundWindow();
    RECT targetRect;
    GetWindowRect(targetWindow, &targetRect);
    SetWindowPos(overlayWindow, NULL, targetRect.left, targetRect.top,
        targetRect.right - targetRect.left, targetRect.bottom - targetRect.top, SWP_NOZORDER | SWP_NOREDRAW);
    RedrawWindow(overlayWindow, NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_FRAME | RDW_ALLCHILDREN);
    // Optionally, add additional rendering logic here based on the target window
}

// Additional utility functions can be added here
