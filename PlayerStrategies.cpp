    #include "PlayerStrategies.h"

    //===================PLAYER STRATEGY=====================

    // Constructor
    PlayerStrategy::PlayerStrategy(Player* p) : p(p) {}

    // Destructor
    PlayerStrategy::~PlayerStrategy() {}






    //====================HUMAN PLAYER========================

    // Constructor
    HumanPlayerStrategy::HumanPlayerStrategy(Player* p) : PlayerStrategy(p) {
        cout << "I am a Human Player" << endl;
    }

    // Destructor
    HumanPlayerStrategy::~HumanPlayerStrategy() {
        delete p;
        p = NULL;
    }


    vector <Territory*> HumanPlayerStrategy::toAttack() {
        cout << "Human Player toAttack" << endl;

        vector<Territory*> terrToAttack;

        //Loop through the Player's territoryList
        for (Territory* territory : this->p->getTerritoryList()) {

            //Get adjacent territories of the current territory
            vector<Territory*> adjacentTerritories = territory->adjencyList;

            //Loop through the adjacent territories
            for (Territory* adjacentTerritory : adjacentTerritories) {

                //Check if the adjacent territory is not owned by the player
                    if (adjacentTerritory->getTerritoryOwner() != p) {
                        //Prevent duplicates in terrToAttack
                        if (find(terrToAttack.begin(), terrToAttack.end(), adjacentTerritory) == terrToAttack.end()) {
                            terrToAttack.push_back(adjacentTerritory);
                        }
                    }
                }
            }

        return terrToAttack;

    }

    vector <Territory*> HumanPlayerStrategy::toDefend() {
        cout << "Human Player toDefend" << endl;

        vector<Territory*> terrList = this->p->getTerritoryList();

        //initialize terrToDefend with the Player's territoryList
         vector<Territory*> terrToDefend(terrList.begin(), terrList.end());

        //sort terrToDefend vector in ascending order of NumOfArmies on Territory
        sort(terrToDefend.begin(), terrToDefend.end(), [](Territory* a, Territory* b) {
            return a->getNumOfArmies() < b->getNumOfArmies();
        });

        return terrToDefend;
    }

    void HumanPlayerStrategy::issueOrder() {
        cout << "Human Player issueOrder" << endl;

        vector<Territory*> toDefend = this->toDefend();
        vector<Territory*> toAttack = this->toAttack();
        bool deployedAll = false;

        //Ensure the player still has territories to defend (still in the game)
        if (toDefend.empty() || p->getReinforcementPool() <= 0) {
            return;
        }

        //=====================================DEPLOY=========================================//

        //Display territories to defend and the number of armies on each territory
        cout << this->p->getPlayerID() << ",  HERE ARE THE TERRITORIES YOU NEED TO DEFEND:\n" << endl;

        for (int i = 0; i < toDefend.size(); i++) {
            cout << i + 1 << ". TERRITORY: "  << toDefend[i]->getTerritoryName() << endl; //" (ARMIES: " << toDefend[i]->getNumOfArmies() << ")\n";
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
                    cout << "SELECT THE NUMBER OF TROOPS YOU WISH TO DEPLOY ON " << targetTerritory->getTerritoryName() << " (NUMBER OF ARMY UNITS AVAILABLE: " << this->p->getReinforcementPool() << "): " << endl;
                    cin >> numDeployed;

                    if (numDeployed < 0 || numDeployed > this->p->getReinforcementPool()) {
                        cout << "**Invalid number of army units. Please try again.**\n" << endl;
                    }
                } while (numDeployed < 0 || numDeployed > this->p->getReinforcementPool());

                //Create a Deploy order
                //Deploy* deploy = new Deploy(this, numDeployed, targetTerritory);
                // // Add the order to the player's order list
                //addOrderToOrderList(deploy);

                // Update the number of armies in the target territory
                targetTerritory->setNumOfArmies(targetTerritory->getNumOfArmies() + numDeployed);

                // Remove deployed army units from the reinforcement pool
                this->p->removeReinforcements(numDeployed);

                // Check if there are no more armies left to deploy
                if (this->p->getReinforcementPool() <= 0) {
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



    //==========================================ADVANCE=======================================/

    char ynAdvanceOrder;
        cout << this->p->getPlayerID() << ", DO YOU WISH TO ISSUE ADVANCE ORDERS (Y/N)?" << endl;
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
                        cout << i + 1 << ". Territory Name: " << toDefend[i]->getTerritoryName() << endl; //"   Armies: " << toDefend[i]->getNumOfArmies() << endl;
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
                    //fromTerritory->setNumOfArmies(fromTerritory->getNumOfArmies() - numUnitsToAdvance);

                    cout << "\nADVANCE ORDER #" << orderNumber << " ISSUED: " << numUnitsToAdvance << " units advanced from " << fromTerritory->getTerritoryName() << " to " << toTerritory->getTerritoryName() << "." << endl;
                
                
                } else { // Advance units to an enemy territory

                    // Display the territories to defend
                    cout << "HERE IS A LIST OF YOUR TERRITORIES:\n" << endl;
                    for (int i = 0; i < toDefend.size(); i++) {
                        cout << i + 1 << ". Territory Name: " << toDefend[i]->getTerritoryName() << endl; //"      Armies: " << toDefend[i]->getNumOfArmies() << endl;
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

        //======================================DRAW CARD===============================//

        cout << "\n" << endl;

        // Check if the player has any cards in their hand
        if (this->p->getHandOfCards() == nullptr || this->p->getHandOfCards()->hand.empty()) {
            cout << this->p->getPlayerID() << ", YOU DO NOT HAVE ANY CARDS IN YOUR HANDS.\n" << endl;
            return;
        }

        cout << "HERE ARE THE CARDS IN YOUR HAND:" << endl;
            for (int i = 0; i < this->p->getHandOfCards()->hand.size(); i++) {
                cout << i + 1 << ". " << *(this->p->getHandOfCards())->hand[i] << endl;
            }

            int cardChoice;
            do {
                cout << "\nCHOOSE THE CARD YOU WANT TO USE (1-" << this->p->getHandOfCards()->hand.size() << "): " << endl;;
                cin >> cardChoice;
                cin.ignore();

                if (cardChoice < 1 || cardChoice > this->p->getHandOfCards()->hand.size()) {
                    cout << "**Invalid card choice. Please try again.**" << endl;
                }
            } while (cardChoice < 1 || cardChoice > this->p->getHandOfCards()->hand.size());

            Card* selectedCard = this->p->getHandOfCards()->hand[cardChoice - 1];

            //Use the selected card based on its type
            Territory* targetTerritory = nullptr;
            Territory* sourceTerritory = nullptr;
            Player* targetPlayer = nullptr;
            int numArmies = 0;
            int movedArmies = 0;
            cout << "\n" << endl;
            switch (selectedCard->getValue()) {
                case 'B':
                    //Bomb Order
                    targetTerritory = toAttack.front();
                    //order = new Bomb(this, targetTerritory);
                    //addOrderToOrderList(&order);
                    cout << "ISSUE BOMB ORDER ON " << targetTerritory->getTerritoryName() << ", OWNED BY " << targetTerritory->getTerritoryOwner()->getPlayerID() << endl;
                    break;
                case 'R':
                    //this->reinforcementPool += 10;
                    this->p->addReinforcements(10);
                    cout << "YOU HAVE PLAYED THE REINFORCEMENT CARD! YOU HAVE BEEN REINFORCED WITH 10 ARMY UNITS" << endl;  
                    break;
                case 'L':
                    //Blockade Order
                    targetTerritory = toDefend.front();
                    //order = new Blockade(this, targetTerritory);
                    //addOrderToOrderList(&order);
                    cout << "ISSUE BLOCKADE ORDER ON " << targetTerritory->getTerritoryName() << ", OWNED BY " << targetTerritory->getTerritoryOwner()->getPlayerID() << endl;
                    break;
                case 'A':
                    //Airlift order
                    sourceTerritory = toDefend.back();
                    targetTerritory = toDefend.front();

                    if (sourceTerritory->getNumOfArmies() <= 0) {
                        movedArmies = 1;
                    }

                    numArmies = (rand() % movedArmies) + 1;
                    //order = new Airlift(this, numArmies, sourceTerritory, targetTerritory);
                    //addOrderToOrderList(&order);
                    cout << "ISSUE AIRLIFT ORDER FROM " << sourceTerritory->getTerritoryName() << " TO " << targetTerritory->getTerritoryName() << ", OWNED BY " << this->p->getPlayerID() << endl;

                    break;
                case 'D':
                    //Negotiate Order
                    targetPlayer = toAttack.front()->getTerritoryOwner();
                    //order = new Negotiate(this, targetPlayer);
                    //addOrderToOrderList(&order);
                    cout << "ISSUE NEGOTIATE ORDER ON PLAYER " << targetPlayer->getPlayerID() << endl;
                    break;
                default:
                    cout << "**Invalid card type. Please try again.**" << endl;
                    break;
            }

            // Remove the used card from the player's hand
            this->p->getHandOfCards()->hand.erase(this->p->getHandOfCards()->hand.begin() + cardChoice - 1);

    }







    //====================AGGRESSIVE PLAYER=====================
    // Constructor
    AggressivePlayerStrategy::AggressivePlayerStrategy(Player* p) : PlayerStrategy(p) {
        cout << "I am an Aggressive Player" << endl;
    }

    // Destructor
    AggressivePlayerStrategy::~AggressivePlayerStrategy() {
        delete p;
        p = NULL;
    }

    vector <Territory*> AggressivePlayerStrategy::toAttack() {
        cout << "Aggressive Player toAttack" << endl;

         vector<Territory*> terrToAttack;

        //Loop through the Player's territoryList
        for (Territory* territory : this->p->getTerritoryList()) {

            //Get adjacent territories of the current territory
            vector<Territory*> adjacentTerritories = territory->adjencyList;

            //Loop through the adjacent territories
            for (Territory* adjacentTerritory : adjacentTerritories) {

                //Check if the adjacent territory is not owned by the player
                    if (adjacentTerritory->getTerritoryOwner() != p) {
                        //Prevent duplicates in terrToAttack
                        if (find(terrToAttack.begin(), terrToAttack.end(), adjacentTerritory) == terrToAttack.end()) {
                            terrToAttack.push_back(adjacentTerritory);
                        }
                    }
                }
            }

        // Sort terrToAttack vector in ascneding order of NumOfArmies on Territory
        sort(terrToAttack.begin(), terrToAttack.end(), [](Territory* a, Territory* b) {
            return a->getNumOfArmies() < b->getNumOfArmies();  //front = Territory with lowest numOfArmies  //back = Territory with highest numOfArmies
        });

        return terrToAttack;

    }


    vector <Territory*> AggressivePlayerStrategy::toDefend() {
        cout << "Aggressive Player toDefend" << endl;

        vector<Territory*> terrList = this->p->getTerritoryList();

        //initialize terrToDefend with the Player's territoryList
         vector<Territory*> terrToDefend(terrList.begin(), terrList.end());

        //sort terrToDefend vector in ascending order of NumOfArmies on Territory
        sort(terrToDefend.begin(), terrToDefend.end(), [](Territory* a, Territory* b) {
            return a->getNumOfArmies() < b->getNumOfArmies();
        });

        return terrToDefend; //front = Territory with lowest numOfArmies  //back = Territory with highest numOfArmies

    }


    void AggressivePlayerStrategy::issueOrder() {

        //====Computer Player that always deployes and advances armies to its strong territories, then advances armies from its strongest Territory to the weakest enemy Territory, then uses any aggressive card====//
        cout << "Aggressive Player issueOrder" << endl;

        vector<Territory*> toDefend = this->toDefend();
        vector<Territory*> toAttack = this->toAttack();
        Territory* myStrongestTerritory = toDefend.back();
	    Territory* weakestEnemyTerritory = toAttack.front();
        Territory* strongestEnemyTerritory = toAttack.back();
        bool deployedAll = false;

        //Ensure the player still has territories to defend (still in the game)
        if (toDefend.empty() || p->getReinforcementPool() <= 0) {
            return;
        }

        //========================================DEPLOY=====================================//
            // Deploys all its armies to its strongest Territory
        int numDeployed = this->p->getReinforcementPool();
        //Deploy* deploy = new Deploy(this, numDeployed, myStrongestTerritory);
        //addOrderToOrderList(deploy);

        // Update the number of armies in the target territory
        myStrongestTerritory->setNumOfArmies(myStrongestTerritory->getNumOfArmies() + numDeployed);

        // Remove deployed army units from the reinforcement pool
        this->p->removeReinforcements(numDeployed);

        cout << "\n" << this->p->getPlayerID() << " deployed " << numDeployed << " army units to " << myStrongestTerritory->getTerritoryName() << endl;



        //========================================ADVANCE=====================================//
            // Advance all army units to strongest Territory if other territories than the strongest have any army units, else advance units from strongest territory to enemy territory
        Territory* fromTerritory = nullptr;
        Territory* toTerritory = nullptr;
        int unitsAdvanced = 0;
        
        for (int i = 0; i < toDefend.size(); i++) {
            if (toDefend[i]->getNumOfArmies() != 0 && toDefend[i] != myStrongestTerritory) {
                Territory* fromTerritory = toDefend[i];
                unitsAdvanced = fromTerritory->getNumOfArmies();
                myStrongestTerritory->setNumOfArmies(myStrongestTerritory->getNumOfArmies() + unitsAdvanced);
                // Advance* advanceOrder = new Advance(this, unitsAdvanced, fromTerritory, myStrongestTerritory); (line above gets removed b/c part of order execution)
                // addOrderToOrderList(advanceOrder);
                fromTerritory->setNumOfArmies(fromTerritory->getNumOfArmies() - unitsAdvanced); //this line is also part of order execution
            }
            else {
                unitsAdvanced = myStrongestTerritory->getNumOfArmies();
                weakestEnemyTerritory->setNumOfArmies(weakestEnemyTerritory->getNumOfArmies() + unitsAdvanced);
                // Advance* advanceOrder = new Advance(this, unitsAdvanced, myStrongestTerritory, weakestEnemyTerritory); (line above gets removed b/c part of order execution)
                // addOrderToOrderList(advanceOrder);
                myStrongestTerritory->setNumOfArmies(myStrongestTerritory->getNumOfArmies() - unitsAdvanced); //this line is also part of order execution 
            }
        }



        //===========================================CARD=======================================//
        
        // Check if the player has any cards in their hand
        if (this->p->getHandOfCards() == nullptr || this->p->getHandOfCards()->hand.empty()) {
            return;
        }


        // Loop through player's handOfCards and use each card
        for (int i = 0; i < this->p->getHandOfCards()->hand.size(); i++) {
            //Use the selected card based on its type
            Territory* targetTerritory = nullptr;
            Territory* sourceTerritory = nullptr;
            Player* targetPlayer = nullptr;
            int numArmies = 0;
            int movedArmies = 0;
            
            //use the card agressively based on its type
            switch(this->p->getHandOfCards()->hand[i]->getValue()) {
                case 'B':
                    //Bomb Order
                    targetTerritory = weakestEnemyTerritory;
                    //order = new Bomb(this, targetTerritory);
                    //addOrderToOrderList(&order);
                    cout << "PLAYING BOMB CARD ON " << targetTerritory->getTerritoryName() << ", OWNED BY " << targetTerritory->getTerritoryOwner()->getPlayerID() << endl;
                    break;
                case 'R':
                    //this->reinforcementPool += 10;
                    this->p->addReinforcements(10);
                    cout << "PLAYING REINFORCEMENT CARD" << endl;  
                    break;
                case 'L':
                    //Blockade Order
                    targetTerritory = toDefend.front();
                    //order = new Blockade(this, targetTerritory);
                    //addOrderToOrderList(&order);
                    cout << "PLAYING BLOCKADE CARD ON " << targetTerritory->getTerritoryName() << ", OWNED BY " << targetTerritory->getTerritoryOwner()->getPlayerID() << endl;
                    break;
                case 'A':
                    //Airlift order
                    sourceTerritory = toDefend.back();
                    targetTerritory = myStrongestTerritory;

                    if (sourceTerritory != targetTerritory) {
                        if (sourceTerritory->getNumOfArmies() <= 0) {
                        movedArmies = 1;
                        }

                        numArmies = (rand() % movedArmies) + 1;
                        //order = new Airlift(this, numArmies, sourceTerritory, targetTerritory);
                        //addOrderToOrderList(&order);
                        cout << "PLAYING AIRLIFT CARD FROM " << sourceTerritory->getTerritoryName() << " TO " << targetTerritory->getTerritoryName() << ", OWNED BY " << this->p->getPlayerID() << endl;
                    }
                    
                    break;
                case 'D':
                    //Negotiate Order
                    targetPlayer = strongestEnemyTerritory->getTerritoryOwner();
                    //order = new Negotiate(this, targetPlayer);
                    //addOrderToOrderList(&order);
                    cout << "PLAYING NEGOTIATE CARD ON PLAYER " << targetPlayer->getPlayerID() << endl;
                    break;
                default:
                    cout << "**Invalid card type. Please try again.**" << endl;
                    break;

            }

            // Remove all used cards from the player's hand
            this->p->getHandOfCards()->hand.clear();

        }

    }