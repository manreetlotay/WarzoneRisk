#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;



class Player
{
private:
    string playerName;
public:
    Player(/* args */);
    ~Player();
};
 Player:: Player(/* args */)
{
    playerName = "";
}
Player:: ~Player()
{

}
class Continent
{
private:
    string continentName;
    int bonus;
public:
    Continent();
    Continent(string, int);
    ~Continent();
    string getContinentName();
};

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

class Territory
{
private:
    string territoryName;
    int id;
    Continent* continent;
    Player* player;
    int armies;

public:
    Territory();
    Territory(string, Continent*); // Constructor for string map format
    Territory(int, Continent*); // Constructor for int map format
    Territory(int ID); // Creating adjacent territories if they don't exist
    Territory(string Name); // Creating adjacent territories if they don't exist

    ~Territory();
    void setContinent(Continent*);
    string getTerritoryName();
    vector<Territory*> adjencyList; // Track adjacent territories
    bool operator==(const Territory& other) const;
    
};

Territory::Territory()
{
    territoryName = "";
    id = 0;
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

Territory::Territory(int ID, Continent *c)
{
    id = ID;
    continent = c;
}
Territory::Territory(int ID){
    id = ID;
}
Territory::Territory(string Name)
{
    territoryName  = Name;   
}

Territory::~Territory()
{
}
string Territory::getTerritoryName(){
    return this -> territoryName;
}
void Territory::setContinent(Continent* c){
    continent = c;
}
bool Territory::operator==(const Territory& other) const {
    return territoryName == other.territoryName;
}
class Map
{
private:

public:
    Map();
    ~Map();
    vector<Continent*>continentList; // List points to existing continent objects
    vector<Territory*>territoryList; // List points to existing territory objects
    Continent* findContinentByName(string name);    // Find and return Continent from continentList
    Territory* findTerritoryByName(string name);    // Find and return Territory from territoryList
    bool Validate();    // Validate map by checking territory and continent connections 
                        // and 1 to many relationship continent-territory
    void DFS(Territory*,vector<Territory*>&);
    void DFS1(Territory*, vector<Territory*>&, vector<Continent*>&);    //Search through DFS to check continent connections
    bool checkTerritoryConnections();   // Search through DFS to check territory connections
    bool checkContinentConnections();   //Search through DFS to check continent connections
    bool checkTerritoryTo1Contient();
};
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


bool Map::checkTerritoryConnections(){
    vector<Territory*> visited;
    DFS(territoryList[0],visited);

    return visited.size()==territoryList.size();
}

bool Map::checkContinentConnections(){
    
}