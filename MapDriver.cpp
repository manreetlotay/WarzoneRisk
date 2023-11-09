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
    map.mapLoader("Caribbean.map");
    map.Validate();
    map.showTerritories();
    map.showContinents();
    map.getADJTerritories("Cuba");
            
    Map map2;
    map2.mapLoader("Canada.map");
    map2.Validate();
}