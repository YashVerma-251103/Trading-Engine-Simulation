#include "../defines_macros/TradingPair.hpp"

struct Price
{
    // ? Attributes
    int integer, fractional, scaler = 100;
    float decimal;

    // ? Constructors
    Price()
    {
        // scaler = 100;
        decimal = -1.0f;
        integer = -1;
        fractional = 0;
    }a
    Price(float price)
    {
        // scaler = 100
        decimal = price;
        integer = (int)(price);
        fractional = (int)((price - integer) * scaler);
    }

    // ! Structure Utilities
    bool operator==(const Price &otherPrice) const
    {
        return (
            (integer == otherPrice.integer) &&
            (fractional == otherPrice.fractional) &&
            (decimal == otherPrice.decimal));
    }
    bool operator>(const Price &otherPrice) const
    {
        if (integer > otherPrice.integer)
            return true;
        else if (integer == otherPrice.integer)
            return (fractional > otherPrice.fractional);
        return false;
    }

    // ? Functional Utilities
    void printPrice() const
    {
        println("Price : " << decimal);
    }
    void printPartPrice() const
    {
        println("Integral : " << integer << " | Fractional : " << fractional);
    }

    float getPrice()
    {
        return decimal;
    }
    float getPartPrice()
    {
        return (float)((float)integer + ((float)fractional / (float)scaler));
    }
};

namespace std
{
    template <>
    struct hash<Price>
    {
        auto operator()(const Price &price) const
        {
            return ((Hash<int>()(price.integer)) ^ (Hash<int>()(price.fractional)) ^ (Hash<int>()(price.scaler)));
        }
    };

} // namespace std
