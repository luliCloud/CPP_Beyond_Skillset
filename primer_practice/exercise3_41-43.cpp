/* 用 指针，类型别名，和auto来循环二维数组 */
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    int arr[3][4];
    int count = 0;
    // construct 2-d arr
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            arr[i][j] = count;
            count++;
        }
    }

    cout << "--- solution 1 ---" << endl;
    // using pointer to cout arr
    // row is a pointer, pointing to an int arr(1-d) with 4 int member
    // noting the diff from int* parent[4], which is a 1d arr containing 4 int pointer
    for (int(*row)[4] = arr; row < arr + 3; row++) { // row++ increase auto based on itself type
        for (int *col = *row; col < *row + 4; col++) {
            cout << *col << " ";
        }
    }
    cout << endl;
    cout << "--- solution 2 ---" << endl;
    // using alias 
    // no alternative way to claim a pointer to a size 4 int arr
    using int_array = int[4]; // int_array is the alias of a size 4 int arr
    for (int_array* p = arr; p < arr + 3; p++) {
        for (int* q = *p; q < *p + 4; q++) {
            cout << *q << " ";
        }
    }
    cout << endl;
    cout << "--- solution 3 ---" << endl;
    // using auto
    for (auto p = arr; p < arr + 3; p++) {
        for (auto q = *p; q < *p + 4; q++) {
            cout << *q << " ";
        }
    }
    cout << endl;
    return 0;
}
/* 针对第一种写法 
解引用操作
解引用 row：由于 row 的类型是 int(*)[4]，即指向一个包含四个整数的数组的指针，所以当您对 row 使用解引用操作符 *（如 *row）时，您得到的是它指向的那个数组本身。
结果的类型：这个结果的类型是 int[4]，即一个包含四个整数的数组。
指针退化
数组到指针的退化：在C和C++中，当数组用在几乎所有表达式中时（除了作为 & 操作符的操作数和 sizeof 的操作数），数组名会退化为指向其第一个元素的指针。因此，虽然 *row 解引用得到了一个数组，但在表达式 int *col = *row; 中，这个数组名立即退化成了指向其首元素的指针。
实际操作：在表达式 int *col = *row; 中，*row 首先解引用得到 int[4] 类型的数组，然后这个数组退化为类型为 int* 的指针，指向数组的第一个元素。这个指针被赋值给 col。
*/