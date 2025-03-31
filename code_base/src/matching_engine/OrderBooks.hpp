#include "../defines_imports_macros/imports.hpp"

// Engine structs
struct Order
{
    // order attribute
    float size;
    BuyOrSell type;

    // struct utilities
    Order(float *order_size, BuyOrSell order_type)
    {
        assert(order_size != nullptr);

        size = *order_size;
        type = order_type;
    }
    Order(float order_size, BuyOrSell order_type) : size(order_size), type(order_type) {}

    // order utilities
    void printOrders()
    {
        print(size << "," << (type ? "Ask" : "Bid") << "\n");
    }
    bool isFilled()
    {
        return (size == 0.0f);
    }
};

struct Limit
{
    // Limit Attributes
    Price *price;
    // need to change it to vector of pointer
    vector<Order *> orders;
    float total_volume;

    // Constructor
    Limit()
    {
        price = &(Price());
        orders = vector<Order *>();
        total_volume = 0;
    }
    Limit(float price) : price(&(Price(price)))
    {
        orders = vector<Order *>();
        total_volume = 0;
    }
    Limit(Price *price) : price(price)
    {
        assert(price != nullptr);
        orders = vector<Order *>();
        total_volume = 0;
    }

    // Limit utilities
    void updatePrice(Price *newPrice)
    {
        price = newPrice;
    }
    void updatePrice(float *newPrice)
    {
        price = &(Price(*newPrice));
    }
    void printCurrentOrders()
    {
        for (size_t i = 0; i < orders.size(); i++)
        {
            (orders[i]->printOrders());
        }
    }
    void addOrder(Order *newOrder)
    {
        assert(newOrder != nullptr);
        orders.push_back(newOrder);
        total_volume += newOrder->size;
    }

    bool fillOrder(Order *marketOrder)
    {
        // Checking if the market order can even be filled or not.
        if (marketOrder->size > total_volume)
        {
            return not_filled;
        }

        assert(marketOrder->size <= total_volume);

        // float nullSize = 0.0f;
        for (auto &limitOrder : orders)
        {
            if (marketOrder->size >= limitOrder->size)
            {

                marketOrder->size -= limitOrder->size;
                total_volume -= limitOrder->size;
                limitOrder->size = 0.0f;
                // should i remove this filled order from limit ?
            }
            else
            { // false case
                limitOrder->size -= marketOrder->size;
                total_volume -= marketOrder->size;
                marketOrder->size = 0.0f;
            }

            if (marketOrder->isFilled())
            {
                break;
            }
        }
        return filled;
    }

    static void vector_merge(vector<Price *> *list, bool *reverse, int start, int mid, int end)
    {
        // new sorted vector
        vector<Price *> sorted_list = vector<Price *>();

        // merge 2 pointers
        int i = start, j = mid;
        Price *A, *B;
        bool order = (*reverse) ? (*A > *B) : (*B > *A);
        while (i < mid && j <= end)
        {
            A = (*list)[i];
            B = (*list)[j];

            if ((*A) == (*B))
            {
                sorted_list.push_back(A);
                i++;
                sorted_list.push_back(B);
                j++;
            }
            else if (order)
            {
                sorted_list.push_back(B);
                j++;
            }
            else
            {
                sorted_list.push_back(A);
                i++;
            }
        }
        free(A);
        free(B);

        // filling if some are left
        while (reverse && j <= end)
        {
            sorted_list.push_back((*list)[j++]);
        }
        while (i < mid)
        {
            sorted_list.push_back((*list)[i++]);
        }
        while ((!reverse) && j <= end)
        {
            sorted_list.push_back((*list)[j++]);
        }

        // original filler loop
        i = start;
        for (const auto &price : sorted_list)
        {
            (*list)[i++] = price;
        }

        //  TODO :need to solve this problem
        // i want to free the created vector but i am not able to.
        // free(sorted_list);
    }
    static void Limit::vector_sort(vector<Price *> *list, bool *reverse, int start, int end)
    {
        if (start <= end)
        {
            // Single Element
            if (start == end)
            {
                return;
            }

            int mid = (int)(((end - start) / 2) + start);
            // left sort
            Limit::vector_sort(list, reverse, start, mid);
            // right sort
            Limit::vector_sort(list, reverse, mid + 1, end);

            // merging sorted lists
            vector_merge(list, reverse, start, mid, end);
        }
    }
    static void linear_sort(vector<Limit *> *list, vector<Limit *> *sorted_list, bool *reverse)
    {
        int len = list->size();
        list->clear();
        switch (*reverse)
        {
        case true:
            for (auto i = 0; i < (len); i++)
            {
                list->push_back((*sorted_list)[i]);
            }
            break;

        case false:
            for (auto i = len - 1; i > (-1); i--)
            {
                list->push_back((*sorted_list)[i]);
            }
            break;
        }
    }
};

struct OrderBook
{
    // OrderBook Attributes
    hashmap<Price *, Limit *> asks, bids;
    vector<Limit *> *asks_asc, *asks_decs, *bids_asc, *bids_decs;

    // hashmap functions
    hashmap<Price *, Limit *>::iterator begin(hashmap<Price *, Limit *> &orderMaps)
    {
        return orderMaps.begin();
    }

    // Constructors
    OrderBook()
    {
        bids = hashmap<Price *, Limit *>();
        asks = hashmap<Price *, Limit *>();
        bids_asc = &vector<Limit *>();
        bids_decs = &vector<Limit *>();
        asks_asc = &vector<Limit *>();
        asks_decs = &vector<Limit *>();
    }

    // OrderBook utilities
    void printBidOrders()
    {
        print("Bid Orders : \n");
        for (auto &pair : bids)
        {
            // Limit limit = bids[pair.first];
            print_ne("Current Price -> ");
            pair.first->printPrice();
            pair.second->printCurrentOrders();
            print("\n\n");
        }
    }
    void printAskOrders()
    {
        print("Ask Orders : \n");
        for (auto &pair : asks)
        {
            print_ne("Current Price -> ");
            pair.first->printPrice();
            if (pair.second->orders.empty())
                print("Vector empty.");
            else
                print("Vector not empty.");
            pair.second->printCurrentOrders();
            print("\n\n");
        }
    }
    void printOrders()
    {
        printBidOrders();
        printAskOrders();
    }
    vector<Limit *> *getLimits(hashmap<Price *, Limit *> *bid_ask, bool reverse = false)
    {
        // TODO : return a vector of limit pointers sorted in ascending order of price.
        vector<Limit *> list_of_limits = vector<Limit *>();
        vector<Price *> list_of_prices = vector<Price *>();

        for (auto &pair : *bid_ask)
        {
            list_of_prices.push_back(pair.first);
        }

        Limit::vector_sort(&list_of_prices, &reverse, 0, list_of_prices.size() - 1);

        for (auto &price : list_of_prices)
        {
            list_of_limits.push_back((*bid_ask)[price]);
        }

        return &list_of_limits;
    }

    void limitsRefresher()
    {
        refreshAsks();
        refreshBids();
    }
    // ? Buy Market order => wants to fill using cheapest price => ask limits in ascending order
    void refreshAsks()
    {
        asks_decs = getLimits(&asks, max_first);
        Limit::linear_sort(asks_asc, asks_decs, &min_first);
    }
    // ? Sell Market order => wants to fill using highest price => ask limits in descending order
    void refreshBids()
    {
        bids_asc = getLimits(&bids, min_first);
        Limit::linear_sort(bids_decs, bids_asc, &max_first);
    }

    // Orderbook functionalities
    void addLimitOrder(Order *newOrder, Price *orderPrice)
    {
        assert(newOrder != nullptr);
        assert(orderPrice != nullptr);

        Limit temp = shptr(Limit)(orderPrice);
        switch (newOrder->type)
        {
        case Bid:
        {
            // Limit temp = Limit(orderPrice);
            bids[orderPrice] = &temp;
            // bids[orderPrice] = &(Limit(orderPrice));
            bids[orderPrice]->addOrder(newOrder);
            break;
        }
        case Ask:
        {
            // Limit temp = Limit(orderPrice);
            asks[orderPrice] = &temp;
            // asks[orderPrice] = &(Limit(orderPrice));
            asks[orderPrice]->addOrder(newOrder);
            asks[orderPrice]->printCurrentOrders();
            break;
        }
        default:

            break;
        }
    }
    bool fillMarketOrder(Order *newOrder)
    {
        // the major confusion i have -> since we are filling the market order using the highest limits first, then does it not mean that there is some missed amount of money as not all limits are of same price. but the market order is of fixed price.

        vector<Limit *> *limits;

        switch (newOrder->type)
        {
        case Bid:
            limits = asks_decs;
            break;
        case Ask:
            limits = bids_asc;
            break;
        default:
            limits = nullptr;
            break;
        }

        assert(limits != nullptr);

        // ! filling order
        for (auto &limit : *limits)
        {
            limit->fillOrder(newOrder);
            if (newOrder->isFilled())
                break;
        }
    }
};