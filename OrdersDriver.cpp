#include "Orders.h"

using namespace std;



void testOrdersList()
{
    cout << "test OrderDriver...\n" << endl;
    OrderList anOrderList;

    Deploy deploy;
    Advance advance;
    Bomb bomb;
    Blockade blockade;
    Airlift airlift;
    Negotiate negotiate;

    anOrderList.set_order_list(&deploy);
    anOrderList.set_order_list(&advance);
    anOrderList.set_order_list(&advance);
    anOrderList.set_order_list(&blockade);
    anOrderList.set_order_list(&airlift);
    anOrderList.set_order_list(&negotiate);


    //print orderlist
    cout << "\n the orderlist contains: " << endl;
    for (int i = 0; i < anOrderList.get_order_list()->size(); i++) {
        cout <<"  "<< anOrderList.get_order_list()->at(i)->getType() << endl;
    }

    //delete an order
    anOrderList.remove(&deploy);

    //print orderlist
    cout << "\n the orderlist contains: " << endl;
    for (int i = 0; i < anOrderList.get_order_list()->size(); i++) {
        cout << "  " << anOrderList.get_order_list()->at(i)->getType() << endl;
    }

    //move an order
    anOrderList.move(0,4);
    //anOrderList.move(0, 5);
    anOrderList.move(0, 8);//invalid
    //print orderlist
    cout << "\n the orderlist contains: " << endl;
    for (int i = 0; i < anOrderList.get_order_list()->size(); i++) {
        cout << "  " << anOrderList.get_order_list()->at(i)->getType() << endl;
    }

}