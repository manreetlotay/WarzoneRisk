#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Player;

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
    void Validate();
    void DFS(Territory*,vector<Territory*>&);
    void DFS1(Territory*, vector<Territory*>&, vector<Continent*>&);
    bool checkTerritoryConnections();
    bool checkContinentConnections();
    bool checkTerritoryTo1Contient();
    void mapLoader(string);
    void showTerritories();
    void showContinents();
    void getADJTerritories(string);

};

//free function
void testLoadMaps();
  

