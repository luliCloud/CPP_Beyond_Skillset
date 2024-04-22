/* 从标准输入读入字符，包括制表符，空格，换行符。并计算它们的个数
 同时还可以读入 ff， fl，fi。 注意如果i包括在fi里，既要增加i也要增加fi*/
#include <iostream>
using namespace std;
/*使用 std::noskipws 后，每次读取操作都将考虑空白字符，直到再次使用 std::skipws（默认行为）操纵符来恢复跳过空白的行为。
在使用 std::noskipws 时需要格外注意，因为很多标准输入操作依赖于跳过空白来正确解析输入，如读取数值和字符串。*/
int main() {
    unsigned aCnt = 0, eCnt =0, iCnt = 0, oCnt = 0, uCnt = 0;
    unsigned spaceCnt = 0, tabCnt = 0, newLineCnt = 0;
    unsigned ffCnt = 0, flCnt = 0, fiCnt = 0;
    char ch, prech = '\0';
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
            case'i':  // noting here
                if (prech == 'f') fiCnt++;
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
            case'f':
                if (prech == 'f') {
                    ffCnt++;
                }
                break;
            case'l':
                if (prech == 'f') {
                    flCnt++;
                }
                break;
        }
        prech = ch;  // noting prech is outside of switch condition
    }
    cout << "Number of vowel a(A): \t" << aCnt << '\n'
		<< "Number of vowel e(E): \t" << eCnt << '\n'
		<< "Number of vowel i(I): \t" << iCnt << '\n'
		<< "Number of vowel o(O): \t" << oCnt << '\n'
		<< "Number of vowel u(U): \t" << uCnt << '\n'
		<< "Number of space: \t" << spaceCnt << '\n'
		<< "Number of tab char: \t" << tabCnt << '\n'
		<< "Number of new line: \t" << newLineCnt << '\n'
		<< "Number of ff: \t" << ffCnt << '\n'
		<< "Number of fl: \t" << flCnt << '\n'
		<< "Number of fi: \t" << fiCnt << endl;

	return 0;
}

/*
output:
fi
fl
ff
iii
  
aeiuofsldlf 
Number of vowel a(A):   1
Number of vowel e(E):   1
Number of vowel i(I):   5
Number of vowel o(O):   0
Number of vowel u(U):   1
Number of space:        3
Number of tab char:     2
Number of new line:     6
Number of ff:   1
Number of fl:   1
Number of fi:   1
*/


