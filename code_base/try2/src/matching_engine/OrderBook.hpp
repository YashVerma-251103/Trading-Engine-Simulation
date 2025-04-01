#include "../fundamental_structs/Limit.hpp"

struct OrderBook
{
    // ? Attributes
    hashmap<shPtr(Price), shPtr(Limit)> asks, bids;
    vector<shPtr(Limit)> *asks_asc, *bids_asc, *asks_desc, *bids_desc;

    // ! Hashmap Functionalities
    hashmap<shPtr(Price), shPtr(Limit)>::iterator begin(hashmap<shPtr(Price), shPtr(Limit)> &orderMaps)
    {
        return orderMaps.begin();
    }

    // ? Constructors
    OrderBook()
    {
        bids = hashmap<shPtr(Price), shPtr(Limit)>();
        asks = hashmap<shPtr(Price), shPtr(Limit)>();
        asks_desc = &(vector<shPtr(Limit)>());
        asks_asc = &(vector<shPtr(Limit)>());
        bids_desc = &(vector<shPtr(Limit)>());
        bids_asc = &(vector<shPtr(Limit)>());
    }

    void printOrders(hashmap<shPtr(Price), shPtr(Limit)> *orders, BuyOrSell type)
    {
        assert(orders != nullptr);
        println(((type) ? "Ask" : "Bid") << " Orders : \n");
        for (auto &Pair : *orders)
        {
            print("Current Price -> ");
            Pair.first->printPrice();
            Pair.second->printCurrentOrders();
            println("\n");
        }
    }
    void printOrders()
    {
        printOrders(&asks, Ask);
        printOrders(&bids, Bid);
    }
    vector<shPtr(Limit)> *getLimits(hashmap<shPtr(Price), shPtr(Limit)> *bid_ask, bool reverse = false)
    {
        assert(bid_ask != nullptr);
        vector<shPtr(Limit)> list_of_limits = vector<shPtr(Limit)>();
        vector<shPtr(Price)> list_of_prices = vector<shPtr(Price)>();

        for (auto &Pair : *bid_ask)
            list_of_prices.push_back(Pair.first);

        Limit::vector_sort(&list_of_prices, &reverse, 0, (list_of_prices.size() - 1));

        for (auto &price : list_of_prices)
            list_of_limits.push_back((*bid_ask)[price]);

        return &list_of_limits;
    }
    void refreshLimits(bool ask_limits = true)
    {
        // ? Buy Market order => wants to fill using cheapest price => ask limits in ascending order
        if (ask_limits)
        {
            asks_desc = getLimits(&asks, max_first);
            Limit::linear_sort(asks_asc, asks_desc, &min_first);
            return;
        }
        // ? Sell Market order => wants to fill using highest price => bids limits in descending order
        bids_asc = getLimits(&bids, min_first);
        Limit::linear_sort(bids_desc, bids_asc, &max_first);
    }
    void refreshLimits()
    {
        refreshLimits(true);
        refreshLimits(false);
    }

    void addLimitOrder(shPtr(Order) new_order, shPtr(Price) order_price)
    {
        assert(new_order != nullptr && order_price != nullptr);

        shPtr(Limit) temp = shObj(Limit)(order_price);
        switch (new_order->type)
        {
        case Bid:
            bids[order_price] = temp;
            bids[order_price]->addOrder(new_order);
            break;
        case Ask:
            asks[order_price] = temp;
            asks[order_price]->addOrder(new_order);
            break;
        }
    }

    bool fillMarketOrder(shPtr(Order) market_order)
    {
        assert(market_order != nullptr);

        vector<shPtr(Limit)> *limits;
        switch (market_order->type)
        {
        case Bid:
            limits = asks_desc;
            break;
        case Ask:
            limits = bids_asc;
            break;
        default:
            limits = nullptr;
            break;
        }

        assert(limits!=nullptr);

        // ! filling order
        for (auto &limit : *limits){
            limit->fillOrder(market_order);
            if (market_order->isFilled())
                break;
        }
    }
};
