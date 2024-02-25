#include <Windows.h>
#include "utitlites/render/render.h"
#include "utitlites/utitlies.h"
#include "cheat/esp/esp.h"

RECT clientRect;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE:
        // Set up a timer to periodically check and update the overlay
        SetTimer(hwnd, 1, 1000 / 60, NULL);  // Set to approximately 60 fps
        break;
    case WM_TIMER:
        // Update the overlay when the timer fires
        UpdateOverlay(hwnd);
        break;
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // Clear the overlay by filling the entire window with a color (e.g., black)
        RECT clientRect;
        GetClientRect(hwnd, &clientRect);
        HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));  // Black color
        FillRect(hdc, &clientRect, hBrush);
        DeleteObject(hBrush);

        // Render text "ZENITH" at specific x and y coordinates
        const wchar_t* text = L"ZENITH";

        // Set the background mode to transparent
        SetBkMode(hdc, TRANSPARENT);

        // Set text color to white
        SetTextColor(hdc, RGB(255, 255, 255));  // White color

        // Use a larger font
        HFONT hFont = CreateFont(30, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
            CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Impact");
        HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);

        // Specify x and y coordinates for drawing the text
        int x = clientRect.left + 20;  // Adjust as needed
        int y = clientRect.bottom - 50;  // Adjust as needed

        // Draw the text at the specified coordinates
        TextOut(hdc, x, y, text, wcslen(text));

        // Your ESP calculations and rendering
        CalculateESP(hwnd);
        RenderESP(hdc, hwnd);;

        // Restore the original fonts
        SelectObject(hdc, hOldFont);
        DeleteObject(hFont);

        EndPaint(hwnd, &ps);
        break;
    }
    case WM_DESTROY:
        // Clean up resources and exit
        KillTimer(hwnd, 1);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int main() {
    // Create a transparent overlay window
    WNDCLASS windowClass = {};
    windowClass.lpfnWndProc = WindowProc;
    windowClass.hInstance = GetModuleHandle(NULL);
    windowClass.lpszClassName = L"OverlayWindowClass";
    RegisterClass(&windowClass);

    HWND overlayWindow = CreateWindowEx(
        WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOPMOST,
        windowClass.lpszClassName,
        L"Overlay Window",
        WS_POPUP,
        0, 0, 0, 0,  // Initial size and position, will be updated in UpdateOverlay
        NULL, NULL, GetModuleHandle(NULL), NULL
    );

    // Set the overlay window as transparent
    SetLayeredWindowAttributes(overlayWindow, RGB(0, 0, 0), 0, LWA_COLORKEY);

    // Make the overlay window visible
    ShowWindow(overlayWindow, SW_SHOWNORMAL);
    UpdateWindow(overlayWindow);

    // Main message loop
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
