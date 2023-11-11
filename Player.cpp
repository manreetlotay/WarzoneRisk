/*
IMEPLEMENTATION OF A WARZONE PLAYER
AUTHOR: Manreet Kaur Lotay (40202883)
*/

#include "Player.h"
#include <iostream>
#include <algorithm> 
#include <set>

// default constructor
Player::Player() : handOfCards(nullptr), orderList(nullptr), territoryList(vector<Territory*>()), playerID("default"){}


//Parameterized Constructor
Player::Player(Hand* handOfCards, OrderList* orderList, vector<Territory*> territoryList, string playerID)
    : handOfCards(handOfCards), orderList(orderList), territoryList(territoryList), playerID(playerID) {}

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

    //copying handOfCards
    if(ogPlayer.handOfCards != nullptr) {   
        this->handOfCards = new Hand(*(ogPlayer.handOfCards));
    }
    else {
        this->handOfCards = nullptr;
    }

    //copying orderList
    if(ogPlayer.orderList != nullptr) {
        this->orderList = new OrderList(*(ogPlayer.orderList));  
    }
    else {
        this->orderList = nullptr;
    }

    //copying territoryList
    if(!ogPlayer.territoryList.empty()) {
        //deep copy each Territory from one list to the other
         for (Territory* territory: ogPlayer.territoryList) {
            this->territoryList.push_back(new Territory(*territory));
        }
    }
    else {
        //instantiate new territoryList
        territoryList = vector<Territory*>();
    }

    //copying playerID
    this->playerID = ogPlayer.playerID;
 }

 //assignment operator
 Player& Player::operator = (const Player& player) {

    //self assignment
    if (this == &player) {
        return *this; 
    }

    //copying handOfCards
    if(player.handOfCards != nullptr) {   
        this->handOfCards = new Hand(*(player.handOfCards));
    }
    else {
        this->handOfCards = nullptr;
    }

    //copying orderList
    if(player.orderList != nullptr) {
        this->orderList = new OrderList(*(player.orderList));  
    }
    else {
        this->orderList = nullptr;
    }

    //copying territoryList
    if(!player.territoryList.empty()) {
        //deep copy each Territory from one list to the other
         for (Territory* territory: player.territoryList) {
            this->territoryList.push_back(new Territory(*territory));
        }
    }
    else {
        //instantiate new territoryList
        territoryList = vector<Territory*>();
    }

    //copying playerID
    this->playerID = player.playerID;

    return *this;
 }

 //stream insertion operator overloader
 std::ostream &operator<<(std::ostream &output, Player &player) {

    Hand* handOfCards = player.getHandOfCards();
    OrderList* orderList = player.getOrderList();
    vector<Territory*> territoryList = player.getTerritoryList();
    string playerID = player.getPlayerID();

    output << "Player's Information: " << std::endl;
    output << "\n";

    //print player's id
    output << "Player ID: " << playerID << std::endl;

    //print player's handOfCards message if its empty
    if (handOfCards == nullptr) {
        output << "Player's Hand of Cards is empty" << std::endl;
    }
    else {
        //Print player's hand of cards
        output << "Player's Hand of Cards: " << std::endl;
            // Iterate through the cards in the player's hand and print them
            for (Card* card : handOfCards->hand) {
                card->Play();
            }
    }

    //print player's orderList message if its empty
    if (orderList == nullptr) {
        output << "Player's List of Orders is empty" << std::endl;
    }
    else {
        //print player's list of orders
        output << "Player's List of Orders: " << std::endl;
            // Iterate through the order list and print each order's type
            for (int i = 0; i < orderList->get_order_list()->size(); i++) {
                output << "  " << orderList->get_order_list()->at(i)->getType() << std::endl;
            }
    }

    //print player's territoryList message if its empty
    if(territoryList.empty()) {
        output << "Player Does Not Own Any Territories" << std::endl;
    }
    else {
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

 string Player::getPlayerID() {
    return playerID;
 }

 int Player::getReinforcementPool() {
    return reinforcementPool;
 }

 //setters
 void Player::setHand(Hand* newHandOfCards) {
    handOfCards = newHandOfCards;
}

void Player::setTerritoryList(vector<Territory*> newTerritoryList) {
    territoryList = newTerritoryList;
}

void Player::setPlayerID(string newPlayerID) {
    playerID = newPlayerID;
}

void Player::setReinforcementPool(int newReinforcementPool) {
    reinforcementPool = newReinforcementPool;
}

void Player::addReinforcements(int armyUnits) {
    this->reinforcementPool += armyUnits;
}

void Player::removeReinforcements(int armyUnits) {
    this->reinforcementPool -= armyUnits;
}

void Player::addOrderToOrderList(Order* order) {
    orderList->set_order_list(order);
}

//create Order object and add it to player's list of orders
void Player::issueOrder() {

    vector<Territory*> toDefend = this->toDefend();
    vector<Territory*> toAttack = this->toAttack();
    bool deployedAll = false;

    //Ensure the player still has territories to defend
    if (toDefend.empty() || this->reinforcementPool <= 0) {
        return;
    }

    //********DEPLOY*********//

    //Display territories to defend and the number of armies on each territory
    cout << playerID << ",  HERE ARE THE TERRITORIES YOU NEED TO DEFEND:\n" << endl;

    for (int i = 0; i < toDefend.size(); i++) {
        cout << i + 1 << ". TERRITORY: "  << toDefend[i]->getTerritoryName() << setw(25) << " (ARMIES: " << toDefend[i]->getNumOfArmies() << ")\n";
    }
    cout << endl;

    while (!deployedAll) {
        //cout << "You currently have " << this->reinforcementPool << " army units in your reinforcement pool.\n" << endl;
        deployedAll = true; 

        // Loop through the territories to defend
        for (int i = 0; i < toDefend.size(); i++) {
            Territory* targetTerritory = toDefend[i];

            // Prompt the user to enter the number of army units to deploy
            int numDeployed;
            do {
                cout << "SELECT THE NUMBER OF TROOPS YOU WISH TO DEPLOY FOR " << targetTerritory->getTerritoryName() << " (NUMBER OF ARMY UNITS AVAILABLE: " << this->reinforcementPool << "): " << endl;
                cin >> numDeployed;

                if (numDeployed < 0 || numDeployed > this->reinforcementPool) {
                    cout << "**Invalid number of army units. Please try again.**\n" << endl;
                }
            } while (numDeployed < 0 || numDeployed > this->reinforcementPool);

            // // Create a Deploy order
            // Deploy* deployOrder = new Deploy(this, numDeployed, targetTerritory);
            // // Add the order to the player's order list
            // addOrderToOrderList(deployOrder);

            // Update the number of armies in the target territory
            targetTerritory->setNumOfArmies(targetTerritory->getNumOfArmies() + numDeployed);

            // Remove deployed army units from the reinforcement pool
            this->reinforcementPool -= numDeployed;

            // Check if there are no more armies left to deploy
            if (this->reinforcementPool <= 0) {
                deployedAll = true; // All armies have been deployed
                break;
            } else {
                deployedAll = false; // Some armies remain in the reinforcement pool
            }
        }

        if (deployedAll) {
            cout << "GREAT JOB! ALL YOUR ARMY UNITS HAVE BEEN DEPLOYED!\n" << endl;
        } else {
            cout << "YOU STILL HAVE ARMY UNITS IN YOUR REINFORCEMENT POOL. YOU NEED TO DEPLOY YOUR ARMIES TO DEFEND YOUR TERRITORIES. PLEASE HAVE ANOTHER LOOK AT THE TERRITORIES YOU NEED TO DEFEND AND DEPLOY YOUR ARMIES UNITS.\n" << endl;
        }
    }



//***********ADVANCE***********************

 char ynAdvanceOrder;
    cout << playerID << "DO YOU WISH TO ISSUE ADVANCE ORDERS (Y/N)?" << endl;
    cin >> ynAdvanceOrder;
    cin.ignore();

    if (ynAdvanceOrder == 'y' || ynAdvanceOrder == 'Y') {
        int numAdvanceOrders;
        cout << "\n" << endl;
        do {
            cout << "HOW MANY ADVANCE ORDERS WOULD YOU LIKE TO ISSUE (1-5)? " << endl;
            cin >> numAdvanceOrders;
            cin.ignore(); // Consume the newline character

            if (numAdvanceOrders < 1 || numAdvanceOrders > 5) {
                cout << "**Invalid number of advance orders. Must be between 1 and 5.**" << endl;
            }
        } while (numAdvanceOrders < 1 || numAdvanceOrders > 5);

        cout << "\n" << endl;

        for (int orderNumber = 1; orderNumber <= numAdvanceOrders; orderNumber++) {
            cout << "ADVANCE ORDER #" << orderNumber << ":\n" << endl;

            int choice;
            do {
                cout << "CHOOSE THE TYPE OF ADVANCE ORDER:" << endl;
                cout << "1. ADVANCE UNITS TO YOUR TERRITORY" << endl;
                cout << "2. ADVANCE UNITS TO AN ENEMY TERRITORY\n" << endl;
                cin >> choice;
                cin.ignore(); // Consume the newline character
            } while (choice != 1 && choice != 2);

            if (choice == 1) { // Advance units to your territory
                // Display the territories to defend
                cout << "HERE IS A LIST OF YOUR TERRITORIES:\n" << endl;
                for (int i = 0; i < toDefend.size(); i++) {
                    cout << i + 1 << ". Territory Name: " << toDefend[i]->getTerritoryName() << "   Armies: " << toDefend[i]->getNumOfArmies() << endl;
                }
                int fromChoice;
                do {
                    cout << "CHOOSE THE SOURCE TERRITORY (1-" << toDefend.size() << "): " << endl;
                    cin >> fromChoice;
                    cin.ignore(); // Consume the newline character

                    if (fromChoice < 1 || fromChoice > toDefend.size()) {
                        cout << "**Invalid territory choice. Please try again.**" << endl;
                    }
                } while (fromChoice < 1 || fromChoice > toDefend.size() || toDefend[fromChoice-1]->getNumOfArmies() == 0);

                // Select the 'from' territory
                Territory* fromTerritory = toDefend[fromChoice - 1];


                int toChoice;
                do {
                    cout << "CHOOSE THE TARGET TERRITORY (1-" << toDefend.size() << "): " << endl;
                    cin >> toChoice;
                    cin.ignore(); // Consume the newline character

                    if (toChoice < 1 || toChoice > toDefend.size()) {
                        cout << "**Invalid territory choice. Please try again.**" << endl;
                    }
                } while (toChoice < 1 || toChoice > toDefend.size());

                // Select the 'to' territory
                Territory* toTerritory = toDefend[toChoice - 1];

                int numUnitsToAdvance;
                do {
                    cout << "ENTER THE NUMBER OF ARMY UNITS TO ADVANCE (1-" << fromTerritory->getNumOfArmies() << "): ";
                    cin >> numUnitsToAdvance;
                    cin.ignore(); // Consume the newline character

                    if (numUnitsToAdvance < 1 || numUnitsToAdvance > fromTerritory->getNumOfArmies()) {
                        cout << "**Invalid number of army units to advance. Please try again.**" << endl;
                    }
                } while (numUnitsToAdvance < 1 || numUnitsToAdvance > fromTerritory->getNumOfArmies());

                // Advance* advanceOrder = new Advance(this, numUnitsToAdvance, fromTerritory, toTerritory);
                // addOrderToOrderList(advanceOrder);
                // fromTerritory->setNumOfArmies(fromTerritory->getNumOfArmies() - numUnitsToAdvance);

                cout << "\nADVANCE ORDER #" << orderNumber << " ISSUED: " << numUnitsToAdvance << " units advanced from " << fromTerritory->getTerritoryName() << " to " << toTerritory->getTerritoryName() << "." << endl;
            
            
            } else { // Advance units to an enemy territory

                // Display the territories to defend
                cout << "HERE IS A LIST OF YOUR TERRITORIES:\n" << endl;
                for (int i = 0; i < toDefend.size(); i++) {
                    cout << i + 1 << ". Territory Name: " << toDefend[i]->getTerritoryName() << "      Armies: " << toDefend[i]->getNumOfArmies() << endl;
                }


                int fromChoice;
                int enemyChoice;

                do {
                    cout << "CHOOSE THE SOURCE TERRITORY (1-" << toDefend.size() << "): " << endl;
                    cin >> fromChoice;
                    cin.ignore(); // Consume the newline character

                    if (fromChoice < 1 || fromChoice > toDefend.size()) {
                        cout << "**Invalid territory choice. Please try again.**" << endl;
                    }
                } while (fromChoice < 1 || fromChoice > toDefend.size() || toDefend[fromChoice-1]->getNumOfArmies() == 0);

                // Select the source 'from' territory
                Territory* fromTerritory = toDefend[fromChoice - 1];

                cout << "HERE IS A LIST OF ENEMY TERRITORIES TO ATTACK:\n" << endl;
                for (int i = 0; i < toAttack.size(); i++) {
                    cout << i + 1 << ". Territory Name: " << toAttack[i]->getTerritoryName() << "     Owner: " << toAttack[i]->getTerritoryOwner()->getPlayerID() << endl;
                }

                do {
                    cout << "CHOOSE AN ENEMY TERRITORY TO ATTACK (1-" << toAttack.size() << "): " << endl;
                    cin >> enemyChoice;
                    cin.ignore(); // Consume the newline character

                    if (enemyChoice < 1 || enemyChoice > toAttack.size()) {
                        cout << "**Invalid territory choice. Please try again.**" << endl;
                    }
                } while (enemyChoice < 1 || enemyChoice > toAttack.size());

                // Select the target enemy territory
                Territory* toTerritory = toAttack[enemyChoice - 1];

                int numUnitsToAdvance;

                do {
                    cout << "ENTER THE NUMBER OF UNITS TO ADVANCE (1-" << fromTerritory->getNumOfArmies() << "): " << endl;
                    cin >> numUnitsToAdvance;
                    cin.ignore(); // Consume the newline character

                    if (numUnitsToAdvance < 1 || numUnitsToAdvance > fromTerritory->getNumOfArmies()) {
                        cout << "**Invalid number of units to advance. Please try again.**" << endl;
                    }
                } while (numUnitsToAdvance < 1 || numUnitsToAdvance > fromTerritory->getNumOfArmies());

                // Advance* advanceOrder = new Advance(this, numUnitsToAdvance, fromTerritory, toTerritory);
                // addOrderToOrderList(advanceOrder);
                // fromTerritory->setNumOfArmies(fromTerritory->getNumOfArmies() - numUnitsToAdvance);

                cout << "\nADVANCE ORDER #" << orderNumber << " ISSUED: " << numUnitsToAdvance << " units advanced from " << fromTerritory->getTerritoryName() << " to " << toTerritory->getTerritoryName() << "." << endl;
            }
        }
    }

    //*************************DRAW CARD*******************

    // Check if the player has any cards in their hand
    if (handOfCards == nullptr || handOfCards->hand.empty()) {
        cout << playerID << ", you don't have any cards in your hand. Ending your order phase." << endl;
        return;
    }

    cout << "Here are the cards in your hand:" << endl;
        for (int i = 0; i < handOfCards->hand.size(); i++) {
            cout << i + 1 << ". " << *handOfCards->hand[i] << endl;
        }

        int cardChoice;
        do {
            cout << "Choose the card you want to use (1-" << handOfCards->hand.size() << "): ";
            cin >> cardChoice;
            cin.ignore();

            if (cardChoice < 1 || cardChoice > handOfCards->hand.size()) {
                cout << "Invalid card choice. Please try again." << endl;
            }
        } while (cardChoice < 1 || cardChoice > handOfCards->hand.size());

        Card* selectedCard = handOfCards->hand[cardChoice - 1];

        //Play the Card
        // Use the selected card based on its type
        switch (selectedCard->getValue()) {
            case 'B':
                // Implement the Bomb card logic here
                break;
            case 'R':
                // Implement the Reinforcement card logic here  
                break;
            case 'L':
                // Implement the Blockade card logic here
                break;
            case 'A':
                // Implement the Airlift card logic here
                break;
            case 'D':
                // Implement the Diplomacy card logic here
                break;
            default:
                cout << "**Invalid card type. Please try again.**" << endl;
                break;
        }


         // Remove the used card from the player's hand
        handOfCards->hand.erase(handOfCards->hand.begin() + cardChoice - 1);
    
}

//Return List of territories to be defended by Player
vector<Territory*> Player::toDefend() {

    //initialize terrToDefend with the Player's territoryList
    vector<Territory*> terrToDefend(territoryList.begin(), territoryList.end());

    //sort terrToDefend vector in ascending order of NumOfArmies on Territory
    std::sort(terrToDefend.begin(), terrToDefend.end(), [](Territory* a, Territory* b) {
        return a->getNumOfArmies() < b->getNumOfArmies();
    });

    return terrToDefend;

}

//Return List of territories to be attacked by Player
vector<Territory*> Player::toAttack() {

    vector<Territory*> terrToAttack;

    //Loop through the Player's territoryList
    for (Territory* territory : territoryList) {

        //Get adjacent territories of the current territory
        vector<Territory*> adjacentTerritories = territory->adjencyList;

        //Loop through the adjacent territories
        for (Territory* adjacentTerritory : adjacentTerritories) {

            //Check if the adjacent territory is not owned by the player
                if (adjacentTerritory->getTerritoryOwner() != this) {
                    //Prevent duplicates in terrToAttack
                    if (find(terrToAttack.begin(), terrToAttack.end(), adjacentTerritory) == terrToAttack.end()) {
                        terrToAttack.push_back(adjacentTerritory);
                    }
                }
            }
        }

	return terrToAttack;
}

//Print Each Territory object's name and other info inside territoryList
void Player::printTerritoryList(vector<Territory*> terrListToPrint) {
    //Iterate through territoryList and print name of each Territory
     for (Territory* territory : terrListToPrint) {
        std::cout << territory->getTerritoryName() << ", ";
    }
}




