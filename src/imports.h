#include <iostream>
#include <vector>
#include <unordered_map>

// Namespace defines
#define vector std::vector
#define hashmap std::unordered_map

// utility macros
#define print(obj) (std::cout << obj << std::endl)

// Value enums and respective macros
enum BuyOrSell
{
    // Options
    Bid = 0,
    Ask = 1
};
#define BuyOrSell enum BuyOrSell

// structs
struct Price
{
    // Price Attributes
    int integral, fractional, scaler;

    // Constructor
    Price(float price)
    {
        scaler = 100000;
        integral = (int)price;
        fractional = (int)((price - integral) * scaler);
    }

    // Struct Utilities
    void print_price()
    {
        print("Integral: " << integral);
        print("Fractional: " << fractional);
        print("Scaler: " << scaler);
    }

    float get_price()
    {
        return (float)((float)integral + ((float)fractional / (float)scaler));
    }
};

struct Order
{
    // order attribute
    float size;
    BuyOrSell type;

    // struct utilities
    Order(float order_size, BuyOrSell order_type)
    {
        size = order_size;
        type = order_type;
    }

    // order utilities
    void print_orders()
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
    Limit(float price) : price(Price(price))
    {
        orders = vector<Order>();
    }

    // Limit Functionalities
    void print_current_orders()
    {
        for (size_t i = 0; i < orders.size(); i++)
        {
            (orders[i].print_orders());
        }
    }
    void add_order(Order new_order)
    {
        orders.push_back(new_order);
    }
};

struct OrderBook
{
    hashmap<Price, Limit> asks, bids;
};
