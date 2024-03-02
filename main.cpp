#include <iostream>
#include <windows.h>
#include <thread>
#include <array>
#include <chrono>
#include <fstream>


#define WHITE { 255, 255, 255 }

#define BAR_X 1729 // normal: 1491 left half: 1729
#define BAR_Y 239 // normal: 237 left half: 239

#define TOL 30



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






void fish() {
    sleep(750);
    click();
    int x, y;
    get_pos(x, y);
    std::array color = get_rgb(x, y);
    bool res = compeare_color(color, WHITE, TOL);
    while (!res) {
        get_pos(x, y);
        color = get_rgb(x, y);
        res = compeare_color(color, WHITE, TOL);
    }
    sleep(100);
    click();
}

void click_to_fill_bar() {
    sleep(200);
    std::array color = get_rgb(BAR_X, BAR_Y);
    bool res = compeare_color(color, WHITE, TOL);
    while (res) {
        color = get_rgb(BAR_X, BAR_Y);
        res = compeare_color(color, WHITE, TOL);
        click();
        sleep(50);
    }
}


int main() {
    
    while (true) {
        fish();

        sleep(500);

        click_to_fill_bar();
    }

    return 0;
}