////////////////////////////////////////////////////////////
//
//  CommandProcessingDriver.cpp
//
//
////////////////////////////////////////////////////////////

// INCLUDES ////////////////////////////////////////////////
#include "CommandProcessing.h"

// PROTOTYPE ///////////////////////////////////////////////

// Free function for testing all classes
void testCommandProcessor();

// MAIN ////////////////////////////////////////////////////
/*int main()
{
    testCommandProcessor();
    return 0;
}*/

// FUNCTION ////////////////////////////////////////////////
void testCommandProcessor()
{
    CommandProcessor cp;

    // Initialize the gamestate
    cp.initGs();

    // Reads command from console and saves the command if there is one to be saved.
    cp.saveCommand();

    // TEST STREAM OPERATORS [OK]
    // Check CommandProcessor stream operator
    // std::cout<<"Stream test "<< cp <<std::endl;

    // Stores the last command entered from the vector
    Command* a_command = cp.getCommand();

    while (a_command->getCmd()!="quit")
    {
        cp.saveCommand();
        Command* nextCmd = cp.getCommand();
        // stream test for CommandProcessor OK
        //std::cout<<"  Stream test "<< cp <<std::endl;
        cp.updateGs(nextCmd->getCmd());
    }
}