#include "test_imports.hpp"

struct tests
{
    shPtr(Price) price = shObj(Price)(1000.0f);
    shPtr(Limit) limit = shObj(Limit)(price);

    // * Market Orders
    shPtr(Order) market_sell_order = shObj(Order)(92.9f,Ask);

    // * Bid 

};
