//
// Created by hengy on 11/9/2023.
//

#include "Orders.h"
#include "Player.h"
#include "GameEngine.h"
#include "Map.h"

using namespace std;

void testOrderExecution() {
//    // Create players, territories, and other necessary game elements
//    Player* player1 = new Player;
//    Player* player2 = new Player;
//    Territory* t1 = new Territory("Quebec");
//    Territory* t2 = new Territory("BC");
//
//    // (1) Validate and execute each order
//    // Example for an Advance order
//    Advance advanceOrder(player1,10, t1, t2); // Sample parameters
//    if (advanceOrder.validate()) {
//        advanceOrder.execute();
//        std::cout << "Advance order executed." << std::endl;
//    } else {
//        std::cout << "Advance order validation failed." << std::endl;
//    }
//
//    // (2) Transfer ownership on successful conquest
//    // Check and demonstrate ownership transfer
//    if (t2->getTerritoryOwner() == player1) {
//        std::cout << "Ownership of territory transferred to Player 1." << std::endl;
//    }
//
//    // (3) Award card for conquering territory
//    // Implement logic to award card and demonstrate it
//    // ...
//
//    // (4) Prevent attacks between players involved in negotiate order
//    // Create and demonstrate negotiate order
//    Negotiate negotiateOrder(player1, player2);
//    negotiateOrder.execute();
//    // Implement logic to demonstrate prevention of attacks
//    // ...
//
//    // (6) Demonstrate all orders can be issued and executed
//    // Create and execute different types of orders to demonstrate this
//    // ...
//
//    std::cout << "Order execution tests completed." << std::endl;
    // Setup
    Continent* c1 = new Continent;
    c1->setContinentName("Europe");
    c1->setContinentBonus(10);

    Territory* t1 = new Territory("Cuba", c1);
    Territory* t2 = new Territory("Venezuela", c1);
    Territory* t3 = new Territory("Florida", c1);


    Map map;
    map.continentList.push_back(c1);
    map.getTerritoryList().push_back(t1);
    map.getTerritoryList().push_back(t2);
    map.getTerritoryList().push_back(t3);

    t1->adjencyList.push_back(t2);
    t2->adjencyList.push_back(t1);

    Player* player = new Player;
    Player* enemy = new Player;
    player->setPlayerID("Bob");
    enemy->setPlayerID("John");
    player->getTerritoryList().push_back(t1);
    player->getTerritoryList().push_back(t2);
    enemy->getTerritoryList().push_back(t3);


    OrderList ordersList;
    ordersList.addOrder(new Deploy(player, 5, t1));
    ordersList.addOrder(new Advance(player, 10, t1, t3));
    ordersList.addOrder(new Bomb(player, t3));
    ordersList.addOrder(new Airlift(player, 7, t1, t2));
    ordersList.addOrder(new Blockade(player, t1));
    ordersList.addOrder(new Negotiate(player, enemy));



    // Show the OrderList
    std::cout << "===== " << "Original orders list: " << ordersList << " =====" << std::endl;
    for (const auto &order : *ordersList.get_order_list()) {
        std::cout << *order << std::endl;
        std::cout << std::boolalpha << "Order is valid: " << order->validate() << std::endl;
        order->execute();
        std::cout << std::endl;
    }

    // Show the OrderList after moving an order from index 1 to index 4
    ordersList.move(1, 4);
    std::cout << "===== " << "Orders list after moving an order: " << ordersList << " =====" << std::endl;
    for (const auto &order : *ordersList.get_order_list())
    {
        std::cout << *order << std::endl;
    }

    // Show the OrderList after deleting an order at index 5
    ordersList.remove(reinterpret_cast<Order *>(1));
    std::cout << "\n===== " << "Orders list after deleting an order: " << ordersList << " =====" << std::endl;
    for (const auto &order : *ordersList.get_order_list())
    {
        std::cout << *order << std::endl;
    }

    std::cout << "\nChecking Adjacency between territories:" << std::endl;
//    if (map.isADJ(t1->getTerritoryName(), t2->getTerritoryName())) {
//        std::cout << "Territory1 and Territory2 are adjacent." << std::endl;
//    } else {
//        std::cout << "Territory1 and Territory2 are not adjacent." << std::endl;
//    }



    delete t1;
    delete t2;
    delete t3;

}
int main() {
    testOrderExecution();
    return 0;
}