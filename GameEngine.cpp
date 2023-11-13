#include"GameEngine.h"
//#include "Player.h"
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

Map Loaded
Map Validated
Players added
Assign Reinforcement

*/
GameEngine::GameEngine() {

	userInput = new string("");
	playersCounter = new int(0);
	currentState = new string("Start");
	mapObj = new Map();
	
}


void GameEngine::loadMap(string uInput) {
	int errCounter = 0; //Counter for number of wrong command entries
	bool flag = true;
	/*while (uInput != "loadmap")
	{
		errCounter++;


		cout << "\nERROR! Invalid command" << endl;
		setCommand();

		if (errCounter == 4) {
			cout << "ERROR! Invalid command" << endl;
			cout << "Too many attempts, terminating session" << endl;
			exit(0);

		}

	}*/

	mapObj->mapLoader(uInput);
	*currentState = "Map Loaded";
	string secInput = "";

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
			cout << "\nEnter Command: " << endl;
			cin >> uInput >> secInput; //secInput here is the second argument for the command.
			delete mapObj;
			mapObj = new Map();
			mapObj->mapLoader(secInput);
			cout << "\nSTATE:Map Loaded" << endl;
	
		}
		else {
			cout << "ERROR! Invalid command" << endl;
			/*cout << "Would you like to load map again? (yes/no)" << endl;
			cin >> uInput;*/
		}
		cout << "Would you like to load map again? (yes/no)" << endl;
		cin >> uInput;

	}

}
void GameEngine::validateMap(string& uInput) {
	int errCounter = 0;
	bool flag = true;
	while (uInput != "validatemap")
	{
		errCounter++;


		cout << "\nERROR! Invalid command" << endl;
		setInput();

		if (errCounter == 4) {
			cout << "ERROR! Invalid command" << endl;
			cout << "Too many attempts, terminating session" << endl;
			exit(0);

		}

	}
	*currentState = "Map Validated";
	mapObj->Validate();
	cout << "\nSTATE:Map Validated" << endl;
}

//make this 2 paramaters
void GameEngine::addPlayer(string uInput, string playerName) {

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
	const int minPlayers = 2;
	const int maxPlayers = 6;
	Player* p= new Player();
	p->setName(playerName);
	players.push_back(p);
	*playersCounter += 1;
	*currentState = "Players Added";
	
	cout << "\nSTATE: " << *playersCounter << " Players added to the game" << endl;
	
	cout << "Would you like to add another player? (yes/no)" << endl;
	cin >> uInput;
	while (flag = true)
	{
		if (uInput == "no") {
			if (*playersCounter < minPlayers || *playersCounter >maxPlayers) {
				cout << "Insufficient Players: add " <<minPlayers-*playersCounter<<" - " <<maxPlayers-*playersCounter<<" player(s) to continue" <<endl;
			}
			else
			{
				flag = false;
				break;
			}
			/*flag = false;
			break;*/
		}
		if (uInput == "yes") {
			cout << "\nEnter Command: " << endl;
			cin >> playerName;
			p = new Player();
			p->setName(playerName);
			players.push_back(p);
			*playersCounter += 1;
			cout << "\nSTATE: " << *playersCounter << " Players added to the game" << endl;
			/*cout << "Would you like to add another player? (yes/no)" << endl;
			cin >> uInput;*/
		}
		else {
			cout << "ERROR! Invalid command" << endl;
			/*cout << "Would you like to add another player? (yes/no)" << endl;
			cin >> uInput;*/
		}
		cout << "\nWould you like to add another player? (yes/no)" << endl;
		cin >> uInput;
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

		//loadMap(*userInput);

		//setCommand();

		//validateMap(*userInput);

		//setCommand();

		//addPlayer(*userInput);

		//setCommand();

		bool isWin = false;
		bool flag = false;
		//assignReinforcement(*userInput);

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
void GameEngine::setInput() {
	cout << "\nEnter Command: " << endl;
	cin >> *userInput;
}

void GameEngine::setCommand() {

	string secInput = "";
	//string commandsArr[] = { "loadmap","validatemap","addplayer","assigncountries","endexecorders","execorder","win","play" };
	//string stateArr[] = { "Start", "Map Loaded", "Map Validated", "Players added", "Assign Reinforcement" };
	cout << "\nEnter Command: " << endl;
	

	if (*currentState == "Start") {
		cin >> *userInput >> secInput;
		if (*userInput == "loadmap") {
			if (secInput != "") {
				loadMap(secInput);
			}
		}
		else {
			cout << "\nERROR! Invalid command" << endl;
			setCommand();
		}
	}if (*currentState == "Map Loaded") {
		setInput();
		/*if (*userInput == "validatemap") {
			validateMap(*userInput);
		}*/
		validateMap(*userInput);
		
	}if (*currentState == "Map Validated") {
		cin >> *userInput >> secInput;
		addPlayer(*userInput, secInput);
	}if (*currentState == "Players Added") {
		setInput();
		if (*userInput == "gamestart") {

		}
	}

	



}

string GameEngine::getInput() {
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



