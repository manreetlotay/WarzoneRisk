#include <iostream>
#include "Map.h"
#include <fstream>
#include <string.h>
#include <sstream>
//#include <algorithm>

using namespace std;

void testLoadMaps()
{
    Map map;
    map.mapLoader("maps/Caribbean.map");
    map.Validate();
    map.showTerritories();
    map.showContinents();
    map.getADJTerritories("Jamaica");
    
    Map map2;
    map2.mapLoader("maps/Canada.map");
    map2.Validate();

    

    Territory* t1 = map.findTerritoryByName("Venezuela");
    cout << "armies of venezuela: " << t1->getNumOfArmies() << endl;
    cout << "name of t1" << t1->getTerritoryName() << endl;
    cout << "owner of t1" << t1->getTerritoryOwner() << endl;

    Territory* t2 = map.findTerritoryByName("Cuba");
    cout << "armies of cuba: " << t2->getNumOfArmies() << endl;
    

    Continent* c1 = map.findContinentByName("East");
    cout << "continent bonus" << c1->getContinentBonus() << endl;
   

}