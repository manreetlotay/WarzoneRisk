#include <iostream>
#include "Map.h"
#include <fstream>
#include <string.h>
#include <sstream>
#include <algorithm>



using namespace std;


int main()
{
    cout<<"Hello World :)";

    ifstream file("Canada.map");

    if(!file.is_open()){
        cerr << "Failed to open file :("<< endl;
        return 0;
    }

    string line;
    Map map;
    while (getline(file, line)){
        if (line == "[Continents]"){
            getline(file,line);
            while(line != ""){
                if (line != ""){ 
                size_t delimPos = line.find("=");
                string name = line.substr(0,delimPos);
                int bonus = stoi(line.substr(delimPos+1,line.length()));
                Continent* c = new Continent(name, bonus);
                map.continentList.push_back(c);
                getline(file,line);
                }
            }
            
        }
        if (line == "[Territories]"){
            getline(file,line);
            
            string name;
            while (!file.eof()) 
            {
                bool flag;
                while(line == ""){
                    getline(file,line); 
                    flag= file.eof();
                    if(flag == true){
                        break;
                    }                    
                }
                if (flag == false){
                    stringstream ss(line);
                    vector<string> tokens;
                    string token;
                    while (getline(ss,token,','))
                    {
                        tokens.push_back(token); 
                    }

                    string nameTerritory = tokens[0];
                    name = tokens[3];
                    Continent* c;
                    Territory* t;
                    c= map.findContinentByName(name);

                    if (map.findTerritoryByName(nameTerritory)==nullptr)
                    { 
                        t = new Territory(tokens[0],c);
                        map.territoryList.push_back(t);
                    } else {
                        t = map.findTerritoryByName(nameTerritory);
                        t->setContinent(c);
                    }

                    // Check if adjacent territory exist
                    for (int i=4;i< tokens.size();i++){
                        name = tokens[i];
                        auto it = find_if(map.territoryList.begin(),map.territoryList.end(),[&name](Territory* cont){return cont->getTerritoryName() == name;});
                        if (it == map.territoryList.end()){
                            Territory* newTerritory = new Territory(name);
                            map.territoryList.push_back(newTerritory);
                            t->adjencyList.push_back(newTerritory);
                        }else{
                            t->adjencyList.push_back(*it);
                        }
                    }
                    getline(file,line);
                }
            }
        }
    }
    bool f = map.checkTerritoryConnections();

    return 0;
}
