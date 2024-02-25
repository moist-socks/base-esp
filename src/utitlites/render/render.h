#pragma once
#include <Windows.h>

void DrawRectangle(HDC hdc, int left, int top, int right, int bottom, BOOL filled, COLORREF color);
void DrawLine(HDC hdc, int startX, int startY, int endX, int endY, COLORREF color);
void DrawCircle(HDC hdc, int centerX, int centerY, int radius, BOOL filled, COLORREF color);
void FrameEllipse(HDC hdc, int left, int top, int right, int bottom, int borderWidth, COLORREF color);