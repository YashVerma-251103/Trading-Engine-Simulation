#include "../test_imports.hpp"


struct tests
{
    
    Price price = Price(1000.0f);
    Limit limit = Limit(&price);

    // * Market orders
    Order market_sell_order = Order(92.0f,Ask);
    
    // * Bid Limit orders
    Order buy_limit_order = Order(100.0f,Bid);
    Order buy_limit_order_a = Order(100.0f,Bid);
    Order buy_limit_order_b = Order(100.0f,Bid);
    
    // * Ask Limit orders
    Order sell_limit_order = Order(10.0f,Ask);
    Price price_sell = Price(500);
    Order sell_limit_order_a = Order(10.0f,Ask);
    Price price_sell_a = Price(100);
    Order sell_limit_order_b = Order(10.0f,Ask);
    Price price_sell_b = Price(200);
    Order sell_limit_order_c = Order(10.0f,Ask);
    Price price_sell_c = Price(300);



    void limit_order_single_fill(){
        
        limit.addOrder(&buy_limit_order);
        limit.fillOrder(&market_sell_order); 

        limit.printCurrentOrders();
    }
    void limit_order_multi_fill(){

        limit.addOrder(&buy_limit_order_a);
        limit.addOrder(&buy_limit_order_b);

        Order market_sell_order = Order(192.0f,Ask);
        limit.fillOrder(&market_sell_order); 

        assert(market_sell_order.isFilled()==true);
        assert(buy_limit_order_a.isFilled()==true);
        assert(buy_limit_order_b.isFilled()==false);

        limit.printCurrentOrders();
    }
    void orderbook_fill_order(){
        OrderBook ob = OrderBook();
        OB_fill_order_asks(&ob);
    }
    void OB_fill_order_asks(OrderBook* ob){
        ob->addLimitOrder(&sell_limit_order,&price_sell);
        ob->addLimitOrder(&sell_limit_order_a,&price_sell_a);
        ob->addLimitOrder(&sell_limit_order_b,&price_sell_b);
        ob->addLimitOrder(&sell_limit_order_c,&price_sell_c);

        ob->printAskOrders();
    }
};







int main(){
    tests t = tests();
    // t.limit_order_single_fill();
    // t.limit_order_multi_fill();

    t.orderbook_fill_order();

}