#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Player;

// class Player
// {
// private:
//     string playerName;
// public:
//     Player(/* args */);
//     ~Player();
// };
//  Player:: Player(/* args */)
// {
//     //playerName = "";                            ////////////////////////////////////////////////////UNCOMMENT
// }
// Player:: ~Player()
// {

// }
class Continent
{
private:
    string continentName;
    int bonus;
public:
    Continent();
    Continent(string, int);
    ~Continent();
    // Setters and Getters
    string getContinentName();
    int getContinentBonus();
    void setContinentName(string);
    void setContinentBonus(int);
};

// Continent::Continent()
// {
//     this -> continentName = "";
//     this -> bonus = 0;
// }

// Continent::Continent(string name, int extra)
// {
//     this -> continentName = name;
//     this -> bonus = extra;
// }

// Continent::~Continent()
// {
// }

// string Continent::getContinentName(){
//     return this -> continentName;
// }

// int Continent::getContinentBonus(){
//     return this->bonus;
// }
// void Continent::setContinentName(string name){
//     this -> continentName = name;
// }
// void Continent::setContinentBonus(int num){
//     this -> bonus = num;
// }
class Territory
{
private:
    string territoryName;
    Continent* continent;
    Player* player;
    int armies;

public:
    Territory();
    Territory(string, Continent*); // Constructor for map
    Territory(string Name); // Creating adjacent territories if they don't exist
    ~Territory();
    // Setters and Getters
    void setContinent(Continent*);
    Continent* getContinent();
    void setTerritoryName(string name);
    string getTerritoryName();
    void setTerritoryOwner(Player*);
    Player* getTerritoryOwner();
    int getNumOfArmies();
    void setNumOfArmies(int);

    vector<Territory*> adjencyList; // Track adjacent territories
    bool operator==(const Territory& other) const; // Override == operator to compare Territories
    
};

// Territory::Territory()
// {
//     territoryName = "";
//     continent = nullptr;
//     player = nullptr;
//     armies = 0;
//     adjencyList.clear();

// }

// Territory::Territory(string Name, Continent *c)
// {
//     territoryName  = Name;
//     continent = c;
    
// }

// Territory::Territory(string Name)
// {
//     territoryName  = Name;   
// }

// Territory::~Territory()
// {
// }
// Continent* Territory::getContinent(){
//     return this->continent;
// }
// void Territory::setContinent(Continent* c){
//     continent = c;
// }
// string Territory::getTerritoryName(){
//     return this -> territoryName;
// }
// void Territory::setTerritoryName(string name){
//     this -> territoryName = name;
// }
// void Territory::setTerritoryOwner(Player* owner){
//     this -> player = owner;
// }
// Player* Territory::getTerritoryOwner(){
//     return this -> player;
// }
// int Territory::getNumOfArmies(){
//     return this -> armies;
// }
// void Territory::setNumOfArmies(int num){
//     this -> armies = num;
// }
// bool Territory::operator==(const Territory& other) const {
//     return territoryName == other.territoryName;
// }
class Map
{
private:

public:
    Map();
    ~Map();
    vector<Continent*>continentList; // List points to existing continent objects
    vector<Territory*>territoryList; // List points to existing territory objects
    Continent* findContinentByName(string name); // Find and return Continent from continentList
    Territory* findTerritoryByName(string name);
    bool Validate();
    void DFS(Territory*,vector<Territory*>&);
    void DFS1(Territory*, vector<Territory*>&, vector<Continent*>&);
    bool checkTerritoryConnections();
    bool checkContinentConnections();
    bool checkTerritoryTo1Contient();

};

//free function
void testLoadMaps();
  
// };
// Map::Map(/* args */)
// {
// }

// Map::~Map()
// {
// }
// Continent* Map::findContinentByName(string name){
//     auto it = find_if(this->continentList.begin(),this->continentList.end(),[&name](Continent* cont){return cont->getContinentName() == name;});
//     return (it != continentList.end()) ? *it : nullptr; 
// }
// Territory* Map::findTerritoryByName(string name){
//     auto it = find_if(this->territoryList.begin(),this->territoryList.end(),[&name](Territory* cont){return cont->getTerritoryName() == name;});
//     return (it != territoryList.end()) ? *it : nullptr; 
// }

// //Create DFS function to check the connection between territories

// void Map::DFS(Territory* territory, vector<Territory*> &visited){
//     visited.push_back(territory);
//     for(Territory* adj : territory->adjencyList){
//         auto it = find(visited.begin(),visited.end(),adj);
//         if (it == visited.end()){
//             DFS(adj,visited);
//         }
//     }
// }
// void Map::DFS1(Territory* territory, vector<Territory*> &visitedT, vector<Continent*> &visitedC){
//     visitedT.push_back(territory);
//     auto it = find(visitedC.begin(),visitedC.end(),territory->getContinent());
//     if (it == visitedC.end())
//     {
//         visitedC.push_back(territory->getContinent());
//     }
    
//     for(Territory* adj : territory->adjencyList){
//         auto it = find(visitedT.begin(),visitedT.end(),adj);
//         if (it == visitedT.end()){
//             DFS1(adj,visitedT,visitedC);
//         }
//     }
// }

// bool Map::checkTerritoryConnections(){
//     vector<Territory*> visited;
//     DFS(territoryList[0],visited);

//     return visited.size()==territoryList.size();
// }

// bool Map::checkContinentConnections(){
//     vector<Territory*> visitedT;
//     vector<Continent*> visitedC;
//     DFS1(territoryList[0],visitedT,visitedC);

//     return visitedC.size()==continentList.size();
// }

// bool Map::checkTerritoryTo1Contient(){
//     for(Territory* territory: territoryList){
//         if (territory->getContinent()==nullptr){
//             return false;
//         }
//         auto it = find(continentList.begin(),continentList.end(),territory->getContinent());
//         if (it == continentList.end() ){
//             return false;
//         }
//     }
//     return true;

