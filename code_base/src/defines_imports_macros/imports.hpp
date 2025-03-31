#include <iostream>

// Testing Libs
#include <assert.h>
// #define NDEBUG

// STLs included
#include <vector>
#include <unordered_map>
#include <string>
#include <memory>

// Namespace defines
#define size_t std::size_t
#define vector std::vector
#define Hash std::hash
#define hashmap std::unordered_map
#define string std::string
#define spair std::pair
#define shptr(Obj) std::make_shared<Obj>


// utility macros
#define print(obj) (std::cout << obj << std::endl)
#define print_ne(obj) (std::cout << obj)

// Value enums and respective macros
enum BuyOrSell
{
    // Options
    Bid = 0,
    Ask = 1
};
#define BuyOrSell enum BuyOrSell

// Defines for orders for better understanding
#define filled true
#define not_filled false
// #define max_first true
// #define min_first false
bool min_first = false, max_first = true;


// #define initial_order_book_price 0.0f
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
    bool operator>(const Price &otherPrice) const
    {
        if (integral > otherPrice.integral)
        {
            return true;
        }
        else if (integral == otherPrice.integral)
        {
            return (fractional > otherPrice.fractional);
        }
        return false;
    }
    bool operator>=(const Price &otherPrice) const
    {
        if (integral > otherPrice.integral)
        {
            return true;
        }
        else if (integral == otherPrice.integral)
        {
            return (fractional >= otherPrice.fractional);
        }
        return false;
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