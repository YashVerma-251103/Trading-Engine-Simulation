#include "./imports.h"
// #include <iostream>



int main()
{

    // std::cout << (int)((10.1585f - (int)10.1585f) *100000) << std::endl;

    // Price price = Price(50.5);
    // print(price.get_price());
    // price.print_price();

    Limit limit = Limit(64.39);
    Order Buy_order = Order(5.5,Bid);
    limit.add_order(Buy_order);

    limit.print_current_orders();

    return 0;
}