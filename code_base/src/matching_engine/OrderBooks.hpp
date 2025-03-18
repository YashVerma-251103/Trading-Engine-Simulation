#include "../defines_imports_macros/imports.hpp"

// Engine structs
struct Price
{
    // Price Attributes
    int integral, fractional, scaler;

    // Constructor
    Price()
    {
        scaler = 100;
        integral = -1;
        fractional = 0;
    }
    Price(float price)
    {
        scaler = 100;
        integral = (int)price;
        fractional = (int)((price - integral) * scaler);
    }

    // Struct Utilities
    bool operator==(const Price &otherPrice) const
    {
        return ((integral == otherPrice.integral) && (fractional == otherPrice.fractional) && (scaler == otherPrice.scaler));
    }

    void printPrice() const
    {
        // print("Integral: " << integral);
        // print("Fractional: " << fractional);
        // print("Scaler: " << scaler);
        print("Integral: " << integral << " | Fractional: " << fractional << " | Scaler: " << scaler);
    }

    float getPrice()
    {
        return (float)((float)integral + ((float)fractional / (float)scaler));
    }
};

namespace std
{
    template <>
    struct hash<Price>
    {
        auto operator()(const Price &price) const
        {
            return ((Hash<int>()(price.integral)) ^ (Hash<int>()(price.fractional)) ^ (Hash<int>()(price.scaler)));
        }
    };

} // namespace std

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
    Price price;
    // need to change it to vector of pointer
    vector<Order *> orders;
    float total_volume;

    // Constructor
    Limit()
    {
        price = Price();
        orders = vector<Order *>();
        total_volume = 0;
    }
    Limit(float price) : price(Price(price))
    {
        orders = vector<Order *>();
        total_volume = 0;
    }
    Limit(Price *price) : price(*price)
    {
        assert(price != nullptr);
        orders = vector<Order *>();
        total_volume = 0;
    }

    // Limit utilities
    void updatePrice(Price *newPrice)
    {
        price = *newPrice;
    }
    void updatePrice(float *newPrice)
    {
        price = Price(*newPrice);
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
};

struct OrderBook
{
    // OrderBook Attributes
    hashmap<Price, Limit> asks, bids;
    // hashmap<Price, Limit, PriceHash> asks, bids;

    // hashmap functions
    hashmap<Price, Limit>::iterator begin(hashmap<Price, Limit> &orderMaps)
    {
        return orderMaps.begin();
    }

    // Constructors
    OrderBook()
    {
        bids = hashmap<Price, Limit>();
        asks = hashmap<Price, Limit>();
    }

    // OrderBook utilities
    void printBidOrders()
    {
        print("Bid Orders : \n");
        for (const auto &pair : bids)
        {
            // Limit limit = bids[pair.first];
            Limit limit = pair.second;
            print_ne("Current Price -> ");
            pair.first.printPrice();
            limit.printCurrentOrders();
            print("\n\n");
        }
    }
    void printAskOrders()
    {
        print("Ask Orders : \n");
        for (const auto &pair : asks)
        {
            Limit limit = pair.second;
            print_ne("Current Price -> ");
            pair.first.printPrice();
            limit.printCurrentOrders();
            print("\n\n");
        }
    }
    void printOrders()
    {
        printBidOrders();
        printAskOrders();
    }
    vector<Limit *> getAskLimits()
    {
        // TODO : return a vector of limit pointers sorted in descending order of price.
        vector<Limit *> list_of_limits = vector<Limit *>();
        for (auto &pair : asks)
        {
        }
    }
    vector<Limit *> getBidLimits()
    {
        // TODO : return a vector of limit pointers sorted in ascending order of price.
        
    }

    // Orderbook functionalities
    void addLimitOrder(Order *newOrder, Price *orderPrice)
    {
        assert(newOrder != nullptr);
        assert(orderPrice != nullptr);

        switch (newOrder->type)
        {
        case Bid:
        {
            // Price price = Price(orderPrice);
            Limit limit = bids[*orderPrice];
            // this will create a new limit at the price if it is not present so it saves time.
            if (limit.price.integral < 0)
            {
                limit.updatePrice(orderPrice);
            }
            limit.addOrder(newOrder);

            break;
        }
        case Ask:
        {
            // Price price = Price(orderPrice);
            Limit limit = asks[*orderPrice];
            // this will create a new limit at the price if it is not present so it saves time.
            if (limit.price.integral < 0)
            {
                limit.updatePrice(orderPrice);
            }
            limit.addOrder(newOrder);
            break;
        }
        default:

            break;
        }
    }
    bool fillMarketOrder(Order *newOrder)
    {
        // the major confusion i have -> since we are filling the market order using the highest limits first, then does it not mean that there is some missed amount of money as not all limits are of same price. but the market order is of fixed price.

        switch (newOrder->type)
        {
        case Bid:
        {

            break;
        }
        default:
        {
            break;
        }
        }
    }
};