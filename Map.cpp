//#include <iostream>
#include "Map.h"
using namespace std;

//  Player:: Player(/* args */)
// {
//     //playerName = "";                            ////////////////////////////////////////////////////UNCOMMENT
// }
// Player:: ~Player()
// {

// }

Continent::Continent()
{
    this -> continentName = "";
    this -> bonus = 0;
}

Continent::Continent(string name, int extra)
{
    this -> continentName = name;
    this -> bonus = extra;
}

Continent::~Continent()
{
}

string Continent::getContinentName(){
    return this -> continentName;
}

int Continent::getContinentBonus(){
    return this->bonus;
}
void Continent::setContinentName(string name){
    this -> continentName = name;
}
void Continent::setContinentBonus(int num){
    this -> bonus = num;
}


Territory::Territory()
{
    territoryName = "";
    continent = nullptr;
    player = nullptr;
    armies = 0;
    adjencyList.clear();

}

Territory::Territory(string Name, Continent *c)
{
    territoryName  = Name;
    continent = c;
    
}

Territory::Territory(string Name)
{
    territoryName  = Name;   
}

Territory::~Territory()
{
}
Continent* Territory::getContinent(){
    return this->continent;
}
void Territory::setContinent(Continent* c){
    continent = c;
}
string Territory::getTerritoryName(){
    return this -> territoryName;
}
void Territory::setTerritoryName(string name){
    this -> territoryName = name;
}
void Territory::setTerritoryOwner(Player* owner){
    this -> player = owner;
}
Player* Territory::getTerritoryOwner(){
    return this -> player;
}
int Territory::getNumOfArmies(){
    return this -> armies;
}
void Territory::setNumOfArmies(int num){
    this -> armies = num;
}
bool Territory::operator==(const Territory& other) const {
    return territoryName == other.territoryName;
}


Map::Map(/* args */)
{
}

Map::~Map()
{
}
Continent* Map::findContinentByName(string name){
    auto it = find_if(this->continentList.begin(),this->continentList.end(),[&name](Continent* cont){return cont->getContinentName() == name;});
    return (it != continentList.end()) ? *it : nullptr; 
}
Territory* Map::findTerritoryByName(string name){
    auto it = find_if(this->territoryList.begin(),this->territoryList.end(),[&name](Territory* cont){return cont->getTerritoryName() == name;});
    return (it != territoryList.end()) ? *it : nullptr; 
}

//Create DFS function to check the connection between territories

void Map::DFS(Territory* territory, vector<Territory*> &visited){
    visited.push_back(territory);
    for(Territory* adj : territory->adjencyList){
        auto it = find(visited.begin(),visited.end(),adj);
        if (it == visited.end()){
            DFS(adj,visited);
        }
    }
}
void Map::DFS1(Territory* territory, vector<Territory*> &visitedT, vector<Continent*> &visitedC){
    visitedT.push_back(territory);
    auto it = find(visitedC.begin(),visitedC.end(),territory->getContinent());
    if (it == visitedC.end())
    {
        visitedC.push_back(territory->getContinent());
    }
    
    for(Territory* adj : territory->adjencyList){
        auto it = find(visitedT.begin(),visitedT.end(),adj);
        if (it == visitedT.end()){
            DFS1(adj,visitedT,visitedC);
        }
    }
}

bool Map::checkTerritoryConnections(){
    vector<Territory*> visited;
    DFS(territoryList[0],visited);

    return visited.size()==territoryList.size();
}

bool Map::checkContinentConnections(){
    vector<Territory*> visitedT;
    vector<Continent*> visitedC;
    DFS1(territoryList[0],visitedT,visitedC);

    return visitedC.size()==continentList.size();
}

bool Map::checkTerritoryTo1Contient(){
    for(Territory* territory: territoryList){
        if (territory->getContinent()==nullptr){
            return false;
        }
        auto it = find(continentList.begin(),continentList.end(),territory->getContinent());
        if (it == continentList.end() ){
            return false;
        }
    }
    return true;
}