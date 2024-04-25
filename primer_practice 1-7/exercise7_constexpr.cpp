#include "exercise7_constexpr.h"

/* 如果我们需要用到rate的引用或者取其地址，我们需要如下声明。否则这个声明可以省略*/
constexpr double Example::rate;
/* static vector need to initialize here. but static keyword is unnecessary */
vector<double> Example::vec(Example::vecSize); // noting vector<double> place front

class Account {
private:
    string owner;
    double amount;
    static double interestRate;
    static constexpr double todayRate = 4.28;
    static double intiRate() { return todayRate; }
public:
    Account(const string& s, double n) : owner(s), amount(n) {}
    void calculate() { amount += amount * interestRate;}
    
    static double rate() {return interestRate;}
    static void rate(double newRate) { interestRate = newRate;}
};

double Account::interestRate = 4.8;

int main() {
    Account ac("me", 2.8);
    printf("original: %f\n", Account::rate());
    Account::rate(3.2);
    ac.calculate();
    printf("after change: %f\n", Account::rate());
    return 0;
}