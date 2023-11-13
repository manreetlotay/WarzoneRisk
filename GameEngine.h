#include <iostream>
#include <string>
#include <vector>
//#include "Map.h"
#include "Player.h"
using namespace std;

//class Player;

class GameEngine
{
private:
    /* data */
    string* userInput;
    int *playersCounter; //number of players
    string* currentState;

    Map* mapObj;
    vector<Player*> players;

public:
    GameEngine(); //default constructor
   
    ~GameEngine();
    void startup();
    //void play();
    void loadMap(string);
    void setCommand();
    void setInput();
    string getInput();
    //void verifyCommand();
    void validateMap(string&);
    void addPlayer(string,string);
    void assignReinforcement(string&);
    void endExecOrders(string&);
    void issueOrders(string&);
    void executeOrders(string&);
    bool win();
    //void startupPhase();
    void gameStart();

};

//free function
void testGameStates();