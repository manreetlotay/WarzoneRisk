#include <iostream>
#include "Map.h";
using namespace std;

void dfs(Territory* territory, std::set<Territory*>& visited) {
    visited.insert(territory);
    for (Territory* adj : territory->adjencyList) {
        if (visited.find(adj) == visited.end()) {
            dfs(adj, visited);
        }
    }
}

bool Map::checkTerritoryConnections(){
    set<Territory*> visited;
    dfs(territoryList[0],visited);
    return visited.size() == territoryList.size();
}



