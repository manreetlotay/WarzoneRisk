#include <iostream>
#include <string>
using namespace std;

class GameEngine
{
private:
    /* data */
    string* userInput;
    int* players; //number of players


public:
    GameEngine(); //default constructor
    ~GameEngine();
    void startup();
    //void play();
    void loadMap(string&);
    void setCommand();
    string getCommand();
    //void verifyCommand();
    void validateMap(string&);
    void addPlayer(string&);
    void assignReinforcement(string&);
    void endExecOrders(string&);
    void issueOrders(string&);
    void executeOrders(string&);
    bool win();

    void mainGameLoop();
    void reinforcementPhase();
    void issueOrdersPhase();
    void executeOrdersPhase();

};

//free function
void testGameStates();
void testMainGameLoop();