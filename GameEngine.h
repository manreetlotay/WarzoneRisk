#include <iostream>
#include <string>

#include "Player.h"

#include "LoggingObserver.h"

using namespace std;

class GameEngine : public ILoggable, public Subject
{
private:
    /* data */
    string* userInput;
    int* players; //number of players

        Deck* deck;
        vector <Player*> playerList;

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

        void startupPhase();
        void mainGameLoop();
        void reinforcementPhase();
        void issueOrdersPhase();
        void executeOrdersPhase();
};

//free function
void testGameStates();
void testMainGameLoop();