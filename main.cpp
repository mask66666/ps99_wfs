#include <iostream>
#include <windows.h>
#include <thread>
#include <array>
#include <chrono>
#include <fstream>

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

bool compeare_color(std::array<int, 3> color1, std::array<int, 3> color2, int tolerance) {
    return (abs(color1[0] - color2[0]) <= tolerance &&
            abs(color1[1] - color2[1]) <= tolerance &&
            abs(color1[2] - color2[2]) <= tolerance);
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

void sleep(int duration) {
    std::this_thread::sleep_for(std::chrono::milliseconds(duration));
}


int main() {
    std::array<int, 3> color = get_rgb(100, 200);
    std::array<int, 3> color2 = get_rgb(100, 100);

    bool res = compeare_color(color, color2, 20);
    std::cout << res << std::endl;
    
}