#include <string>
#include <iostream>
using namespace std;

string deepest_string(const string& input) {
    int max_depth = 0;
    int curr_depth = 0;
    string curr;
    string deepest_str;

    int n = input.size();
    for (int i = 0; i < n; i++) {
        char c = input[i];
        if (c == '(') {
            // indicate enter next level
            curr_depth++;
            // discard what we save for prev level, it for sure not the deepest
            curr.clear();
        } else if (c == ')') {
            if (curr_depth > max_depth) {
                max_depth = curr_depth;
                deepest_str = curr;
                curr.clear();
            }
            curr_depth--; // return back to last stack
        } else {
            curr += c;
        }
    }
    return deepest_str;
}

int main() {
    std::string input = "a(b(c)a(c(ac)))";
    
    std::string result = deepest_string(input);
    std::cout << "Deepest content: " << result << std::endl;

    return 0;
}