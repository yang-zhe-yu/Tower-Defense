#include <iostream>
#include <windows.h>
#include <string>
#include <conio.h>
#include <algorithm>
#include <time.h>
#define S(c) system(c);
#define Set(c) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|(c))
#define R FOREGROUND_RED 
#define B FOREGROUND_BLUE 
#define G FOREGROUND_GREEN
using namespace std;
const short L = 10, C = 40;
HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE); CONSOLE_CURSOR_INFO info = { 1,0 };
string a[L]; short T, x = 4, g[L] = { 6,6,6,6,6,6,6,6,6,6 };
void pos(int x, int y) { COORD Pos = { x,y }; SetConsoleCursorPosition(H, Pos); }
void cp(short a, string s) {
    switch (a) {
    case 0: Set(R | B | G); break; 
    case 1: Set(R | B); break;
    case 2: Set(B); break;
    case 3: Set(B | G); break;
    case 4: Set(G); break;
    case 5: Set(R | G); break;
    case 6: Set(R); break;
    }
    cout << s;
}
bool Game() {
    for (short i = 0;i < L;i++)
        if (g[i] > 1) return true;
    return false;
}
int main() {
    SetConsoleCursorInfo(H, &info); S("color F0");
    cout << "\n\t\t\t\t\t游戏规则：\n";
    cout << "\t  保护所有行的生命值（右侧敌人 ），避免所有的生命值归 0。";
    cout << "\n\t  使用↑和↓控制<在10行之间切换，选中你要操作的行。";
    cout << "\n\t  选中目标行后，按空格攻击，会攻击该行最右侧的敌人";
    cout << "\n\t  敌人开始，降低其强度（颜色变浅），直到敌人消失。";
    cout << "\n\t  当敌人到每行最右边时，会根据敌人强度削减对应行的生命值。";
    S("pause"); S("mode con cols=87 lines=12"); S("color 0F");
    for (int i = 0;i < L;i++)
        for (int j = 0;j < C;j++) a[i] = a[i] + "0";
    time_t start = time(NULL); srand(start);
    while (Game()) {
        pos(0, 0); time_t t = time(NULL); T++; cp(3, " ");
        cout << "  第 " << t - start << " 秒\t\t\t\t\t 危险值对应的颜色：";
        for (short i = 6;i;i--) cp(i, " "), cout << i << ' ';
        if (T == 20) {
            T = 0; short BX = rand() % L;
            if (g[BX]) a[BX][0] += rand() % 6 + 1;
        }
        for (short i = 0;i < L;i++) {
            cout << endl;
            for (short j = 0;j < C;j++)
                if (a[i][j] > '0') cp(a[i][j] - '0', "●");
                else cp(0, "  ");
            if (i == x) cp(0, "<"); else cp(0, " ");
            if (g[i] > 0) { cp(7 - g[i], "| ("); cout << g[i] << ')'; }
            else cp(6, "| ( )");
        }
        for (short i = 0;i < L;i++) {
            if (a[i][C - 1] > '0') g[i] -= (a[i][C - 1] - '0');
            a[i] = "0" + a[i].erase(C - 1, 1);
        }
        if (_kbhit()) {
            char k = _getch();
            if (k == 72 && x > 0) x--;
            if (k == 80 && x < L - 1) x++;
            if (k == ' ') {
                for (short i = C - 1;i >= 0;i--)
                    if (a[x][i] > '0') { a[x][i]--; break; }
            }
        }
    }
    S("cls"); Set(R);
    cout << "\n\n\n\t\t游戏结束\n\t  成绩：" << (time(NULL) - start) * 1.0 << "秒";
}
