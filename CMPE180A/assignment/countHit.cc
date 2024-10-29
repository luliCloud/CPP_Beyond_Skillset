#include <iostream>
#include <stack>
#include "countHit.h"
using namespace std;

int countHit(vector<Asteroid> a) {
    stack<Asteroid> st;

    for (const auto& ast : a) {
        if (st.empty()) {
            st.push(ast);
            continue;
        }

        bool destroy = false; // check whether right not destroy till the end
        if (ast.d == Direction::left) { // only the one with left dir need to be addressed
            while (!st.empty()) {
                if (st.top().d == Direction::left) {
                    break;
                }

                if (st.top().d == Direction::right) {
                    if (st.top().m == ast.m) {
                        st.pop(); // left destroyed
                        destroy = true;
                        break; // both destroyed
                    } else if (st.top().m > ast.m) {
                        destroy = true;
                        break; // left destroyed
                    } else { // right is small
                        st.pop(); // keep check the next in next while loop
                    }
                }
            }
        }
        // check whetehr destroy yet
        if (!destroy) {
            st.push(ast);
        }
    }
    // check the whole stack to see how many is right
    int res = 0;
    while (!st.empty()) {
        auto curr = st.top();
        st.pop();
        if (curr.d == Direction::right) {
            res++;
        }
    }
    return res;
}

int main() {
    Asteroid a, b, c, d;
    a.m = 10, a.d = Direction::right;
    b.m = 11, b.d = Direction::left;
    c.m = 11, c.d = Direction::right;
    d.m = 5, d.d = Direction::left;
    vector<Asteroid> arr = {a,b,c,d};

    int res = countHit(arr);
    cout << res << endl;

    return 0; 
}