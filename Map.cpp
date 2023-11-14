//#include <iostream>
#include "Map.h"
#include <fstream>
#include <string.h>
#include <sstream>
#include <iomanip>
using namespace std;


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



void Map::Validate() {
    bool a = checkContinentConnections() && checkTerritoryConnections() && checkTerritoryTo1Contient();
    if (a == true) {
        cout << "Map created and validated" << endl;
    }
    else {
        cout << "Map not valid" << endl;
    }
}

void Map::mapLoader(string mapname)
{
    cout << "Creating Map: "<< mapname << endl;

    fstream file;
    file.open(mapname);

    if (!file.is_open()) {
        cerr << "Failed to open file :(" << endl;

    }
    else {
        string line;
        while (getline(file, line)) {
            if (line == "[Continents]") {
                getline(file, line);
                while (line != "") {
                    if (line != "") {
                        size_t delimPos = line.find("=");
                        string name = line.substr(0, delimPos);
                        int bonus = stoi(line.substr(delimPos + 1, line.length()));
                        Continent* c = new Continent(name, bonus);
                        this->continentList.push_back(c);
                        getline(file, line);
                    }
                }

            }
            if (line == "[Territories]") {
                getline(file, line);

                string name;
                while (!file.eof())
                {
                    bool flag = false;
                    while (line == "") {
                        getline(file, line);
                        flag = file.eof();
                        if (flag == true) {
                            break;
                        }
                    }
                    if (flag == false) {
                        stringstream ss(line);
                        vector<string> tokens;
                        string token;
                        while (getline(ss, token, ','))
                        {
                            tokens.push_back(token);
                        }

                        string nameTerritory = tokens[0];
                        name = tokens[3];
                        Continent* c;
                        Territory* t;
                        c = this->findContinentByName(name);

                        if (this->findTerritoryByName(nameTerritory) == nullptr)
                        {
                            t = new Territory(tokens[0], c);
                            this->territoryList.push_back(t);
                        }
                        else {
                            t = this->findTerritoryByName(nameTerritory);
                            t->setContinent(c);
                        }

                        // Check if adjacent territory exist
                        for (int i = 4; i < tokens.size(); i++) {
                            name = tokens[i];
                            auto it = find_if(this->territoryList.begin(), this->territoryList.end(), [&name](Territory* cont) {return cont->getTerritoryName() == name; });
                            if (it == this->territoryList.end()) {
                                Territory* newTerritory = new Territory(name);
                                this->territoryList.push_back(newTerritory);
                                t->adjencyList.push_back(newTerritory);
                            }
                            else {
                                t->adjencyList.push_back(*it);
                            }
                        }
                        getline(file, line);
                    }
                }
            }
        }
    }

}

void Map::showTerritories()
{
   cout << left << setw(25) << "Territory Name" << setw(25) << "Continent" << "Adjacent Territories" << endl;
   cout << "______________________________________________________________________________________________________________" << endl;
    
    for (int i = 0; i < territoryList.size(); i++) {
        cout << setw(25) << left << territoryList[i]->getTerritoryName();
        cout << setw(25) << left << territoryList[i]->getContinent()->getContinentName();
        
        for (int j = 0; j < territoryList[i]->adjencyList.size(); j++) {
            cout << territoryList[i]->adjencyList[j]->getTerritoryName();
            if (j < territoryList[i]->adjencyList.size() - 1) {
                cout << ", ";
            }
        }
        
        cout << endl;
    }
    
    cout << endl;
}

void Map::showContinents()
{
    cout << "Continent List: ";
    for (int i = 0; i < continentList.size(); i++) {
        cout << continentList[i]->getContinentName()<< " ";
    }
    cout << endl;
}


void Map::getADJTerritories(string territoryName)
{
    Territory *t;
    t = findTerritoryByName(territoryName); 
    cout << "Adjacency List of " + territoryName + ":";
    for (int i = 0; i < t->adjencyList.size(); i++) {
        cout << " " + t->adjencyList[i]->getTerritoryName() + ",";
    }
    cout << endl;
}

vector<Territory*> Map::getTerritoryList() {
    return territoryList;
}



//Added my Manreet
//Takes a player as a parameter and returns a list of continents owned by that player
// vector<Continent*> Map::continentsOwnedByPlayer(Player* player) {
//     vector<Continent*> continentsOwned;

//     for (Continent* continent : continentList) {
//         vector<Territory*> territoriesInContinent;

//         // Find all territories in the current continent
//         copy_if(territoryList.begin(), territoryList.end(), back_inserter(territoriesInContinent),
//             [continent](Territory* territory) {
//                 return territory->getContinent() == continent;
//             });

//         // Check if the first territory's owner is the same for all territories in the continent
//         if (!territoriesInContinent.empty() &&
//             all_of(territoriesInContinent.begin(), territoriesInContinent.end(),
//                 [owner = territoriesInContinent[0]->getTerritoryOwner()](Territory* territory) {
//                     return territory->getTerritoryOwner() == owner;
//                 }) &&
//             territoriesInContinent[0]->getTerritoryOwner() == player) {
//             continentsOwned.push_back(continent);
//         }
//     }

//     return continentsOwned;
// }

vector<Continent*> Map::continentsOwnedByPlayer(Player* player) {
    vector<Continent*> continentsOwned;

    for (Continent* continent : continentList) {
        bool ownsAllTerritories = true;

        for (Territory* territory : territoryList) {
            if (territory->getContinent() == continent && territory->getTerritoryOwner() != player) {
                ownsAllTerritories = false;
                break;
            }
        }

        if (ownsAllTerritories) {
            continentsOwned.push_back(continent);
        }
    }

    return continentsOwned;
}
bool Map::isADJ(string name1, string name2)
{
    Territory* t1 = findTerritoryByName(name1);
    Territory* t2 = findTerritoryByName(name2);
    auto it = find_if(t1->adjencyList.begin(), t1->adjencyList.end(), [&name2](Territory* cont) {return cont->getTerritoryName() == name2; });
    return (it != t1->adjencyList.end()) ? true : false;
}