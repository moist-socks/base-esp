#include "render.h"

// Function to draw a rectangle
void DrawRectangle(HDC hdc, int left, int top, int right, int bottom, BOOL filled, COLORREF color) {
    HBRUSH hBrush = CreateSolidBrush(color);
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

    RECT rect = { left, top, right, bottom };

    if (filled) {
        Rectangle(hdc, left, top, right, bottom);
    }
    else {
        FrameRect(hdc, &rect, hBrush);
    }

    SelectObject(hdc, hOldBrush);
    DeleteObject(hBrush);
}

// Function to draw a framed ellipse (outline)
void FrameEllipse(HDC hdc, int left, int top, int right, int bottom, int borderWidth, COLORREF color) {
    HPEN hPen = CreatePen(PS_SOLID, borderWidth, color);
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

    Arc(hdc, left, top, right, bottom, 0, 0, 0, 0);

    SelectObject(hdc, hOldPen);
    DeleteObject(hPen);
}

// Function to draw a circle
void DrawCircle(HDC hdc, int centerX, int centerY, int radius, BOOL filled, COLORREF color) {
    HBRUSH hBrush = CreateSolidBrush(color);
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

    if (filled) {
        Ellipse(hdc, centerX - radius, centerY - radius, centerX + radius, centerY + radius);
    }
    else {
        FrameEllipse(hdc, centerX - radius, centerY - radius, centerX + radius, centerY + radius, 1, color);
    }

    SelectObject(hdc, hOldBrush);
    DeleteObject(hBrush);
}

// Function to draw a line
void DrawLine(HDC hdc, int startX, int startY, int endX, int endY, COLORREF color) {
    HPEN hPen = CreatePen(PS_SOLID, 1, color);
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

    MoveToEx(hdc, startX, startY, NULL);
    LineTo(hdc, endX, endY);

    SelectObject(hdc, hOldPen);
    DeleteObject(hPen);
}
