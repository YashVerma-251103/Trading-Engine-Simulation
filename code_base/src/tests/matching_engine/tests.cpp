#include "../test_imports.hpp"


struct tests
{
    void limit_order_single_fill(){
        Price price = Price(1000.0f);
        Limit limit = Limit(&price);

        
        Order buy_limit_order = Order(100.0f,Bid);
        limit.addOrder(&buy_limit_order);

        Order market_sell_order = Order(92.0f,Ask);
        limit.fillOrder(&market_sell_order); 

        limit.printCurrentOrders();
    }
    void limit_order_multi_fill(){
        Price price = Price(1000.0f);
        Limit limit = Limit(&price);

        
        Order buy_limit_order_a = Order(100.0f,Bid);
        Order buy_limit_order_b = Order(100.0f,Bid);
        limit.addOrder(&buy_limit_order_a);
        limit.addOrder(&buy_limit_order_b);

        Order market_sell_order = Order(192.0f,Ask);
        limit.fillOrder(&market_sell_order); 

        assert(market_sell_order.isFilled()==true);
        assert(buy_limit_order_a.isFilled()==true);
        assert(buy_limit_order_b.isFilled()==false);
        
        

        limit.printCurrentOrders();
    }
    
};







int main(){
    tests t = tests();
    // t.limit_order_single_fill();
    t.limit_order_multi_fill();

}