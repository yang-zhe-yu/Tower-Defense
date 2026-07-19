#include <iostream>
#include <Windows.h>
#include <string>
#include <conio.h>
#include <algorithm>
#include <cstdlib>
#include <time.h>
#define Set(c) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (c))
#define R FOREGROUND_RED 
#define B FOREGROUND_BLUE 
#define G FOREGROUND_GREEN
#define I FOREGROUND_INTENSITY 
using namespace std;
const int ROWS = 10, COLS = 20;
int T; char get;
void cp(int a, string s) {
    switch (a) {
    case 0: Set(I); break;
    case 1: Set(I | R); break;
    case 2: Set(I | B); break;
    case 3: Set(I | G); break;
    case 4: Set(I | R | B); break;
    case 5: Set(I | R | G); break;
    case 6: Set(I | B | G); break;
    case 7: Set(I | R | B | G); break;
    }
    cout << s;
}
bool Game() {
    static int x = 0;
    static string a[ROWS];
    static int g[ROWS];
    static bool boss = false;
    if (!boss) {
        srand(time(0));
        for (int i = 0;i < ROWS;i++) {
            a[i] = string(COLS, '0');
            g[i] = 10;
        }
        boss = true;
    }
    if (rand() % 100 < T) {
        int Bo = rand() % ROWS;
        if (a[Bo][0] < '7') a[Bo][0]++;
    }
    for (int i = 0;i < ROWS;i++) {
        if (i == x) cp(5, ">");
        else cp(0, " ");
        for (int j = 0;j < COLS;j++)
            if (a[i][j] > '0') cp(a[i][j] - '0', "■");
            else cp(0, "  ");
        cp(3, "| ");
        for (int k = 0;k < g[i];k++) cp(3, "█");
        cout << endl;
    }
    if (_kbhit()) {
        int key = _getch();
        if (key == 0xE0) {
            key = _getch();
            switch (key) {
            case 0x48:if (x > 0)x--; break;
            case 0x50:if (x < ROWS - 1)x++; break;
            }
        }
        else if (key == ' ') {
            for (int i = COLS - 1;i >= 0;i--)
                if (a[x][i] > '0') {
                    a[x][i]--;
                    break;
                }
        }
    }
    for (int i = 0;i < ROWS;i++) {
        if (a[i][COLS - 1] > '0') g[i] = max(0, g[i] - (a[i][COLS - 1] - '0'));
        a[i] = "0" + a[i].substr(0, COLS - 1);
    }
    int life = 0;
    for (int i = 0;i < ROWS;i++)
        if (g[i] > 0) return true;
    return false;
}
int main() {
    CONSOLE_CURSOR_INFO dw;
    dw.dwSize = 30;
    dw.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &dw);
    system("color F0");
    cout << "\n\t\t\t\t\t游戏规则：\n";
    cout << "  保护所有行的「生命值」（右侧绿色方块 █），避免所有行的生命值归 0。";
    cout << "\n  移动光标：使用「上方向键 ↑」和「下方向键 ↓」，控制左侧的 > 符号在 10 行之间切换，选中你要操作的行。";
    cout << "\n  攻击方块：选中目标行后，按「空格键」攻击 —— 会从该行最右侧的非 0 ";
    cout << "\n  方块开始，降低其强度（数字减小，颜色变浅），直到方块消失（变回 0，显示空白）。";
    cout << "\n  当方块移动到最右侧（每行最右边的位置）时，会根据方块数字（1~6）削减对应行的生命值（数字多大，就减多少生命值）。";
    cout << "\n  生命值以绿色方块 █ 显示，初始每行为 10 个，减后不会恢复。";
    cout << "\n\t\t\t1，简单\t2，中等\t3，炼狱\n";
    get = _getch();
    switch (get) {
    case '1': T = 20; break;
    case '2': T = 50; break;
    case '3': T = 80; break;
    }
    system("mode con cols=55 lines=11");
    while (Game()) {
        Sleep(100);
        system("cls");
    }
    system("cls");
    Set(I | R);
    cout << "\n\n\n\t\t游戏结束";
}
