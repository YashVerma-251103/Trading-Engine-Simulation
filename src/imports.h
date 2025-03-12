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
    void printPrice()
    {
        print("Integral: " << integral);
        print("Fractional: " << fractional);
        print("Scaler: " << scaler);
    }

    float getPrice()
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
    Limit(float price) : price(Price(price))
    {
        orders = vector<Order>();
    }

    // Limit Functionalities
    void printCurrentOrders()
    {
        for (size_t i = 0; i < orders.size(); i++)
        {
            (orders[i].printOrders());
        }
    }
    void addOrder(Order new_order)
    {
        orders.push_back(new_order);
    }
};

struct OrderBook
{
    // OrderBook Attributes
    hashmap<Price, Limit> asks, bids;

    // // Constructors
    // OrderBook(){
    //     asks=hashmap<Price,Limit>();
    // }

    void addLimitOrder(Order newOrder){
        
    }

};
