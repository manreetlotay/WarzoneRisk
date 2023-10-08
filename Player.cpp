#include "Player.h"
#include <iostream>

// default constructor
Player::Player() : handOfCards(nullptr), orderList(nullptr), territoryList(vector<Territory*>()){
}

//Parameterized Constructor
Player::Player(Hand* handOfCards, OrderList* orderList, vector<Territory*> territoryList)
    : handOfCards(handOfCards), orderList(orderList), territoryList(territoryList) {
}

 //destructor
 Player::~Player() {

    //Deallocation memory for handOfCards and orderList and preventing dangling pointers
    delete handOfCards;
    handOfCards = NULL;

    delete orderList;
    orderList = NULL;

    //deallocation memory for each Territory* in territoryList and clearing the list
    for (Territory* territory: territoryList) {
        delete territory;
    }
    territoryList.clear();
 }

 //copy constructor
 Player::Player(const Player& ogPlayer) {

    //if ogPlayer was instantiated using the parameterized constructor
     if ((ogPlayer.handOfCards != nullptr) && (ogPlayer.orderList != nullptr) && (!ogPlayer.territoryList.empty())) {
        this->handOfCards = new Hand(*(ogPlayer.handOfCards));
        this->orderList = new OrderList(*(ogPlayer.orderList));

        //deep copy each Territory from one list to the other
         for (Territory* territory: ogPlayer.territoryList) {
            this->territoryList.push_back(new Territory(*territory));
        }

    //if ogPlayer was instantiated using the default constructor
    } else {
        this->handOfCards = nullptr;
        this->orderList = nullptr;
        territoryList = vector<Territory*>();
    }
 }

 //assignment operator
 Player& Player::operator = (const Player& player) {

    //self assignment
    if (this == &player) {
        return *this; 
    }

    //clear memory
     delete handOfCards; 
     delete orderList; 

    //if player was instantiated using the parameterized constructor
    if ((player.handOfCards != nullptr) && (player.orderList != nullptr) && (!player.territoryList.empty())) {
        this->handOfCards = new Hand(*(player.handOfCards));
        this->orderList = new OrderList(*(player.orderList));

        //deep copy each Territory from one list to the other
        for (Territory* territory: player.territoryList) {
        this->territoryList.push_back(new Territory(*territory));
    }
    //if player was instantiated using the default constructor
    } else {
        this->handOfCards = nullptr;
        this->orderList = nullptr;
    }

    return *this;
 }

 //stream insertion operator overloader
 std::ostream &operator<<(std::ostream &output, Player &player) {

    Hand* handOfCards = player.getHandOfCards();
    OrderList* orderList = player.getOrderList();
    vector<Territory*> territoryList = player.getTerritoryList();

    //If player was instantiated using default constructor
    if ((handOfCards == nullptr) && (orderList == nullptr) && (territoryList.empty())) {
        output << "Player's Hand of Cards is empty" << std::endl;
        output << "Player's List of Orders is empty" << std::endl;
        output << "Player Does Not Own Any Territories" << std::endl;

    //If player was instantiated using parameterized constructor
    } else {
        //Print player's hand of cards
        output << "Player's Hand of Cards: " << std::endl;
            // Iterate through the cards in the player's hand and print them
            for (Card* card : handOfCards->hand) {
                card->Play();
            }

        output << "\n";

        //print player's list of orders
        output << "Player's List of Orders: " << std::endl;
            // Iterate through the order list and print each order's type
            for (int i = 0; i < orderList->get_order_list()->size(); i++) {
                output << "  " << orderList->get_order_list()->at(i)->getType() << std::endl;
            }

        //print player's list of territories
        output << "Player's List of Territories:" << std::endl;
            //Iterate through territoryList and print name of each Territory object
            for (Territory* territory : player.territoryList) {
                output << "Territory Name: " << territory->getTerritoryName() << std::endl;
                //other info about territory to print...
            }
    }

    return output;
}

 //getters
 Hand* Player::getHandOfCards() {
    return handOfCards;
 };

 OrderList* Player::getOrderList() {
    return orderList;
 };

 vector<Territory*> Player::getTerritoryList() {
    return territoryList;
 };

 //setters
 void Player::setHand(Hand* newHandOfCards) {
    handOfCards = newHandOfCards;
}

void Player::setTerritoryList(vector<Territory*> newTerritoryList) {
    territoryList = newTerritoryList;
}

//create Order object and add it to player's list of orders
void Player::issueOrder(Order* order) {
    if (orderList != nullptr && order != nullptr) {
        orderList->set_order_list(order);
    }
}

//Return List of territories to be defended by Player
vector<Territory*> Player::toDefend() {

    vector<Territory*> terrToDefend;

    // Check if the Player's territoryList is empty
    if (!territoryList.empty()) {

        //FOR NOW: Iterate through territoryList and if Territory has armies < 2, it need to be defended
        for (Territory* territory : territoryList) {
            if (territory->getNumOfArmies() < 2) {
                terrToDefend.push_back(territory);
            }
        }
    }

    return terrToDefend;
}

//Return List of territories to be attacked by Player
vector<Territory*> Player::toAttack() {

    vector<Territory*> terrToAttack;

    // Check if the Player's territoryList is empty
    if (!territoryList.empty()) {

        //FOR NOW: Iterate through territoryList and if Territory has armies >= 2, it need to be attacked
        for (Territory* territory : territoryList) {
            if (territory->getNumOfArmies() >= 2) {
                terrToAttack.push_back(territory);
            }
        }
    }

    return terrToAttack;
}

//Print Each Territory object's name and other info inside territoryList
void Player::printTerritoryList(vector<Territory*> terrListToPrint) {
    //Iterate through territoryList and print name of each Territory
     for (Territory* territory : terrListToPrint) {
        std::cout << territory->getTerritoryName() << std::endl;
    }
}




