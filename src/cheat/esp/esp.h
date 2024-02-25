// esp.h
#pragma once

#include <Windows.h>
#include "../../utitlites/render/render.h"

// Function declarations for ESP calculations and rendering
void CalculateESP(HWND overlayWindow);  // You can modify the parameters based on your needs
void RenderESP(HDC hdc, HWND overlayWindow);
