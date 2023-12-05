#include <iostream>
#include <string>
#include <random>
#include <cstdlib> 


#include "Player.h"

using namespace std;

class GameEngine {

    private:
        string* userInput;
        int* players;

        Map selectedMap;
        vector<Player*> allPlayers;
        int numDistributedTerritories;
        int numPlayers;
        vector<string> playerNames;
        vector<string> mapNames;
        string selectedMapName;
        Deck* deck;

    public:
        GameEngine(); 
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


        void startupPhase();
        void mainGameLoop();
        void reinforcementPhase();
        void issueOrdersPhase();
        void executeOrdersPhase();
        void removePlayers();
        Player* checkWinner();
        //For Demo
        void setSelectedMap(const Map& map);
        void setAllPlayers(const vector<Player*>& players);
        void initializeGame(Map& map, vector<Player*>& players);
      
};

//free function
void testGameStates();
void testMainGameLoop();
