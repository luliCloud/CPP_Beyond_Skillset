#ifndef _SCREEN_
#define _SCREEN_
#include <iostream>
#include <string>
using namespace std;

class Screen; // pre-decalre, for ref in WindowMgr

class WindowMgr {
public:
//类型名alias的定义通常出现在类的开始处，这样就能确保所有使用该类型的成员都出现在类名的定义之后。
    using ScreenIndex = vector<Screen>::size_type; // similar to iterator, the alias in vector template
    // can use this to represent any data type in a vector. generally used for vector.size() or idx in vector
    inline void clear(ScreenIndex);
private:
    vector<Screen> screens;
};

class Screen {
    friend void WindowMgr::clear(ScreenIndex); // don't forget void
public:
    using pos = string::size_type;  // pos是alias
    // 两种定义别名的方法
    // using pos = size_type[10];
    // typedef size_type pos[10];

    /* 三个构造函数：一个默认构造函数；
    另一个构造函数接受宽和高的值，然后将contents 初始化成给定数量的空白；
    第三个构造函数接受宽和高的值以及一个字符，该字符作为初始化后屏幕的内容。
    contents is a string, string(size_type, char)*/
    Screen() = default;
    Screen(pos ht, pos wd) : height(ht), width(wd), contents(ht * wd, ' ') {}
    Screen(pos ht, pos wd, char c) 
    : height(ht), width(wd), contents(ht * wd, c) {}

    char get() const { return contents[cursor]; };
    char get(pos r, pos c) const { return contents[r * width + c]; }
    /* move, set and display. we will do Screen.move().set().display. so return Screen& */
    inline Screen& move(pos r, pos c);
    inline Screen& set(char c);
    inline Screen& set(pos r, pos c, char ch);
    /* overload the display, for const Screen and not const Screen. As it is for different caller, can overload */
    
    /* for const Screen */
    const Screen& display(ostream& os) const {
        cout << "in const Screen" << endl;
        to_display(os);  // os can be changed in to_display func, but const is the promise to Screen obj
        return *this;
    }
    
    /* for general Screen obj */
    Screen& display(ostream& os) {
        cout << "in Screen" << endl;
        to_display(os);
        return *this;
    }
private:
    pos cursor, height, width;
    string contents;
    void to_display(ostream& os) const { os << contents; };
};

inline void WindowMgr::clear(ScreenIndex i) {
    Screen& s = screens[i]; // screens is the container for screen
    s.contents = string(s.height * s.width, ' ');
}

inline Screen& Screen::move(pos r, pos c) {
    cursor = r * width + c;
    return *this;
}

inline Screen& Screen::set(char c) {
    contents[cursor] = c;
    return *this;
}

inline Screen& Screen::set(pos r, pos c, char ch) {
    contents[r * width + c] = ch;
    return * this;
}
#endif
/*
用途：string::size_type 主要用于表示字符串的长度和访问字符串中的字符位置。使用这个类型而非普通的 int 或 size_t 可以提高代码的可移植性和安全性，因为它自动适应不同平台和编译器对整型大小的具体实现。
定义：在 std::string 的实现中，size_type 通常是 std::size_t 的一个别名。std::size_t 是 C++ 标准库中用来表示大小和计数的标准无符号整型，其大小足以表示内存中任何对象的大小。
*/