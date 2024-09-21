#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <string>
#include <priority_queue>
using namespace std;

class StockTrading {
private:
    unordered_map<string, int> stock; // stock_name -> sell num
    /** reason of using unordered_map and sort, not pq. 
     * compare insert: map is O1, and pq is logN.
     * compare read all stock from greatest to smallest. hash_map and sort (nlogn), 
     * but for pq, we need to pop out all ele in pq, every element pop out will be logN. N in total is NlogN. 
     * So the insertion cost of pq is greater than map and sort
     */

public:
    void add_trade(const string& stock_name, int sold_num) {
        stock[stock_name] += sold_num; // noting is add. as some stock may sold twice or more
    }

    vector<pair<string, int>> get_sorted_stock() {
        vector<pair<string, int>> res(stock.begin(), stock.end());

        //sort(res.begin(), res.end(), greater<pair<string, int>>());
        sort(res.begin(), res.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.second > b.second;
        });
        return res;

        /** pq 排序 */
        priority_queue<pair<string, int>, vector<pair<string, int>>, 
        function<bool(const pair<string, int>&, const pair<string, int>&)>> pq (
            [](const pair<string, int>& lhs, const pair<string, int>& rhs) {
                return lhs.first > rhs. first;
            }
        );
    }

};

int main() {

    StockTrading stock_trading;

    // Add trades for various stocks
    stock_trading.add_trade("AAPL", 100);
    stock_trading.add_trade("GOOGL", 150);
    stock_trading.add_trade("AAPL", 50);
    stock_trading.add_trade("TSLA", 200);

    // Get and print the sorted stock names and trade volumes
    vector<pair<string, int>> sorted_trades = stock_trading.get_sorted_stock();

    for (const auto& trade : sorted_trades) {
        cout << trade.first << ": " << trade.second << endl;
    }
    return 0;
}