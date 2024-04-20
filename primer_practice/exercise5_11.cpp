/* 从标准输入读入字符，包括制表符，空格，换行符。并计算它们的个数*/
#include <iostream>
using namespace std;
/*使用 std::noskipws 后，每次读取操作都将考虑空白字符，直到再次使用 std::skipws（默认行为）操纵符来恢复跳过空白的行为。
在使用 std::noskipws 时需要格外注意，因为很多标准输入操作依赖于跳过空白来正确解析输入，如读取数值和字符串。*/
int main() {
    unsigned aCnt = 0, eCnt =0, iCnt = 0, oCnt = 0, uCnt = 0;
    unsigned spaceCnt = 0, tabCnt = 0, newLineCnt = 0;
    char ch;
    while (cin >> noskipws >> ch) { // not skip pws
        switch(ch)
        {
            case'a':
            case'A':
                aCnt++;
                break;
            case'e':
            case'E':
                eCnt++;
                break;
            case'i':
            case'I':
                iCnt++;
                break;
            case'u':
            case'U':
                uCnt++;
                break;
            case' ':
                spaceCnt++;
                break;
            case'\t':
                tabCnt++;
                break;
            case'\n':
                newLineCnt++;
                break;
        }
    }
    cout << "Number of vowel a(A): \t" << aCnt << '\n'
		<< "Number of vowel e(E): \t" << eCnt << '\n'
		<< "Number of vowel i(I): \t" << iCnt << '\n'
		<< "Number of vowel o(O): \t" << oCnt << '\n'
		<< "Number of vowel u(U): \t" << uCnt << '\n'
		<< "Number of space: \t" << spaceCnt << '\n'
		<< "Number of tab char: \t" << tabCnt << '\n'
		<< "Number of new line: \t" << newLineCnt << endl;

	return 0;
}

/*
output:
1
2
eyrytyiqwiqer "   
sdifndnslla; 
Number of vowel a(A):   1
Number of vowel e(E):   2
Number of vowel i(I):   3
Number of vowel o(O):   0
Number of vowel u(U):   0
Number of space:        5
Number of tab char:     1
Number of new line:     4
*/


