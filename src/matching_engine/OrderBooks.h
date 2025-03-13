#include "../imports.h"


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
        size = *order_size;
        type = order_type;
    }

    // order utilities
    void printOrders()
    {
        print(size << "," << (type ? "Ask" : "Bid") << "\n");
    }
};

struct Limit
{
    // Limit Attributes
    Price price;
    vector<Order> orders;

    // Constructor
    Limit()
    {
        price = Price();
        orders = vector<Order>();
    }
    Limit(float price) : price(Price(price))
    {
        orders = vector<Order>();
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
            (orders[i].printOrders());
        }
    }
    void addOrder(Order *new_order)
    {
        orders.push_back(*new_order);
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

    // Orderbook functionalities
    void addLimitOrder(Order *newOrder, Price *orderPrice)
    {
        assert(newOrder != nullptr);

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
};