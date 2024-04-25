#include "exercise7_screen.h"

int main() {
    Screen myScreen(5, 5, 'X');
    myScreen.move(4, 0).set('#').display(cout);
    cout << "\n";
    myScreen.display(cout);
    cout << "\n";

    const Screen otherScreen(5,5,'C');
    otherScreen.display(cout);
    cout << "\n";
    return 0;
}
/*
in Screen
XXXXXXXXXXXXXXXXXXXX#XXXX
in Screen
XXXXXXXXXXXXXXXXXXXX#XXXX
in const Screen
CCCCCCCCCCCCCCCCCCCCCCCCC

注意如果我们move，set，display返回的是Screen而不是Screen&，那么修改的是Screen的副本
那么myScreen本身就不会被修改
in Screen
XXXXXXXXXXXXXXXXXXXX#XXXX
in Screen
XXXXXXXXXXXXXXXXXXXXXXXXX
*/