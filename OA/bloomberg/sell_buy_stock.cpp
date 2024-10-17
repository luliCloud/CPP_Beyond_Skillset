#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Trade {
    double date; // trading date
    string type; // BUY or SELL
    int shares;  // stock sahres
    double price; // price
    Trade(double d, string t, int s, double p) : date(d), type(t), shares(s), price(p) {}
};

// checking the trading is valid
bool isValidTrader(const vector<Trade>& trades) {
    queue<Trade> buyQueue; // to store unmatched BUY op

    for (const auto& trade : trades) {
        if (trade.type == "BUY") {
            // every time BUY, add to buy queue
            buyQueue.push(trade);
        } else if (trade.type == "SELL") {
            int shareToSell = trade.shares;

            // checking whether BUY within 30 days. evey "SELL" need to check valid
            while (!buyQueue.empty() && shareToSell > 0) {
                Trade& buyTrade = buyQueue.front();

                if (trade.date - buyTrade.date > 30) {
                    buyQueue.pop(); // if execeed 30 for last buy, remove directly. will handle
                    // shareToSell later in this loop
                    shareToSell -= buyTrade.shares;
                    continue;
                } // if not exceed 30, still kept in queue, wait for next possible sell

                if (trade.price > buyTrade.price) {
                    return false; //within 30 days and price invalid. trade > buy
                }

                if (buyTrade.shares <= shareToSell) {
                    shareToSell -= buyTrade.shares;
                    buyQueue.pop();
                } else {
                    shareToSell -= buyTrade.shares;
                    buyTrade.shares -= shareToSell; // noting this should be deducted too
                }
            }

            // if the buy already empty but the toShare still >0
            if (shareToSell > 0) {
                return false;
            }
        }
        
    }
    return true;
}

int main() {
    vector<Trade> trades = {
        {9.1, "BUY", 100, 50},  // date, type, shares, price
        {9.2, "BUY", 50, 55},
        {9.3, "SELL", 50, 80},   // 无效，因为30天内不能赚钱
        {40.1, "SELL", 100, 80}, // 合法，超过30天，价格不再受限制
        {9.4, "SELL", 50, 45},   // 合法卖出
    };

    if (isValidTrader(trades)) {
        cout << "交易序列有效" << endl;
    } else {
        cout << "交易序列无效" << endl;
    }

    return 0;
}
