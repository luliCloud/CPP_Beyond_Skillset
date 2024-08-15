#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

/* store a text value of string and provide a getter get_text(), implement < operator,
will used in fix_order of recipient for sorting */
class Message {
private:
    string msg;
    static int msg_count;  // for count the total message and assign id increasingly to every msg
    int id;
public:
    Message() { msg_count++; } // empry construct need an id too
    Message(string str) {
        msg = str;
        msg_count++;
        id = msg_count;
    }
    /** operator< 和 std::sort 的组合原理
std::sort 使用比较函数来确定元素的顺序。当你没有提供自定义比较函数时，std::sort 
默认使用容器元素的 operator<。因此，std::sort 会根据 operator< 的返回值来决定元素的排序顺序。 */
    bool operator <(const Message& other) {
        if (id < other.id) {
            return true;
        } else {
            return false;
        }
    }
    
    const string& get_text() {
        return msg;
    }
};
int Message::msg_count = 0;

/* MessageFactory need to have an empty constructor. a Methood create_message(text) that to 
return a Message obj stroing the text. So the Message Factory should receive vector<Message>, suffle, and send to receipient */
class MessageFactory {
public:
    MessageFactory() {}
    
    Message create_message(const string& text) {
        Message msg(text);
        return msg;
    }
};

/* Recipeint should receive the msgs from Network. sort the msgs in the vector, then print every message */
class Recipient {
private:
    vector<Message> msgs;
public:
    void receive(const Message& msg) {
        msgs.push_back(msg);
    }
    
    void fix_order() {
        sort(msgs.begin(), msgs.end()); // here will use the operator overloading defined in Message class. the sort will iterate the vector, compare every obj with others and use < to compare their value, then sort. 
    }
    
    void print_message() {
        for (auto& m : msgs) { // why we cannot use const auto& m here?
        /** When you use const auto& m, m is deduced as a reference to a const Message object. 
         * This means m is treated as a constant reference, and 
         * only const member functions of the Message class can be called on m. */
            const string& msg = m.get_text();
            cout << msg << endl;
        }
    }
};

/* Network receive cin, using MessageFactory to generate message and put in vector, send suffle message vector to receipient  */
class Network {
public:
    void sendMsgs(vector<Message> msgs, Recipient& re) {
        random_shuffle(msgs.begin(), msgs.end()); // noting this is a STL func in algo?
        for (const auto& msg : msgs) {
            re.receive(msg);
        }
    }
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    string txt;
    MessageFactory mf;
    vector<Message> msgs;
    while (getline(cin, txt)) {
        msgs.push_back(mf.create_message(txt));
    }
    
    Network net;
    Recipient re;
    net.sendMsgs(msgs, re);
    re.fix_order();
    re.print_message();   
    return 0;
}