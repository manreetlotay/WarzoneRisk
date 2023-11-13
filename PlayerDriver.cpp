/*
IMEPLEMENTATION OF A WARZONE PLAYER
AUTHOR: Manreet Kaur Lotay (40202883)
*/

#include "Player.h"
#include <iostream>

using namespace std;

//jsut for me
void mainGameLoop();
void reinforcementPhase();
        void issueOrdersPhase();
        void executeOrdersPhase();


void testPlayers() {

    //Testing for Player begins (ASSIGNMENT 1)
    std::cout << "TESTING THE FEATURES OF A PLAYER: " << std::endl;

    //Create a Deck of Card Objects, a Hand* of Card objects and populate the Hand* with repeated calls to the Draw() method
    Deck d(10);
    Hand* handOfCards = new Hand;
    for (int i = 0; i < 5; ++i) {
        d.Draw(handOfCards->hand);
    }

    //Create a OrderList* object and a couple Order objects
    OrderList* orderList = new OrderList;
    Deploy deploy;
    Advance advance;
    Bomb bomb;
    Blockade blockade;
    Airlift airlift;
    Negotiate negotiate;

    //Create Continent objects
    Continent* Asia = new Continent("Asia", 5);
    Continent* Europe = new Continent("Europe", 3);

    //Create Territory objects with references to Continent objects
    Territory* England = new Territory("England", Europe);
    Territory* France = new Territory("France", Europe);
    Territory* Malaysia = new Territory("Malaysia", Asia);
    Territory* India = new Territory("India", Asia);

    //Create territoryList and add Territory* objects to it
    vector<Territory*> territoryList;
    territoryList.push_back(England);
    territoryList.push_back(France);
    territoryList.push_back(Malaysia);
    territoryList.push_back(India);

    //Set the Number of armies for different Territory* objects
    England->setNumOfArmies(3);
    France->setNumOfArmies(1);  //deDefend
    Malaysia->setNumOfArmies(10);
    India->setNumOfArmies(4);

    //Instantiate a Player object with the default constructor
    Player* playerDefault = new Player;

    //Testing Default constructor
    std::cout << "The following player was instantiated using the default constructor: " << std::endl;
    std::cout << *playerDefault << std::endl;

    //Instantiate a Player object with the parameterized constructor using handOfCards and orderList
    Player* player = new Player(handOfCards, orderList, territoryList, "manreet");

    //Testing issueOrder() method
    player->addOrderToOrderList(&deploy);
    player->addOrderToOrderList(&advance);
    player->addOrderToOrderList(&airlift);

    //Testing parameterized constructor
    std::cout << "The following player was instantiated using the parameterized constructor: " << std::endl;
    std::cout << *player << std::endl;

    //Testing toDefend() and toAttack() method
    std::cout << "Territories to Attack:" << std::endl;
    player->printTerritoryList(player->toAttack());

    std::cout << "Territories to Defend:" << std::endl;
    player->printTerritoryList(player->toDefend());

    //Testing copy constructor of player
    std::cout << "Testing copy constructor: " << std::endl;
    Player* playerCopy = new Player(*player);
    std::cout << *playerCopy << std::endl;

    //Testing assignment operator of player
    std::cout << "Testing assignment operator" << std::endl;
    Player* playerAssignment = new Player(); //instantiated as default
    playerAssignment = player;               //now: assigned with parameterized Player             
    std::cout << *playerAssignment << std::endl;  

    //prevent memory leaks and dangling pointers (calls destructor of Player class and deletes handOfCards, orderList and territoryList)
    delete playerDefault;
    delete playerCopy;
    delete player;
    delete playerAssignment;

    playerDefault = nullptr;
    player = nullptr;
    playerCopy = nullptr;
    playerAssignment = nullptr;

}



