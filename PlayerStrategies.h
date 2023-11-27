#pragma once
#include <string>
#include <vector>

using namespace std;

class Player;
class Territory;

//Strategy Class
class PlayerStrategy {   

    private:
        string strategyName;
        Player* p;

    public:
        //constructor and destructor
        PlayerStrategy();
        ~PlayerStrategy();

        //methods
        virtual void issueOrder() = 0;
        virtual vector<Territory*> toAttack() = 0;
        virtual vector<Territory*> toDefend() = 0;

};

//Concrete Strategy Classes

class HumanPlayerStrategy : public PlayerStrategy {

    //Constructor and Destructor
    HumanPlayerStrategy();
    ~HumanPlayerStrategy();

    //methods
    void issueOrder();
    vector<Territory*> toAttack();
    vector<Territory*> toDefend();

};

class AggressivePlayerStrategy : public PlayerStrategy {

    //Constructor and Destructor
    AggressivePlayerStrategy();
    ~AggressivePlayerStrategy();

    //methods
    void issueOrder();
    vector<Territory*> toAttack();
    vector<Territory*> toDefend();

};