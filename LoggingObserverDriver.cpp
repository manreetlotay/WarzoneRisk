#include <iostream>
#include "GameEngine.h"
#include "CommandProcessing.h"

void testLoggingObserver() {
	cout << "Testing CommandProcessing Observer" << endl;
	testCommandProcessor();
	testGameStates();
	
}
