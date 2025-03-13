#include "./OrderBooks.h"

struct TradingPair
{
    // BTC-USD
    // BTC => BASE
    // USD => QUOTE
    // Amount of quote one is will to give to obtain base

    // TradingPair Attributes
    string base, quote;

    // Constructor
    TradingPair() : base("Basky"), quote("Qosky") {}
    TradingPair(string base, string quote) : base(base), quote(quote) {}

    bool operator==(const TradingPair &otherPair) const
    {
        return ((base == otherPair.base) && (quote == otherPair.quote));
    }
};

namespace std
{
    template <>
    struct hash<TradingPair>
    {
        auto operator()(const TradingPair &tp) const
        {
            return ((Hash<string>()(tp.base)) ^ (Hash<string>()(tp.quote)));
        }
    };
} // namespace std

struct MatchingEngine
{
    // Maching Engine Attributes
    hashmap<TradingPair,OrderBook> orderBooks; // may need to change the name to market soon for clarity.

    // Constructor
    MatchingEngine(){
        orderBooks = hashmap<TradingPair,OrderBook>();
    }
};

int main()
{

    TradingPair tp = TradingPair("BTC", "USD");

    MatchingEngine me = MatchingEngine();


    return 0;
}
