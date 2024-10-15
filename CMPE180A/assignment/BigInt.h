#ifndef __BIGINT__
#define __BIGINT__
#include <vector>
#include <iostream>
using namespace std;

class BigInt {
public:
    BigInt() {
        nums.push_back(0);
    }

    BigInt(const vector<int>& digits);
    BigInt(const char* digits, int size);

    // friend function can visit other BigInt private members
    BigInt operator+(const BigInt& other) const;
    BigInt operator-(const BigInt& other) const; // may have two possibility, reverse this or deduce others
    BigInt operator*(const BigInt& other) const; // to do
    void operator-(); // change current num to opposite sign
    // BigInt operator/(const BigInt& other);
    bool operator!() const; // determine whether this are 0 or not
    bool operator==(const BigInt& other) const;  // compare nums and is_neg
    bool operator>=(const BigInt& other) const;
    bool operator>(const BigInt& other) const;
    bool operator<=(const BigInt& other) const;
    bool operator<(const BigInt& other) const;

    // pre and post
    BigInt& operator++(); // pre
    BigInt operator++(int); // post
    BigInt& operator--();  // pre
    BigInt operator--(int); // post

friend istream& operator>>(istream& is, BigInt& bi);
friend ostream& operator<<(ostream& os, const BigInt& bi);

    void print () const {
        if (is_neg) {
            cout << "-";
        }
        for (int i = 0; i < nums.size(); i++) {
            cout << nums[i];
        }
        cout << endl;
    }; // helper function to print out current digits

    bool is_neg_() const {
        return is_neg;
    }

    int size_() const {
        return nums.size();
    }

    vector<int> getter() const {
        vector<int> res;
        for (int i = 0; i < nums.size(); i++) {
            res.push_back(nums[i]);
        }
        return res;
    }

private:
    vector<int> nums;
    bool is_neg = false;

    void add_operator(const BigInt& other, vector<int>& temp) const;
    void deduct_operator(const BigInt& other, vector<int>& temp) const;
    
    int compare_helper(const BigInt& other) const;
    void deduct_helper(const vector<int>& lhs, const vector<int>& rhs, vector<int>& temp) const;
};

#endif
