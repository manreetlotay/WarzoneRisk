#include <iostream>
#include <string>
#include "LoggingObserver.h"

using namespace std;

class GameEngine : public ILoggable, public Subject
{
private:
    /* data */
    string* userInput;
    int* players; //number of players


public:
    GameEngine(); //default constructor
    ~GameEngine();
    string stringToLog() override;
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



};

//free function
void testGameStates();