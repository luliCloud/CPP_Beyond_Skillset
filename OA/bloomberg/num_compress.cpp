#include <iostream>
#include <vector>
using namespace std;

int numCompression(int num) {
    int res = 0;
    int count = 0;
    int prev = -1;
    int copy_num = num;

    vector<int> st; // store reverse order of num

    while (copy_num > 0) {
        int curr = copy_num % 10;
        copy_num /= 10;
        st.push_back(curr);
    }

    while (!st.empty()) {
        int curr = st.back();
        st.pop_back();

        if (curr == prev || prev == -1) {
            count++;
            prev = curr;
        } else {
            // add count first
            res *= 10;
            res += count;
            res *= 10;
            res += prev;

            count = 1; // for now
            prev = curr;
        }
    }

    // finally deal with the left
    res *= 10;
    res += count;
    res *= 10;
    res += prev;

    return res;
}

int main() {
    int res = numCompression(11122233); // 313223
    cout << res << endl;

    int res2 = numCompression(146667722); // 1114362722
    cout << res2 << endl;
    return 0;
}