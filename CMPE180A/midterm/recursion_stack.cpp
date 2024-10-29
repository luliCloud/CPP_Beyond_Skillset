#include <iostream>
#include <stack>
using namespace std;

void insertBottom(stack<int>& st, int val) {
    if (st.empty()) {
        st.push(val);
    } else {
        int t = st.top();
        st.pop();

        insertBottom(st, val);
        st.push(t);
    }
}

void reverseStackRecursion(stack<int>& st) {
    if (st.empty()) {
        return;
    }
    int t = st.top();
    st.pop();
    reverseStackRecursion(st);
    insertBottom(st, t);
}

int main() {
    stack<int>st({1,5,6,7,8});
    stack<int>st_copy(st);
    while (!st_copy.empty()) {
        std::cout << st_copy.top() << " ";
        st_copy.pop();
    }
    std::cout << std::endl;

    reverseStackRecursion(st);
    while (!st.empty()) {
        std::cout << st.top() << " ";
        st.pop();
    }
    std::cout << std::endl;
    return 0;
}