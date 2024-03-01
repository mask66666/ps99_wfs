#include <iostream>
#include <windows.h>
#include <array>

std::array<int, 3> get_rgb(int x, int y) {
    HWND hwndD = GetDesktopWindow();
    HDC hdcD = GetDC(hwndD);

    COLORREF color = GetPixel(hdcD, x, y);
}


int main() {
    std::cout << "Hello Wrold" << std::endl; // testing and setup
}