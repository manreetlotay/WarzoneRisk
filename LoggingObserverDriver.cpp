#include <iostream>
#include "GameEngine.h"
#include "CommandProcessing.h"

void testLoggingObserver() {
	cout << "Testing CommandProcessing Observer" << endl;
	//testCommandProcessor();
	cout << "Testing Order Observer" << endl;
	testOrderExecution();
	cout << "Testing GameEngine Observer" << endl;
	testGameStates();
	
}
