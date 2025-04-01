// * Import header file
#include "Price.hpp"

// * Structure for Order.
struct Order
{
    // ? Attributes
    float size;
    BuyOrSell type;

    // ? Constructors
    Order(float *order_size, BuyOrSell order_type)
    {
        assert(order_size != nullptr && *order_size > 0);

        size = *order_size;
        type = order_type;
    }
    Order(float order_size, BuyOrSell order_type)
    {
        assert(order_size > 0);

        size = order_size;
        type = order_type;
    }

    // ? Functional Utilities
    void printOrder()
    {
        println(size << ","<< (type ? "Ask":"Bid") << "\n");
    }
    bool isFilled(){
        return (size == 0.0f);
    }
};