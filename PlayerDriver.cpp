/*
IMEPLEMENTATION OF A WARZONE PLAYER
AUTHOR: Manreet Kaur Lotay (40202883)
*/

#include "Player.h"
#include <iostream>

using namespace std;

//jsut for me
void mainGameLoop();
void reinforcementPhase();
        void issueOrdersPhase();
        void executeOrdersPhase();


void testPlayers() {

    // //Testing for Player begins
    // std::cout << "TESTING THE FEATURES OF A PLAYER: " << std::endl;

    // //Create a Deck of Card Objects, a Hand* of Card objects and populate the Hand* with repeated calls to the Draw() method
    // Deck d(10);
    // Hand* handOfCards = new Hand;
    // for (int i = 0; i < 5; ++i) {
    //     d.Draw(handOfCards->hand);
    // }

    // //Create a OrderList* object and a couple Order objects
    // OrderList* orderList = new OrderList;
    // Deploy deploy;
    // Advance advance;
    // Bomb bomb;
    // Blockade blockade;
    // Airlift airlift;
    // Negotiate negotiate;

    // //Create Continent objects
    // Continent* Asia = new Continent("Asia", 5);
    // Continent* Europe = new Continent("Europe", 3);

    // //Create Territory objects with references to Continent objects
    // Territory* England = new Territory("England", Europe);
    // Territory* France = new Territory("France", Europe);
    // Territory* Malaysia = new Territory("Malaysia", Asia);
    // Territory* India = new Territory("India", Asia);

    // //Create territoryList and add Territory* objects to it
    // vector<Territory*> territoryList;
    // territoryList.push_back(England);
    // territoryList.push_back(France);
    // territoryList.push_back(Malaysia);
    // territoryList.push_back(India);

    // //Set the Number of armies for different Territory* objects
    // England->setNumOfArmies(3);
    // France->setNumOfArmies(1);  //deDefend
    // Malaysia->setNumOfArmies(10);
    // India->setNumOfArmies(4);

    // //Instantiate a Player object with the default constructor
    // Player* playerDefault = new Player;

    // //Testing Default constructor
    // std::cout << "The following player was instantiated using the default constructor: " << std::endl;
    // std::cout << *playerDefault << std::endl;

    // //Instantiate a Player object with the parameterized constructor using handOfCards and orderList
    // Player* player = new Player(handOfCards, orderList, territoryList, "manreet");

    // //Testing issueOrder() method
    // player->issueOrder(&deploy);
    // player->issueOrder(&advance);
    // player->issueOrder(&airlift);

    // //Testing parameterized constructor
    // std::cout << "The following player was instantiated using the parameterized constructor: " << std::endl;
    // std::cout << *player << std::endl;

    // //Testing toDefend() and toAttack() method
    // std::cout << "Territories to Attack:" << std::endl;
    // player->printTerritoryList(player->toAttack());

    // std::cout << "Territories to Defend:" << std::endl;
    // player->printTerritoryList(player->toDefend());

    // //Testing copy constructor of player
    // std::cout << "Testing copy constructor: " << std::endl;
    // Player* playerCopy = new Player(*player);
    // std::cout << *playerCopy << std::endl;

    // //Testing assignment operator of player
    // std::cout << "Testing assignment operator" << std::endl;
    // Player* playerAssignment = new Player(); //instantiated as default
    // playerAssignment = player;               //now: assigned with parameterized Player             
    // std::cout << *playerAssignment << std::endl;  

    // //prevent memory leaks and dangling pointers (calls destructor of Player class and deletes handOfCards, orderList and territoryList)
    // delete playerDefault;
    // delete playerCopy;
    // delete player;
    // delete playerAssignment;

    // playerDefault = nullptr;
    // player = nullptr;
    // playerCopy = nullptr;
    // playerAssignment = nullptr;


     
        //Welcome the user to Warzone
        cout << "===================================================================================================================" << endl;
        cout << "| WELCOME TO THE WORLD OF WARZONE, where strategy and wit reign supreme!" << endl;
        cout << "| Get ready to conquer your way to victory on this interconnected battlefield, one move at a time!" << endl;
        cout << "==================================================================================================================\n" << endl;
        
        //Initialize variables
        Map selectedMap;
        vector<Player*> allPlayers;
        int numPlayers;
        vector<string> playerNames;
        vector<string> mapNames = { "maps/Canada.map", "maps/Caribbean.map" };
        string selectedMapName;

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
        cout << "TAKE A MOMENT TO SURVEY THE TERRITORIES WHERE YOU'LL BE WAGING YOUR EPIC BATTLES." << endl;

        //Display Territories to players
        selectedMap.showTerritories();

        // Prompt the user to add players to the game
        while (true) {
            cout << "\nIT IS NOW TIME TO CHOOSE YOUR ALLIES. YOU HAVE THE OPTION TO INVITE BETWEEN 2 AND 6 PLAYERS TO JOIN THE BATTLE. PLEASE ENTER A VALID NUMBER\n";
            cin >> numPlayers;

            if (numPlayers >= 2 && numPlayers <= 6) {
                break;
            } else {
                cout << "\nOOPS! IN WARZONE, WE'RE LIMITED TO 2 TO 6 PLAYERS. PLEASE CHOOSE A VALID NUMBER OF COMRADES TO RALLY.\n" << endl;
            }
        }

        // Prompt user to enter names for each player
        cout << "\nGREAT! NOW THAT YOU'VE RALLIED YOUR FORCES, IT'S TIME TO BESTOW UNIQUE TITLES UPON EACH WARRIOR IN YOUR ARMY. CHOOSE A NAME FOR EVERY PLAYER, AND LET THEIR LEGEND BEGIN!\n" << endl;
        for (int i = 0; i < numPlayers; i++) {
            string playerName;
            cout << "Please enter a name for player " << i + 1 << ": ";
            cin >> playerName;
            playerNames.push_back(playerName);
        }

        cout << "\nGREAT JOB! THOSE ARE SOME FANTASTIC NAMES FOR YOUR BATTLE-HARDENED COMRADES." << endl;

        // Create Player objects and store them in allPlayers vector
        for (int i = 0; i < numPlayers; i++) {
            Player* newPlayer = new Player();
            newPlayer->setPlayerID(playerNames[i]);
            allPlayers.push_back(newPlayer);
        }

        cout << "\nBehold, warriors of the battlefield! According to your chosen map, territories have been assigned to each of you. Take a moment to survey the lands you and your adversaries now command.\n" << endl;


        // Assign territories to players 
        vector<Territory*> territories = selectedMap.getTerritoryList();
        random_shuffle(territories.begin(), territories.end());

        int territoriesPerPlayer = territories.size() / numPlayers;

        for (int i = 0; i < numPlayers; i++) {
            vector<Territory*> playerTerritories(territories.begin() + i * territoriesPerPlayer, territories.begin() + (i + 1) * territoriesPerPlayer);

            //Set the owner for each territory
            for (Territory* territory : playerTerritories) {
                territory->setTerritoryOwner(allPlayers[i]);
            }

            allPlayers[i]->setTerritoryList(playerTerritories);

            cout << "\nPlayer " << allPlayers[i]->getPlayerID() << "'s dominion extends over these lands: \n" << endl;
        
            for (Territory* territory : playerTerritories) {
                cout << "Territory: " << territory->getTerritoryName() << " ( Continent: " << territory->getContinent()->getContinentName() << " )" << endl;
            }
             
             cout << "\n" << endl;
        }

        /*
        Set armies on territory to 0 initially
        */
        for (Territory* terr: territories) {
            terr->setNumOfArmies(0);
        }



        
        cout << "\nYou, brave commanders, have been bestowed with a formidable army of 50 units. Wield them wisely, for the fate of your conquest rests upon your strategic decisions.\n" << endl;
        cout << "\nTake a look at the order in which you'll be leading your armies into battle.\n" << endl;

        // Randomize the order of players
        random_shuffle(allPlayers.begin(), allPlayers.end());

        // Display the order in which players will play
        for (int i = 0; i < numPlayers; i++) {
            cout << i + 1 << ". " << allPlayers[i]->getPlayerID() << endl;
        }

        // Assign 50 units to each player
        for (Player* player : allPlayers) {
            player->setReinforcementPool(50);
        }


        cout << "\nEnter the command 'drawCards' and each of you will be granted the chance to draw 2 Warzone Cards to further bolster your arsenal.\n" << endl;

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

        cout << "\nWarriors, you're now armed with cards, reinforcements, and territories. Your battle kit is complete. Get ready to plunge into the action, for your epic conquest is about to begin!\n" << endl;


        cout << "ACCORDING TO THE MAP YOU'VE CHOSEN, TERRITORIES HAVE BEEN ALLOCATED TO EACH OF YOU VALIANT WARRIORS. ADDITIONALLY, YOU'VE ALL BEEN ENTRUSTED WITH A FORMIDABLE FORCE OF 50 ARMY UNITS. THE STAGE IS SET FOR AN EPIC CLASH OF STRATEGIES." << endl;
        //------------------
        //DISPLAY EACH PLAYERS INITIAL STATUS
        //========================================
        for (Player* player: allPlayers) {
            cout << "==================================================================" << endl;
            cout << player->getPlayerID() << ", Take a look" << endl;
            cout << "==================================================================" << endl;
            cout << "\n";
        }


        // for (Player* player : allPlayers) {
        //     cout << "PLayer's handofCards. Player: " << *player << endl;
        // }
        
        //----------------------------------
        //END OF STARTUP PHASE
        //----------------------------------



    //ENTER MAIN GAME LOOP
    //--------------------------------

            //REINFORCEMENT PHASE
                //assign bonus value to each continent in the map

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
            }








            //ISSUE ORDER PHASE
            cout << "Warriors, the time has come to issue your commands and place them in your orderList. Let's proceed in a round-robin fashion, ensuring each of you has a chance to shape the tides of battle." << endl;

            for (Player* player : allPlayers) {
                cout << "----------------------------" << endl;
                cout << player->getPlayerID() << ", it is your turn!" << endl;
                cout << "----------------------------" << endl;
                player->issueOrder();
            }


            //EXECUTE ORDER PHASE




// void mainGameLoop() {

//     // Variable to keep track of the current turn
//     int turnCounter = 0;

//     // Variable to limit the maximum number of game loops
//     int maxGameLoops = 50;

//     // Main game loop
//     while (true) {
//         // Check if a player has won by owning all territories
//         Player* winningPlayer = checkForWin(allPlayers);
//         if (winningPlayer != nullptr) {
//             cout << "Congratulations, " << winningPlayer->getPlayerID() << " has won the game!" << endl;
//             break;
//         }

//         // Check for players with no territories and remove them
//         removePlayersWithNoTerritories(allPlayers);

//         // Check if the maximum number of game loops is reached
//         if (turnCounter >= maxGameLoops) {
//             cout << "The game has ended in a draw." << endl;
//             break;
//         }

//         // Get the current player for the current turn
//         Player* currentPlayer = allPlayers[turnCounter % numPlayers];

//         // Subphase 1: Reinforcement Phase
//         reinforcementPhase(currentPlayer);

//         // Subphase 2: Issue Orders Phase
//         issueOrdersPhase(currentPlayer);

//         // Subphase 3: Execute Orders Phase
//         executeOrdersPhase(currentPlayer);

//         // Increment the turn counter
//         turnCounter++;
//     }

// }
    






















}



