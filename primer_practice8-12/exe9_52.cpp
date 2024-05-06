/*使用stack处理括号化的表达式。当你看到一个左括号，将其记录下来。
当你在一个左括号之后看到一个右括号，从stack中pop对象，直至遇到左括号，
将左括号也一起弹出栈。然后将一个值（括号内的运算结果）
push到栈中，表示一个括号化的（子）表达式已经处理完毕，被其运算结果所替代。*/
#include <iostream>
#include <cctype>
#include <stack>
#include <string>
using namespace std;

string calculate(const string& l, const string& op, const string& r) {
    int left = atoi(l.c_str()), right = atoi(r.c_str());
    int num;
    if (op == "+") {
        num = left + right;
    } else if (op == "-") {
        num = left - right;
    } else if (op == "*") {
        num = left * right;
    } else if (op == "/") {
        num = left / right;
    }
    return to_string(num);
}

stack<string> readString(const string& str) {
    stack<string> res;
    for (int i = 0; i < str.size(); ) {
        char c = str[i];
        if (c == ' ') {continue;}
        if (c != ')') {
            if (c == '(') {
                res.push(string(1, c));
                i++;
            } else if (isdigit(c)) {
                string curr;
                while (i < str.size() && isdigit(str[i])) {
                    curr += str[i];
                    i++;
                }
                res.push(curr);
            } else {  // +-*/
                res.push(string(1, c));
                i++;
            }
        } else {  // top 1 is r, then op, then l
            string r = res.top();
            res.pop();
            string op = res.top();
            res.pop();
            string l = res.top();
            res.pop();
            
            res.pop(); // delete the (
            res.push(calculate(l, op, r));
            i++;
        }
    }
    return res;
}

int main() {
    string formular = "1+2*(20/5)-100";
    // string formular = "1+2-100";
    stack<string> st = readString(formular);
    while (!st.empty()) {
        cout << st.top() << " ";
        st.pop(); 
    }
    cout << endl;
    return 0;
}
/*
here remain the question: how to calcualte the right result
100 - 4 * 2 + 1 
*/