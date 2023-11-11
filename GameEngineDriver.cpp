#include <iostream>
#include"GameEngine.h"

using namespace std;

void testGameStates() {

    //GameEngine engineObj;
    //engineObj.startup();
    //engineObj.play();

    //system("pause");

    GameEngine game;
    game.startupPhase();
    game.mainGameLoop();
}
