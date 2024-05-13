#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;
/**
 * use insert method to insert ele into the map
*/
int main() {
    using Map = map<string, size_t>;
    Map m;
    for (string word; cout << "Plz enter: ", cin >> word && word != "@q";) {
        // insert try to insert the pair{word, 1} into a map
        // it return a pair, first is the iterator of this map, point to the inserted pair
        // second is a bool. if word exist in map, then false, otherwise true.
        // if  false, we enter the second condition
        // 注意如果word已经存在，那么result。first则是it指向map中已经存在的元素。
        // 所以第二个condition，即使我们不要这个判断，也可以做到。但是我们插入的时候应该是{word, 0}
        // 这样iterator在任何情况下都指向元素对的位置，且增加1
        pair<Map::iterator, bool> result = m.insert({word, 1});
        if (!result.second) {
            /**
             * already exist, then the count of word (result.first->second) need ++
            */
            (result.first->second)++;
        }
    }
    for (const auto& [key, value] : m) {
            cout << key << " " << value << endl;
    }
    return 0;
}
/**
 * Plz enter: word
Plz enter: wrrd
Plz enter: word
Plz enter: wizard
Plz enter: word
Plz enter: @q
wizard 1
word 3
wrrd 1
*/