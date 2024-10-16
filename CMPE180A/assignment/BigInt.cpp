#include "BigInt.h"
#include <stdexcept>
#include <algorithm>
#include <string>
#include <sstream>
#include <string.h>
using namespace std;

BigInt::BigInt(const vector<int>& digits) {
    int n = digits.size();
    if (n == 0) {
        throw invalid_argument("input size is 0");
    }
    
    // remove zero
    int i;
    for (i = 0; i < n - 1; i++) {
        if (digits[i] == 0) {
            continue;
        } else {
            break;
        }
    }
    if (i < n && digits[i]< 0) {
        is_neg = true;
        nums.push_back(-digits[i]);
        i++;
    }    
    while (i < n) {
        if (digits[i] < 0) {
            throw invalid_argument("Invalid input: no negative number should appear in middle of digits");
        }
        nums.push_back(digits[i]);
        i++;
    }
    if (nums.empty()) {
        nums.push_back(0);
    }
    if (nums[0] == 0) {
        is_neg = false;
    }
}

BigInt::BigInt(const char* digits, int size) {
    if (strlen(digits) == 0) {
        throw invalid_argument("input size is 0");
    }
    
    int i = 0;
    if (i < size && digits[i] == '-') {
        is_neg = true;
        i++;
    } else if (!isdigit(digits[i])) {
        throw invalid_argument("Invalid input: only number and '-' is allowed");
    }

    for (; i < size - 1; i++) {
        if (digits[i] == '0') {
            continue;
        } else if (!isdigit(digits[i])) {
            throw invalid_argument("Invalid input: only number and '-' is allowed");
        } else {
            break;
        }
    }

    while (i < size) {
        if (!digits[i]) {
            throw invalid_argument("Invalid input: only number and '-' is allowed");
        } else {
            int num = digits[i] - '0';
            nums.push_back(num);
            i++;
        }
    }
    if (nums.empty()) {
        nums.push_back(0);
    }
    if (nums[0] == 0) {
        is_neg = false;
    }
}

// helper function for adding two pos or neg
void BigInt::add_operator(const BigInt& other, vector<int>& temp) const {
    vector<int> a = this->nums, b = other.nums;
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end()); // reverse so that one-digit at 0th idx

    int sz = max(a.size(), b.size()); 
    bool carry = false; // record whether add 1 to next digit
    for (int i = 0; i < sz; i++) {
        int curr = 0;
        if (carry) {
            curr += 1;
            carry = false;
        }
        if (i < a.size()) {
            curr += a[i];
        }

        if (i < b.size()) {
            curr += b[i];
        }

        if (curr > 9) {
            curr %= 10;
            carry = true;
        }
        temp.push_back(curr);
    }
    // reverse temp
    reverse(temp.begin(), temp.end());
}
/** compare abs. 0 is equal. 1 is this > other. 2 is this < other */
int BigInt::compare_helper(const BigInt& other) const {
    // start from highest to lowest
    if (this->nums.size() > other.nums.size()) {
        return 1;
    }

    if (this->nums.size() < other.nums.size()) {
        return 2;
    }

    // size equal, so we need to determine which one is larger one by one
    int n = this->nums.size();
    for (int i = 0; i < n; i++) {
        if (this->nums[i] == other.nums[i]) {
            continue;
        } else if (this->nums[i] > other.nums[i]) {
            return 1;
        } else {
            return 2;
        }
    }
    return 0;
}

void BigInt::deduct_operator(const BigInt& other, vector<int>& temp) const {
    int comp = compare_helper(other);
    if (comp == 0) {
        temp.push_back(0);
    } else if (comp == 1) {
        deduct_helper(this->nums, other.nums, temp); 
        // when call a member funciton inside a const function
        // the called function should be const too
    } else {
        deduct_helper(other.nums, this->nums, temp);
    }
}

void BigInt::deduct_helper(const vector<int>& lhs, const vector<int>& rhs, vector<int>& temp) const {
    // always bigger one before
    vector<int> a = lhs, b = rhs;
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end()); // reverse so that one-digit at 0th idx
    for (int i = 0; i < a.size(); i++) {
        if (i < b.size()) {
            if (a[i] < b[i] && i < a.size() - 1) {
                a[i + 1]--;
                a[i] += 10;
            }
            int c = a[i] - b[i];
            temp.push_back(c);
        } else {
            if (i < a.size() - 1 && a[i] < 0) {
                a[i] += 10;
                a[i + 1]--;
            }
            temp.push_back(a[i]);
        }
    }
    
    int i = temp.size() - 1;
    while (i >= 0 && temp[i] == 0) {
        i--;
    }
    temp.resize(i + 1);
    reverse(temp.begin(), temp.end());
}

// we will iterate since the last digit of the. 
// for the later one is a neg. we infer it to operator -
BigInt BigInt::operator+(const BigInt& other) const {
    // condition 1: + vs -;
    // condition 2: - vs +
    // condition 3: same sign
    // how to obtain the number from other. using getter. no need. we can access otther instance
    // private number if the same class as this.

    vector<int> temp;
    if (this->is_neg == other.is_neg) {
        add_operator(other, temp);
        BigInt res(temp);
        if (this->is_neg) {
            res.is_neg = true;
        }
        return res;
    } else {
        deduct_operator(other, temp);
        BigInt res(temp);

        int comp = compare_helper(other);
        if (comp == 0) {
            return res;
        }
        if (this->is_neg) {
            if (comp == 1) { // this greater
                res.is_neg = true;
            } 
        } else {
            if (comp == 2) {
                res.is_neg = true;
            }
        }
        return res;
    }
    BigInt big;
    return big;
}

BigInt BigInt::operator-(const BigInt& other) const {
    BigInt opposite_other(other.nums);
    opposite_other.is_neg = !other.is_neg;
    return operator+(opposite_other);
}

void BigInt::operator-() {
    this->is_neg = !this->is_neg;
}

BigInt BigInt::operator*(const BigInt& other) const {
    int m = this->nums.size(), n = other.nums.size();
    vector<int> val(m + n , 0);

    vector<int> a = this->nums, b = other.nums;
    
    for (int i = m - 1; i >= 0; i--) {
        for (int j = n - 1; j >= 0; j--) {
            int curr = a[i] * b[j];
            curr += val[i + j + 1]; // reprensent one digits smaller in the val. 10digit of prev cal
            val[i + j + 1] = curr % 10; // remainder
            val[i + j] += curr / 10; // noting here. should be +=. have other res add later. for higher digits
        }
    }

    int i = 0; 
    for (; i < m + n; i++) {
        if (val[i] != 0) {
            break;
        }
    }
    if (i == m + n) {  // original is 0 too
        return BigInt("0", 0);
    }

    vector<int> vec = vector<int>(val.begin() + i, val.end());
    BigInt res(vec);
    if (this->is_neg != other.is_neg) {
        res.is_neg = true;
    }
    return res;
}

bool BigInt::operator!() const {
    if (this->nums.size() == 1 && nums[0] == 0) {
        return true;
    } else {
        return false; // if any number rather than 0, return true.
    }
}

bool BigInt::operator==(const BigInt& other) const {
    int comp = compare_helper(other);
    if (comp == 0 && (this->is_neg == other.is_neg)) {
        return true;
    } 
    return false;
}

bool BigInt::operator>(const BigInt& other) const {
    int comp = compare_helper(other);
    if (comp == 0 && (this->is_neg == other.is_neg)) {
        return false;
    } else if (comp == 0) {
        return this->is_neg == false ? true : false;
    }

    // signal is different
    if (!this->is_neg && other.is_neg) {
        return true;
    }
    if (this->is_neg && !other.is_neg) {
        return false;
    }

    // sig is the same
    if (comp == 1) {
        if (this->is_neg) {
            return false;
        } else {
            return true;
        }
    } else { //other abs greater
        if (this->is_neg) {
            return true;
        } else {
            return false;
        }
    }
    return false;
}

bool BigInt::operator>=(const BigInt& other) const {
    if (*this > other || *this == other) {
        return true;
    }
    return false;
}

bool BigInt::operator<(const BigInt& other) const {
    if (*this >= other) {
        return false;
    }
    return true;
}

bool BigInt::operator<=(const BigInt& other) const {
    if (*this > other) {
        return false;
    }
    return true;
}

// pre increment. return ref to this. as we may immediately modify this 
BigInt& BigInt::operator++() {
    *this = *this + BigInt("1", 1);
    return *this;
}
// int is defaul-rule in c++ that diff pre and post. and return BigInt is to keep track of 
// original value. But we will no longer need to modify it
BigInt BigInt::operator++(int) {
    BigInt temp = *this;
    ++(*this);
    return temp;
}

BigInt& BigInt::operator--() {
    *this = *this - BigInt("1", 1);
    return *this;
}

BigInt BigInt::operator--(int) {
    BigInt temp = *this;
    --(*this);
    return temp;
}

// need to have instance of BigInt. and it need to be modify from input
istream& operator>>(istream& is, BigInt& bi) {   
    string str;
    is >> str;
    int n = str.size();
    if (str.empty()) {
        throw invalid_argument("input is empty");
    }

    for (char c : str) {
        if (!isdigit(c) && c != '-') {
            throw invalid_argument("input should be num or '-'");
        }
    }
    bi = BigInt(str.c_str(), n); // convert str to const char*
    return is;
}

ostream& operator<<(ostream& os, const BigInt& bi) {
    cout << "This Big Int is: ";
    if (bi.is_neg) {
        cout << "-";
    }
    for (int i = 0; i < bi.nums.size(); i++) {
        cout << bi.nums[i];
    }
    return os;
}

int main() {
    vector<int> digits = {0, 0, 0, 2, 3, 4, 5}; // 2345
    BigInt bi1(digits);
    cout << "bi1: ";
    bi1.print();

    const char* str = "-0012345"; // -12345
    BigInt bi2(str,8);
    cout << "bi2: ";
    bi2.print();

    BigInt bi3 = bi1 + bi2;
    cout << "bi3: ";
    bi3.print();

    BigInt bi4 = BigInt("2346", 4) - bi1;
    BigInt bi5 = bi2 - bi1;
    cout << "bi4: ";
    bi4.print();
    cout << "bi5: ";
    bi5.print();

    BigInt bi6 = BigInt({1, 2, 3}) * BigInt("123", 3);
    cout << bi6 << endl;

   
    if (bi4 == bi5) {
         cout << "bi4 == bi5";
    } else {
        cout << "bi4 != bi5";
    }
    cout << endl;
    
    if (!bi4) { // if 0 enter this condition
        cout << "bi4 == 0";
    } else { // otherwise must enter this, no matter what it is.
        cout << "bi4 != 0";
    }
    cout << endl;

    cout << "bi2 >= bi3?: " << (bi2 >= bi3) << endl;
    cout << "bi2 <= bi3?: " << (bi2 <= bi3) << endl;

    bi1++;
    bi1.print();
    bi1--;
    bi1.print();

    --bi2;
    bi2.print();
    ++bi2;
    bi2.print();


    cout << bi2 << endl;
    istringstream input("0001356748326356");
    input >>  bi2;
    cout << bi2 << endl;

    return 0;
}