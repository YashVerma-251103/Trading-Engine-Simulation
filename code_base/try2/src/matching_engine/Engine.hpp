#include "./OrderBook.hpp"

struct Engine
{
    // Maching Engine Attributes
    hashmap<TradingPair, OrderBook> markets;

    // Constructor
    Engine()
    {
        markets = hashmap<TradingPair, OrderBook>();
    }

    // engine utilities
    void addNewMarket(TradingPair *tp)
    {
        markets[*tp] = OrderBook();
    }

    void place_limit_order(TradingPair *tp, float price, shPtr(Order) limitOrder)
    {
        // spair<char, string>
        if (markets.find(*tp) == markets.end())
        {
            // Orderbook for this market does not exist.
            print("\nOrder Book for this market does not exist.\n");
        }
        else
        {
            OrderBook ob = markets[*tp];
            shPtr(Price) p = shObj(Price)(price);
            ob.addLimitOrder(limitOrder, p);
            print("\nLimit Order placed for the market : ");
            tp->printMarketPair();
            print("\nOrder { ");
            limitOrder->printOrder();
            print(" }\n");
        }
    }
};