#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Player.h"

using namespace std;

//class Player;
class Territory;

//Strategy Class
class PlayerStrategy {   

    protected:
        string strategyName;
        Player* p;

    public:
        //constructor and destructor
        PlayerStrategy(Player* p);
        virtual ~PlayerStrategy();

        //methods
        virtual void issueOrder() = 0;
        virtual vector<Territory*> toAttack() = 0;
        virtual vector<Territory*> toDefend() = 0;

};

//Concrete Strategy Classes

class HumanPlayerStrategy : public PlayerStrategy {
public:
    //Constructor and Destructor
    HumanPlayerStrategy(Player* p);
    ~HumanPlayerStrategy();

    //methods
    void issueOrder() override;
    vector<Territory*> toAttack() override;
    vector<Territory*> toDefend() override;

};

class AggressivePlayerStrategy : public PlayerStrategy {
public:
    //Constructor and Destructor
    AggressivePlayerStrategy(Player* p);
    ~AggressivePlayerStrategy();

    //methods
    void issueOrder() override;
    vector<Territory*> toAttack() override;
    vector<Territory*> toDefend() override;

};

class CheaterPlayerStrategy : public PlayerStrategy {
public:
    //Constructor and Destructor
    CheaterPlayerStrategy(Player* p);
    ~CheaterPlayerStrategy();

    // methods
    void issueOrder() override;
    vector<Territory*> toAttack() override;
    vector<Territory*> toDefend() override;

};

//free function declaration
void testPlayerStrategies();