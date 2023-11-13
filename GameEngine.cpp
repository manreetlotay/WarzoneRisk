#include"GameEngine.h"
#include <string>
#include <vector>

/*
commands to implement:
loadmap
validatemap
addplayer
assigncountries
issueorder
endexecorders
execorder
win
play
*/


//Initialize variables
        // Map selectedMap;
        // vector<Player*> allPlayers;
        // int numDistributedTerritories = 0;
        // int numPlayers;
        // vector<string> playerNames;
        // vector<string> mapNames = { "maps/Canada.map", "maps/Caribbean.map" };
        // string selectedMapName;

GameEngine::GameEngine() {
    
    // userInput = new string("");
    // players = new int(0);
    numDistributedTerritories = 0;
    numPlayers = 0;
    selectedMapName = "";
    mapNames = { "maps/Canada.map", "maps/Caribbean.map" };
    selectedMap = Map();


    userInput = new string("");
    players = new int(0);
    LogObserver* ob1 = new LogObserver();
    Attach(ob1);


}

GameEngine::~GameEngine()
{
}

void GameEngine::loadMap(string& uInput) {
    int errCounter = 0; //Counter for number of wrong command entries
    bool flag = true;
    while (uInput != "loadmap")
    {
        errCounter++;


        cout << "\nERROR! Invalid command" << endl;
        setCommand();

        if (errCounter == 4) {
            cout << "ERROR! Invalid command" << endl;
            cout << "Too many attempts, terminating session" << endl;
            exit(0);

        }

    }
    cout << "\nSTATE:Map Loaded" << endl;
    Notify(this);
    cout << "Would you like to load map again? (yes/no)" << endl;
    cin >> uInput;
    while (flag = true)
    {
        if (uInput == "no") {
            flag = false;
            break;
        }
        if (uInput == "yes") {
            cout << "\nSTATE:Map Loaded" << endl;
            cout << "Would you like to load map again? (yes/no)" << endl;
            cin >> uInput;
        }
        else {
            cout << "ERROR! Invalid command" << endl;
            cout << "Would you like to load map again? (yes/no)" << endl;
            cin >> uInput;
        }

    }

}
void GameEngine::validateMap(string& uInput) {
    int errCounter = 0;
    bool flag = true;
    while (uInput != "validatemap")
    {
        errCounter++;


        cout << "\nERROR! Invalid command" << endl;
        setCommand();

        if (errCounter == 4) {
            cout << "ERROR! Invalid command" << endl;
            cout << "Too many attempts, terminating session" << endl;
            exit(0);

        }

    }
    cout << "\nSTATE:Map Validated" << endl;
    Notify(this);
}

void GameEngine::addPlayer(string& uInput) {

    int errCounter = 0;
    bool flag = true;
    while (uInput != "addplayer")
    {
        errCounter++;


        cout << "\nERROR! Invalid command" << endl;
        setCommand();

        if (errCounter == 4) {
            cout << "ERROR! Invalid command" << endl;
            cout << "Too many attempts, terminating session" << endl;
            exit(0);

        }

    }
    *players += 1;
    cout << "\nSTATE: " << *players << " Players added" << endl;

    cout << "Would you like to add another player? (yes/no)" << endl;
    cin >> uInput;
    while (flag = true)
    {
        if (uInput == "no") {
            flag = false;
            break;
        }
        if (uInput == "yes") {
            *players += 1;
            cout << "\nSTATE: " << *players << " Players added" << endl;
            cout << "Would you like to add another player? (yes/no)" << endl;
            cin >> uInput;
        }
        else {
            cout << "ERROR! Invalid command" << endl;
            cout << "Would you like to add another player? (yes/no)" << endl;
            cin >> uInput;
        }

    }
}

void GameEngine::assignReinforcement(string& uInput) {
    int errCounter = 0;
    bool flag = true;
    while (uInput != "assigncountries")
    {
        errCounter++;


        cout << "\nERROR! Invalid command" << endl;
        setCommand();

        if (errCounter == 4) {
            cout << "ERROR! Invalid command" << endl;
            cout << "Too many attempts, terminating session" << endl;
            exit(0);

        }

    }
    cout << "\nSTATE:Assign Reinforcement" << endl;

}

void GameEngine::issueOrders(string& uInput) {

    int errCounter = 0;
    bool flag = true;
    while (uInput != "issueorder")
    {
        errCounter++;


        cout << "\nERROR! Invalid command" << endl;
        setCommand();

        if (errCounter == 4) {
            cout << "ERROR! Invalid command" << endl;
            cout << "Too many attempts, terminating session" << endl;
            exit(0);

        }

    }

    cout << "\nSTATE:Issue Orders" << endl;

    cout << "Would you like to issue another order? (yes/no)" << endl;
    cin >> uInput;
    while (flag = true)
    {
        if (uInput == "no") {
            flag = false;
            break;
        }
        if (uInput == "yes") {

            cout << "\nSTATE:Issue Orders" << endl;
            cout << "Would you like to issue another order? (yes/no)" << endl;
            cin >> uInput;
        }
        else {
            cout << "ERROR! Invalid command" << endl;
            cout << "Would you like to issue another order? (yes/no)" << endl;
            cin >> uInput;
        }

    }
}

void GameEngine::executeOrders(string& uInput) {

    int errCounter = 0;
    bool flag = true;
    while (uInput != "endissueorders")
    {
        errCounter++;


        cout << "\nERROR! Invalid command" << endl;
        setCommand();

        if (errCounter == 4) {
            cout << "ERROR! Invalid command" << endl;
            cout << "Too many attempts, terminating session" << endl;
            exit(0);

        }

    }

    cout << "\nSTATE:Execute Orders" << endl;

    cout << "Would you like to execute another order? (yes/no)" << endl;
    cin >> uInput;
    while (flag = true)
    {
        if (uInput == "no") {
            flag = false;
            break;
        }
        if (uInput == "yes") {

            cout << "\nSTATE:Execute Orders" << endl;
            cout << "Would you like to execute another order? (yes/no)" << endl;
            cin >> uInput;
        }
        else {
            cout << "ERROR! Invalid command" << endl;
            cout << "Would you like to execute another order? (yes/no)" << endl;
            cin >> uInput;
        }

    }
}
void GameEngine::endExecOrders(string& uInput) {
    int errCounter = 0;
    bool flag = true;
    while (uInput != "endexecorders")
    {
        errCounter++;


        cout << "\nERROR! Invalid command" << endl;
        setCommand();

        if (errCounter == 4) {
            cout << "ERROR! Invalid command" << endl;
            cout << "Too many attempts, terminating session" << endl;
            exit(0);

        }

    }
    cout << "\nSTATE:Assign Reinforcement" << endl;
}
bool GameEngine::win() {
    cout << "\nSTATE:Win" << endl;

    bool flag = true;
    do {
        setCommand();
        if (*userInput == "end") {
            flag = false;//Whenever flag is false, the while loop will stop
            return true;


        }if (*userInput == "play") {
            flag = false;
            return false;
        }if (!(*userInput == "end" || *userInput == "play")) {
            flag = true;
            cout << "ERROR! Invalid command" << endl;

        }
    } while (flag);


}
//void GameEngine::play() {
//
//	bool isWin = false;
//    bool flag = false;
//    assignReinforcement(*userInput);
//
//	while (isWin != true) {
//
//        //endExecOrders(*userInput);
//		setCommand();
//		issueOrders(*userInput);
//		setCommand();
//		executeOrders(*userInput);
//        
//        do {
//            setCommand();
//
//            if (*userInput == "endexecorders") {
//                flag = false;
//                endExecOrders(*userInput);
//
//            }
//            else if (*userInput == "win") {
//                flag = false;
//                isWin = true;
//
//            }
//            else if(!(*userInput == "endexecorders" || *userInput == "win")){
//                flag = true;
//                cout << "ERROR! Invalid command" << endl;
//               
//            }
//
//        } while (flag);
//        
//
//	}
//    win();
//
//
//}

void GameEngine::startup() {
    bool again = true;
    bool isEnd;
    while (again == true)
    {
        cout << "Welcome to Warzone!" << endl;
        cout << "STATE:Game Start" << endl;


        setCommand();

        loadMap(*userInput);

        setCommand();

        validateMap(*userInput);

        setCommand();

        addPlayer(*userInput);

        setCommand();

        bool isWin = false;
        bool flag = false;
        assignReinforcement(*userInput);

        while (isWin != true) {


            setCommand();
            issueOrders(*userInput);
            setCommand();
            executeOrders(*userInput);

            do {
                setCommand();

                if (*userInput == "endexecorders") {
                    flag = false;
                    endExecOrders(*userInput);

                }
                else if (*userInput == "win") {
                    flag = false;
                    isWin = true;//This will end the the isWin while loop

                }
                else if (!(*userInput == "endexecorders" || *userInput == "win")) {
                    flag = true;//When flag is true, the do-while will continue to loop
                    cout << "ERROR! Invalid command" << endl;

                }

            } while (flag);


        }
        isEnd = win();
        if (isEnd == true) {
            again = false; //This will end the top most while loop
            cout << "\nThe game has now ended" << endl;
            cout << "Good bye" << endl;

        }
        if (isEnd == false) {
            again = true;
        }

    }

    delete userInput;
    userInput = NULL;

}

void GameEngine::setCommand() {

    cout << "\nEnter Command: " << endl;
    cin >> *userInput;

}

string GameEngine::getCommand() {
    return *userInput;

}


void GameEngine::startupPhase() {

        //Welcome the user to Warzone
        cout << "===================================================================================================================" << endl;
        cout << "| WELCOME TO THE WORLD OF WARZONE, where strategy and wit reign supreme!                                           |" << endl;
        cout << "| Get ready to conquer your way to victory on this interconnected battlefield, one move at a time!                 |" << endl;
        cout << "===================================================================================================================\n" << endl;
        
        //Let the user choose a map and validate it
        while (true) {
            cout << "WARRIORS, THE TIME HAS COME TO MAKE A CRUCIAL DECISION. PLEASE SELECT A MAP.\n" << endl;
            for (int i = 0; i < mapNames.size(); i++) {
                cout << i + 1 << ". " << mapNames[i] << endl;
            }

            int choice;
            cin >> choice;

            if (choice >= 1 && choice <= mapNames.size()) {
                selectedMap = Map();
                selectedMapName = mapNames[choice - 1];
                selectedMap.mapLoader(selectedMapName);
                selectedMap.Validate();

                if (selectedMap.checkContinentConnections() && selectedMap.checkTerritoryConnections()) {
                    cout << "Map '" << selectedMapName << "' has been selected." << endl;
                    break;
                } else {
                    cout << "\nAH, IT APPEARS THAT THE PATH YOU'VE CHOSEN IS NOT ONE WE CAN TRAVERSE. LET'S TRY ANOTHER ROUTE, SHALL WE? PLEASE SELECT A VALID MAP TO CONTINUE YOUR JOURNEY.\n" << endl;
                }
            } else {
                cout << "\nAH, IT APPEARS THAT YOU'VE MADE THE WRONG CHOICE. PLEASE SELECT A VALID MAP TO CONTINUE YOUR JOURNEY.\n" << endl;
            }
        }

        cout << "\nFANTASTIC CHOICE! YOUR MAP HAS BEEN SUCCESSFULLY LOADED AND IS NOW READY FOR YOU TO EMBARK ON YOUR CONQUEST.\n" << endl;
        cout << "TAKE A MOMENT TO SURVEY THE TERRITORIES WHERE YOU'LL BE WAGING YOUR EPIC BATTLES.\n" << endl;

        //Display Territories to players
        selectedMap.showTerritories();
        cout << "\n";
        cout << "THE MAP YOU'VE LOADED CONSISTS OF A TOTAL OF " << selectedMap.getTerritoryList().size() << " TERRITORIES." << endl;
        
        // Prompt the user to add players to the game
        while (true) {
            cout << "\nIT IS NOW TIME TO CHOOSE YOUR ALLIES. YOU HAVE THE OPTION TO INVITE BETWEEN 2 AND 6 PLAYERS TO JOIN THE BATTLE. PLEASE SELECT A VALID NUMBER OF PLAYERS:\n";
            cin >> numPlayers;

            if (numPlayers >= 2 && numPlayers <= 6) {
                break;
            } else {
                cout << "\nOOPS! IN WARZONE, WE'RE LIMITED TO 2 TO 6 PLAYERS. PLEASE CHOOSE A VALID NUMBER OF COMRADES TO RALLY.\n" << endl;
            }
        }

        //Prompt user to enter names for each player
        cout << "\nGREAT! NOW THAT YOU'VE RALLIED YOUR FORCES, IT'S TIME TO BESTOW UNIQUE TITLES UPON EACH WARRIOR IN YOUR ARMY. CHOOSE A NAME FOR EVERY PLAYER, AND LET THEIR LEGEND BEGIN!\n" << endl;
        for (int i = 0; i < numPlayers; i++) {
            string playerName;
            cout << "PLEASE ENTER A NAME FOR PLAYER " << i + 1 << ": ";
            cin >> playerName;
            playerNames.push_back(playerName);
        }

        cout << "\nGREAT JOB! THOSE ARE SOME FANTASTIC NAMES FOR YOUR BATTLE-HARDENED COMRADES.\n" << endl;

        //Store players in allPayers
        for (int i = 0; i < numPlayers; i++) {
            Player* newPlayer = new Player();
            newPlayer->setPlayerID(playerNames[i]);
            allPlayers.push_back(newPlayer);
        }

        cout << "\nWARRIORS, YOU HAVE ALL BEEN GRANTED YOUR FAIR SHARE OF TERRITORIES. SURVEY THE LANDS UNDER YOUR DOMINION AND THOSE THAT STAND AS THE REALMS OF YOUR FOES.\n" << endl;

        //Assign territories to players 
        vector<Territory*> territories = selectedMap.getTerritoryList();

        //Shuffle the territories randomly
        std::random_device rd;
        std::mt19937 g(rd());
        random_shuffle(territories.begin(), territories.end());

        //Set armies on territory to 0 initially
        for (Territory* terr: territories) {
            terr->setNumOfArmies(0);
        }

        int territoriesPerPlayer = territories.size() / numPlayers;

        for (int i = 0; i < numPlayers; i++) {
            vector<Territory*> playerTerritories(territories.begin() + i * territoriesPerPlayer, territories.begin() + (i + 1) * territoriesPerPlayer);

            //Set the owner for each territory
            for (Territory* territory : playerTerritories) {
                territory->setTerritoryOwner(allPlayers[i]);
                numDistributedTerritories++;
            }

            allPlayers[i]->setTerritoryList(playerTerritories);

            cout << setw(25) << left << "Territory" << setw(25) << "Continent" << "Owner" << endl;
            cout << "_____________________________________________________________________________" << endl;
        
            for (Territory* territory : playerTerritories) {
                cout << setw(25) << left <<  territory->getTerritoryName();
                cout << setw(25) << left << territory->getContinent()->getContinentName();
                cout << setw(25) << left << territory->getTerritoryOwner()->getPlayerID() << endl;
            }
             
            cout << "\n" << endl;
        }


        // Assign 50 army units to each player
        for (Player* player : allPlayers) {
            player->setReinforcementPool(50);
        }

      
        //initialize deck with 30 cards
        Deck gameDeck(30);

        //Let each player draw two cards from the gameDeck
        for (Player* player : allPlayers) {
            Hand* handOfCards = player->getHandOfCards();
            //if player doesn't have cards initially create and assign their handOfCards
            if (!handOfCards) {
                handOfCards = new Hand(); 
                player->setHand(handOfCards); 
            }
            for (int i = 0; i < 2; ++i) {
                gameDeck.Draw(handOfCards->hand);
                
            } 
        }

        // Randomize the order of players
        random_shuffle(allPlayers.begin(), allPlayers.end());

        cout << "ALL PLAYERS HAVE DRAWN TWO CARDS FROM THE DECK AND HAVE BEEN ASSIGNED 50 ARMY UNITS\n" << endl;
        cout << "TAKE A LOOK AT YOUR BATTLE KIT!\n" << endl;

        int playerOrder = 0;

        //Display each player's initial status
        for (Player* player: allPlayers) {
            ++playerOrder; 
            cout << "PLAYER ORDER: " << playerOrder << endl;
            cout << "PLAYER: " << player->getPlayerID() << endl;
            cout << "TERRITORIES OWNED: "; player->printTerritoryList(player->getTerritoryList());
            cout << "\nREINFORCEMENT POOL: " << player->getReinforcementPool() << endl;
            cout << "HAND OF CARDS: "; 
                                        Hand* handOfCards = player->getHandOfCards();
                                        for (int i = 0; i < handOfCards->hand.size(); i++) {
                                        cout << *handOfCards->hand[i] << " ";
                                        }
            cout << "\n" << endl;
        }

        cout << "WARRIORS, GET READY TO PLUNGE INTO THE ACTION, FOR YOUR EPIC CONQUEST IS ABOUT TO BEGIN!\n" << endl;

        cout << "    ______" << endl;
        cout << " __/__|___\\__" << endl;
        cout << "|  |  |  |  |" << endl;
        cout << "|  |  |  |  |" << endl;
        cout << "|__|__|__|__|" << endl;
        cout << "|__|__|__|__|" << endl;
        cout << "  | |    | |" << endl;
        cout << "  | |    | |" << endl;
        cout << "  |_|    |_|" << endl;
        cout << "\n";
    
}

void GameEngine::reinforcementPhase() {

            cout << "BEFORE\n" << endl;
            for (Player* player: allPlayers) {

                // if(player->getPlayerID() == "john" || player->getPlayerID() == "mike") 
                cout << player->getPlayerID() << "'s Reinforcement Pool: " << player->getReinforcementPool() << endl;
                
            }


            cout << "ADDITIONAL ARMY UNITS ARE ON THE WAY, ENHANCING YOUR FORCES FOR THE BATTLES AHEAD. GET READY!" << endl;

           for (Player* player : allPlayers) {
                int newReinforcements = 0;

                // Calculate newReinforcements based on the number of territories owned by the player; minimum value is 3
                int territoriesOwned = player->getTerritoryList().size();
                newReinforcements += max(3, territoriesOwned / 3);

                // Check if the player owns any continents and add the continent control bonus
                vector<Continent*> controlledContinents = selectedMap.continentsOwnedByPlayer(player);
                for (Continent* continent : controlledContinents) {
                    newReinforcements += continent->getContinentBonus();
                }

                // Update the player's reinforcement pool using the addReinforcements method
                player->addReinforcements(newReinforcements);

                //cout << player->getPlayerID() << ", this is your reinforcementPool" << player->getReinforcementPool() << endl;
            }

            cout << "AFTER\n" << endl;
            for (Player* player: allPlayers) {

                // if(player->getPlayerID() == "john" || player->getPlayerID() == "mike") 
                cout << player->getPlayerID() << "'s Reinforcement Pool: " << player->getReinforcementPool() << endl;
                
            }
    
}


void GameEngine::issueOrdersPhase() {

    cout << "\nIT'S TIME TO ISSUE YOUR COMMANDS\n" << endl;

    for (Player* player : allPlayers) {

        cout << "  O" << endl;
        cout << " /|\\" << endl;
        cout << " / \\" << endl;
        cout << "/   \\" << endl;
        cout << "___________________________________________________________________________________" << endl;
        cout << player->getPlayerID() << ", IT IS YOUR TURN.....\n" << endl;
        player->issueOrder();
    }

}

void GameEngine::executeOrdersPhase() {

    cout << "\nExecution phase\n" << endl; 
    // for(Player* player: allPlayers) {
    //     for(Order* order: player->getOrderList()) {
    //         order->execute();
    //     }
    // } 

}


Player* GameEngine::checkWinner() {
    //Iterate through all players and check if any player owns all territories
    for (Player* player : allPlayers) {
        if (player->getTerritoryList().size() == numDistributedTerritories) {
            return player;
        }
    }

    return nullptr; //No winner yet
}

void GameEngine::removePlayers() {
    vector<Player*> survivingPlayers;
    
    for (Player* player : allPlayers) {
        if (!player->getTerritoryList().empty()) {
            survivingPlayers.push_back(player);
        } else {
            cout << "OOPS! PLAYER " << player->getPlayerID() << " has been eliminated.................................................................................................................................." << endl;
        }
    }

    allPlayers = survivingPlayers; // Update the player list
}


// void GameEngine::mainGameLoop() {

//     int maxRounds = 3;
//     int currentRound = 1;
//     Player* winner = nullptr;

//     while (currentRound < maxRounds) {
//         reinforcementPhase();  // Implement this function
//         issueOrdersPhase();    // Implement this function
//         executeOrdersPhase(); // Implement this function

//         // Check for a winner
//         winner = checkWinner();
//         if (winner) {
//             cout << "Player " << winner->getPlayerID() << " wins!" << endl;
//             break;
//         }

//         // if (currentRound == 1) {
//         //      int randomIndex = rand() % allPlayers.size();  // Randomly choose a player
//         //     Player* playerToRemove = allPlayers[randomIndex];

//         //     //Remove all the player's territories 
//         //     cout << "Removing player's territories" << endl;
//         //     playerToRemove->setTerritoryList(vector<Territory*>());
//         // }

//         //Check for players with zero territories and remove them
//         removePlayers();

//         currentRound++;
//     }

//     if (!winner) {
//         cout << "The game ends in a tie. No winner." << endl;
//     } 

   
// }


void GameEngine::mainGameLoop() {

    int maxRounds = 5;
    int currentRound = 1; // Start from round 1
    Player* winner = nullptr;

    while (currentRound <= maxRounds) {
        reinforcementPhase();  // Implement this function
        issueOrdersPhase();    // Implement this function
        executeOrdersPhase();  // Implement this function

        // Check for a winner
        winner = checkWinner();
        if (winner) {
            cout << "PLAYER " << winner->getPlayerID() << " wins!" << endl;
            break;
        }

        // Manually remove a player's territories in round 2
        if (currentRound == 2) {
            if (!allPlayers.empty()) {
                int randomIndex = rand() % allPlayers.size();  // Randomly choose a player
                Player* playerToRemove = allPlayers[randomIndex];

                // Remove all the player's territories
                cout << "Removing territories from Player " << playerToRemove->getPlayerID() << endl;
                playerToRemove->setTerritoryList(vector<Territory*>());

                // Check for players with zero territories and remove them
                removePlayers();
            }
        }

        // // After removing players, check if there are still players left
        // if (allPlayers.size() < 2) {
        //     // If there are less than 2 players, the game cannot continue
        //     break;
        // }

        currentRound++;
    }

    if (!winner) {
        cout << "The game ends in a tie. No winner." << endl;
    }
}





void GameEngine::setSelectedMap(const Map& map) {
    selectedMap = map;
}

// Implementation of setAllPlayers
void GameEngine::setAllPlayers(const vector<Player*>& players) {
    allPlayers = players;
}

 void GameEngine::initializeGame(Map& map, vector<Player*>& players) {
    selectedMap = map;
    allPlayers = players;
}
string GameEngine::stringToLog()
{
    return "Game State: "+*userInput;
}


