
#include "exe12_2.h"

int main() {
    StrBlob sb{"hello", "world"};
    const StrBlob csb{"const", "hello", "world", "aaa"};

    cout << "sb : " << sb.front() << " " << sb.back() << endl;
    cout << "csb: " << csb.front() << " " << csb.back() << endl; 
    // csb is a const vector, will not changed any more
    // so we should return const string if get any element.

    return 0;
}
/*

sb : front: hello back: world
csb: const front: const (this const is in the vector) const back: aaa
*/