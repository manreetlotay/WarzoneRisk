//
// Created by hengy on 11/9/2023.
//

#include "Orders.h"
#include "Player.h"

using namespace std;

void testOrderExecution() {
    // Create players, territories, and other necessary game elements
    Player* player1 = new Player;
    Player* player2 = new Player;
    Territory* t1 = new Territory("Quebec");
    Territory* t2 = new Territory("BC");

    // (1) Validate and execute each order
    // Example for an Advance order
    Advance advanceOrder(player1,10, t1, t2); // Sample parameters
    if (advanceOrder.validate()) {
        advanceOrder.execute();
        std::cout << "Advance order executed." << std::endl;
    } else {
        std::cout << "Advance order validation failed." << std::endl;
    }

    // (2) Transfer ownership on successful conquest
    // Check and demonstrate ownership transfer
    if (t2->getTerritoryOwner() == player1) {
        std::cout << "Ownership of territory transferred to Player 1." << std::endl;
    }

    // (3) Award card for conquering territory
    // Implement logic to award card and demonstrate it
    // ...

    // (4) Prevent attacks between players involved in negotiate order
    // Create and demonstrate negotiate order
    Negotiate negotiateOrder(player1, player2);
    negotiateOrder.execute();
    // Implement logic to demonstrate prevention of attacks
    // ...

    // (6) Demonstrate all orders can be issued and executed
    // Create and execute different types of orders to demonstrate this
    // ...

    std::cout << "Order execution tests completed." << std::endl;
}
int main() {
    testOrderExecution();
    return 0;
}