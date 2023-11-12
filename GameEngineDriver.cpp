#include <iostream>
#include"GameEngine.h"

using namespace std;

void testGameStates() {

    GameEngine engineObj;
    engineObj.startup();
    //engineObj.play();

    system("pause");

   
}

void testMainGameLoop() {


    Continent* c1 = new Continent;
    c1->setContinentName("Europe");
    c1->setContinentBonus(10);

    Territory* t1 = new Territory("Cuba", c1);
    Territory* t2 = new Territory("Venezuela", c1);
    Territory* t3 = new Territory("Florida", c1);
    Territory* t4 = new Territory("Aruba", c1);

    Map map;
    map.continentList.push_back(c1);
    map.getTerritoryList().push_back(t1);
    map.getTerritoryList().push_back(t2);
    map.getTerritoryList().push_back(t3);

    Player* p1 = new Player;
    p1->setPlayerID("john");
    Player* p2 = new Player;
    p2->setPlayerID("mike");

    vector<Player*> allPlayers;
    allPlayers.push_back(p1);
    allPlayers.push_back(p2);

    t1->adjencyList.push_back(t2);
    t1->adjencyList.push_back(t3);
    t2->adjencyList.push_back(t1);
    t2->adjencyList.push_back(t3);
    t3->adjencyList.push_back(t1);
    t3->adjencyList.push_back(t2);

    p1->getTerritoryList().push_back(t1);
    p1->getTerritoryList().push_back(t2);
    p2->getTerritoryList().push_back(t3);
    p2->getTerritoryList().push_back(t4);

    t1->setTerritoryOwner(p1);
    t2->setTerritoryOwner(p1);
    t3->setTerritoryOwner(p2);
    t4->setTerritoryOwner(p2);


    GameEngine game;
    // game.setAllPlayers(allPlayers);
    // game.setSelectedMap(map);

    
    game.startupPhase();
    game.reinforcementPhase();
    game.issueOrdersPhase();

    
    






//Prove that player recieves the correct number of army units in the reinforcement phase (show different cases)
        //Play Game with 3 players: Case (# of territories owned / 3, rounded down) => each player has 8 territories which gets rounded to 2 when divided by 3 so they get the minimum which is 3 units each
        //Play Game with 2 players: Case (# of territories owned / 3, rounded down) => each player has 13 territories which gets rounded to 4 when divided by 2 so they get 4 units each
                                  //Case (Continent Bonus) => one of the players gets 2 more units because they own all territories on SouthWest which has a bonus value of 2                                                               

        //GameEngine game;
        //game.startupPhase();
        //game.reinforcementPhase();




//Prove a player will only issue deploy orders and no other kind of orders if they still have anmy units in their reinforcement pool
        //GameEngine game;
        //game.startupPhase();
        //game.reinforcementPhase();
        //game.issueOrdersPhase();


//Prove a player can issue advance orders to either defend or attack, based on the toAttack() and toDefend() lists
        //GameEngine game;
        //game.startupPhase();
        //game.reinforcementPhase();
        //game.issueOrdersPhase();

//prove a player can play cards to issue orders
        //GameEngine game;
        //game.startupPhase();
        //game.reinforcementPhase();
        //game.issueOrdersPhase();

//Prove a player that does not control any territory is removed from the game

//Prove the game ends when a single player controls all the territories




}
