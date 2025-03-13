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

    void printMarketPair() const
    {
        print("\n\nNew Market => Base : " << base << " | Quote : " << quote);
    }
};

namespace std
{
    template <>
    struct hash<TradingPair>
    {
        auto operator()(const TradingPair &tp) const
        {
            return ((Hash<string>()(tp.base)) ^ (Hash<string>()(tp.quote) << 1));
        }
    };
} // namespace std

struct MatchingEngine
{
    // Maching Engine Attributes
    hashmap<TradingPair, OrderBook> markets;

    // Constructor
    MatchingEngine()
    {
        markets = hashmap<TradingPair, OrderBook>();
    }

    // engine utilities
    void addNewMarket(TradingPair *tp)
    {
        markets[*tp] = OrderBook();
    }

    spair<char, string> place_limit_order(TradingPair *tp, float price, Order *limitOrder)
    {
        if (markets.find(*tp) == markets.end())
        {
            // Orderbook for this market does not exist.
            print("\nOrder Book for this market does not exist.\n");
        }
        else
        {
            OrderBook ob = markets[*tp];
            Price p = Price(price);
            ob.addLimitOrder(limitOrder, &p);
            print_ne("\nLimit Order placed for the market : ");
            tp->printMarketPair();
            print_ne("\nOrder { ");
            limitOrder->printOrders();
            print(" }\n");
        }
    }
};

int main()
{

    TradingPair tp[] = {TradingPair("BTC", "USD"), TradingPair("EUR", "USD"), TradingPair("BTC", "USD"), TradingPair("USD", "BTC")};

    MatchingEngine me = MatchingEngine();
    for (auto tpi : tp)
    {
        me.addNewMarket(&tpi);
    }

    for (const auto &pair : me.markets)
    {
        pair.first.printMarketPair();
    }

    return 0;
}
