#pragma once
#ifndef TEST_ORDERS_H
#define TEST_ORDERS_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
using std::vector;
using std::string;
using std::ostream;

class Player;
class Territory;
class Map;

class Order
{
public :

    Order();

    // Destructor
    ~Order();

    //copy constructor
    Order(const Order& O);

    //assignment construtor
    Order& operator = (const Order &O);

    //Check if Order is valid
    virtual bool validate() = 0; // Check if the order is valid.

    virtual void execute() = 0; // Execute the order action.

    //set type of the subclass
    void setTypeID(int num);

    string getType();

    // Stream instertion operator
    friend std :: ostream& operator<<(std::ostream& output, const Order& order);

    std::string getDescription() const;

    bool hasExecuted() const;

protected:
    std:: string description;

    bool isExecuted = false;

private :

    bool valid;

    vector<string> vecType = { "deploy", "advance", "bomb", "blockade", "airlift", "negotiate" };

    int typeID;

    std:: string effect = "effect printed from Order Object";

    virtual Order *clone() const = 0;

    virtual ostream &printOrder(ostream &) const = 0;

    friend ostream &operator<<(ostream &, const Order &);

    friend class OrderList;

};

class Deploy : public Order
{

public:
    Deploy();

    Deploy(Territory* target, int armies, const std:: string& player);

    ~Deploy();

    string* getType();

    bool validate() override;

    void execute() override;

    friend std :: ostream& operator<<(std::ostream& output, const Deploy &deploy);

    Deploy& operator = (const Deploy& other);

private:
    bool valid;

    string type1 = { "deploy" };

    std:: string effect = "effect printed from Deploy Object";

    Territory* territory;

    int numArmies;

    std:: string issuingPlayer;

};

class Advance : public Order {
public:
    Advance();

    Advance(Territory* soruce, Territory* target, int armies, Map* gameMap, std::string  player);

    Advance& operator = (const Advance& other);

    ~Advance();
    friend std :: ostream& operator<<(std::ostream& output, const Advance &advance);

    bool validate() override;
    void execute() override;

private:
    bool valid;
    std:: string effect = "effect printed from Advnace Object";

    Territory* sourceTerritory;
    Territory* targetTerritory;
    int numberOfArmies;
    //Pointer to the map object
    Map* gameMap;
    std::string issuingPlayer;

};

class Bomb : public Order
{
public:
    Bomb();

    Bomb(Territory* target, std::string  player, Map* gameMap);

    Bomb& operator = (const Bomb& other);

    ~Bomb();
    bool valid;

    bool validate() override;
    void execute() override;

private:
    std:: string effect = "effect printed from Bomb Object";
    Territory* targetTerritory;
    std::string issuingPlayer;  // The player issuing the order
    Map* gameMap;

};

class Blockade : public Order
{
public:
    Blockade();

    Blockade(Territory* target, std::string  player);

    ~Blockade();

    friend std :: ostream& operator<<(std::ostream& output, const Blockade &blockade);

    bool validate() override;

    void execute() override;
private:
    bool valid;

    std:: string effect = "effect printed from Blockade Object";

    Territory* targetTerritory;

    std::string issuingPlayer;
};

class Airlift : public Order
{
public:
    Airlift();

    Airlift(Territory *source, Territory *target, int armies, std::string  player)

    ~Airlift();

    friend std :: ostream& operator<<(std::ostream& output, const Airlift &airlift);

    Airlift& operator = (const Airlift& other);

    bool validate() override;

    void execute() override;

private:
    bool valid;

    std:: string effect = "effect printed from Airlift Object";

    Territory* sourceTerritory;

    Territory* targetTerritory;

    int numberOfArmies;

    std::string issuingPlayer;
};

class Negotiate : public Order
{
public:
    Negotiate();
    ~Negotiate();
    friend std :: ostream& operator<<(std::ostream& output, const Negotiate &negotiate);

private:
    bool valid;
    std:: string effect = "effect printed from Negotiate Object";
};

class OrderList
{
public:

    OrderList();

    OrderList(const OrderList& exsistingOrderList);

    ~OrderList();

    void addOrder(Order* order);

    // Sets the order of the list
    void set_order_list(Order* an_order);
    vector<Order*>* get_order_list();
    //Remove order from list
    void remove(Order* oneOrder);
    //Move position
    void move(int position, int newPosition);

    OrderList& operator=(const OrderList& orderList);

    friend std :: ostream& operator<<(std::ostream& output, const OrderList &orderlist);

private:
    std::vector<Order*> vec_order_list; //store the orders
    std:: string effect = "effect printed from OrderList Object";
};


//free function
void testOrdersList();
void testOrderExecution();

#endif //TEST_ORDERS_H
