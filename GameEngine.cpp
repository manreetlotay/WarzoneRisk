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
GameEngine::GameEngine() {

    userInput = new string("");
    players = new int(0);

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
//void GameEngine::verifyCommand() {
//	const vector<string> commandList = { "loadmap","validatemap","addplayer","assigncountries","issueorder","endexecorders","execorder","win","play" };
//    
//    
//}

GameEngine::~GameEngine()
{
}
