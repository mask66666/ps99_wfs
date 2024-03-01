#include <iostream>
#include <windows.h>
#include <array>

// gets color of specific pixel and returns RGB
std::array<int, 3> get_rgb(int x, int y) {
    HWND hwndD = GetDesktopWindow();
    HDC hdcD = GetDC(hwndD);

    // gets color
    COLORREF color = GetPixel(hdcD, x, y);

    // makes it in to 3 elements r g b
    int red = GetRValue(color);
    int green = GetGValue(color);
    int blue = GetBValue(color);

    // packs it in to array and releases DC then returns array
    std::array return_arr = { red, green, blue };
    ReleaseDC(hwndD, hdcD);
    return return_arr;
}

void click() {
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

void get_pos(int& x, int& y) {
    POINT curP;
    if (GetCursorPos(&curP)) {
        x = curP.x;
        y = curP.y;
    }
}


int main() {
    std::array<int, 3> color = get_rgb(100, 200);
    for (int i = 0; i < 3; i++) {
        std::cout << color[i] << std::endl;
    }
    return 0;
}