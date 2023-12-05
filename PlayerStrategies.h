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
        bool gotAttacked = false;
        Player* p;

    public:
        //constructor and destructor
        PlayerStrategy(Player* p);
        virtual ~PlayerStrategy();

        //methods
        virtual void issueOrder() = 0;
        virtual vector<Territory*> toAttack() = 0;
        virtual vector<Territory*> toDefend() = 0;
        string getPlayerStrategy();
        void setAttacked(bool );
        bool getWasNeutralAttacked();
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

class BenevolentPlayerStrategy : public PlayerStrategy{

    public:
    BenevolentPlayerStrategy(Player* p);
    ~BenevolentPlayerStrategy();
    BenevolentPlayerStrategy(const BenevolentPlayerStrategy& otherObj):PlayerStrategy(otherObj){};
    

    //methods


    void issueOrder() override;
    vector<Territory*> toAttack() override;
    vector<Territory*> toDefend() override;

};
class NeutralPlayerStrategy : public PlayerStrategy {

public:
    NeutralPlayerStrategy(Player* p);
    ~NeutralPlayerStrategy();
    NeutralPlayerStrategy(const NeutralPlayerStrategy& otherObj):PlayerStrategy(otherObj){};
    
    //methods
    void issueOrder() override;
    vector<Territory*> toAttack() override;
    vector<Territory*> toDefend() override;

    //void setAttacked(bool);
    //bool getWasNeutralAttacked();

};

//free function declaration
void testPlayerStrategies();