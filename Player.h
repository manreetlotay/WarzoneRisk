/*
IMEPLEMENTATION OF A WARZONE PLAYER
AUTHOR: Manreet Kaur Lotay (40202883)
*/

#pragma once

#include <string>
#include "Cards.h"
#include "Orders.h"
#include "Map.h"


class Player {

    private:  
        Hand* handOfCards;
        OrderList* orderList;
        vector<Territory*> territoryList;
        string playerID;
        int reinforcementPool;

    public:
        //constructor and destructor
        Player();
        ~Player();
        Player(Hand* handOfCards, OrderList* orderList, vector<Territory*> territoryList, string playerID);
        
        //copy constructor
        Player(const Player& ogPlayer);

        //Assignment operator overloader
        Player& operator = (const Player& player);

        //Stream insertion operator overloader
        friend std::ostream &operator << (std::ostream &output, Player &player);

        // required methods of a Player
        void issueOrder();
        vector<Territory*> toDefend();
        vector<Territory*> toAttack();

        //getters
        Hand* getHandOfCards();
        OrderList* getOrderList();
        vector<Territory*> getTerritoryList();
        string getPlayerID();
        int getReinforcementPool();

        //setters
        void setHand(Hand* newHandOfCards);
        void setTerritoryList(vector<Territory*> newTerritoryList);
        void setPlayerID(string newPlayerID);
        void setReinforcementPool(int newReinforcementPool);

        //Other
        void printTerritoryList(vector<Territory*> terrListToPrint);
        void addReinforcements(int armyUnits);
        void removeReinforcements(int armyUnits);
        void addOrderToOrderList(Order* order);
};

//free function declaration
void testPlayers();


