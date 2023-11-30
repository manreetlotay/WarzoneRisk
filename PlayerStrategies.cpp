    #include "PlayerStrategies.h"

    //===================PLAYER STRATEGY=====================

    // Constructor
    PlayerStrategy::PlayerStrategy(Player* p) : p(p) {}

    // Destructor
    PlayerStrategy::~PlayerStrategy() {}






    //====================HUMAN PLAYER==================

    // Constructor
    HumanPlayerStrategy::HumanPlayerStrategy(Player* p) : PlayerStrategy(p) {
        cout << "I am a Human Player" << endl;
    }

    // Destructor
    HumanPlayerStrategy::~HumanPlayerStrategy() {}


    vector <Territory*> HumanPlayerStrategy::toAttack() {
        cout << "Human Player toAttack" << endl;

    }

    vector <Territory*> HumanPlayerStrategy::toDefend() {
        cout << "Human Player toDefend" << endl;

        p->getTerritoryList();

         // //initialize terrToDefend with the Player's territoryList
    // vector<Territory*> terrToDefend(territoryList.begin(), territoryList.end());

    // //sort terrToDefend vector in ascending order of NumOfArmies on Territory
    // std::sort(terrToDefend.begin(), terrToDefend.end(), [](Territory* a, Territory* b) {
    //     return a->getNumOfArmies() < b->getNumOfArmies();
    // });

    // return terrToDefend;
    
    }

    void HumanPlayerStrategy::issueOrder() {
        cout << "Human Player issueOrder" << endl;
    }




    //====================AGGRESSIVE PLAYER==================
    // Constructor
    AggressivePlayerStrategy::AggressivePlayerStrategy(Player* p) : PlayerStrategy(p) {
        cout << "I am an Aggressive Player" << endl;
    }

    // Destructor
    AggressivePlayerStrategy::~AggressivePlayerStrategy() {
        // Cleanup for Aggressive Player Strategy
    }

    vector <Territory*> AggressivePlayerStrategy::toAttack() {
        cout << "Aggressive Player toAttack" << endl;

    }

    vector <Territory*> AggressivePlayerStrategy::toDefend() {
        cout << "Aggressive Player toDefend" << endl;
    }

    void AggressivePlayerStrategy::issueOrder() {
        cout << "Aggressive Player issueOrder" << endl;
    }