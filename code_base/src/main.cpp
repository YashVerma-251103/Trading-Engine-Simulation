#include "./matching_engine/OrderBooks.hpp"







int main()
{
    float SB1 = 4.5f;
    float SBP1 = 65.32f;
    Price SBP1P = Price(SBP1);
    Order B1 = Order(&SB1, Bid);
    float SB2 = 9.48f;
    float SBP2 = 78.51f;
    Price SBP2P = Price(SBP2);
    Order B2 = Order(&SB2, Bid);

    float SA1 = 7.5f;
    float SAP1 = 94.65f;
    Price SAP1P = Price(SAP1);
    Order A1 = Order(&SA1, Ask);
    float SA2 = 98.37f;
    float SAP2 = 98.24f;
    Price SAP2P = Price(SAP2);
    Order A2 = Order(&SA2, Ask);

    OrderBook OB = OrderBook();
    OB.addLimitOrder(&B1,&SBP1P);
    OB.addLimitOrder(&B2,&SBP2P);
    OB.addLimitOrder(&A1,&SAP1P);
    OB.addLimitOrder(&A2,&SAP2P);

    OB.printOrders();


    return 0;
}