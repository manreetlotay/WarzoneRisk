// #pragma once
// #ifndef ORDERS_H
// #define ORDERS_H
// #include <iostream>
// #include <fstream>
// #include <vector>
// #include <string>

// //#include "Map.h"
// class Territory;
// class Player;

// using namespace std;

// class Order {

//     public:
//         Order();
//         ~Order();

//         //copy constructor
//         Order(const Order &O);

//         //assignment construtor
//         Order &operator=(const Order &O);

//         //Check if Order is valid
//         void validate();

//         //Execute Order
//         void execute();

//         //set type of the subclass
//         void setTypeID(int num);

//         string getType();

//         // Stream instertion operator
//         friend std ::ostream &operator<<(std::ostream &output, const Order &order);

//     private:
//         bool valid;
//         vector<string> vecType = {"deploy", "advance", "bomb", "blockade", "airlift", "negotiate"};
//         int typeID;
//         std::string effect = "effect printed from Order Object";
// };

// class Deploy : public Order {

//     public:
//         Deploy();
//         Deploy(Player *orderOwner, int armyUnits, Territory *territory); // Manreet
//         ~Deploy();
//         string *getType();
//         friend std ::ostream &operator<<(std::ostream &output, const Deploy &deploy);

//     private:
//         bool valid;
//         string type1 = {"deploy"};
//         std::string effect = "effect printed from Deploy Object";
//         // Manreet
//         Player *orderOwner;
//         int armyUnits;
//         Territory *territory;
// };

// class Advance : public Order {
//     public:
//         Advance();
//         ~Advance();
//         friend std ::ostream &operator<<(std::ostream &output, const Advance &advance);

//     private:
//         bool valid;
//         std::string effect = "effect printed from Advnace Object";
// };

// class Bomb : public Order {
//     public:
//         Bomb();
//         ~Bomb();
//         bool valid;

//     private:
//         std::string effect = "effect printed from Bomb Object";
// };

// class Blockade : public Order {
//     public:
//         Blockade();
//         ~Blockade();
//         friend std ::ostream &operator<<(std::ostream &output, const Blockade &blockade);

//     private:
//         bool valid;
//         std::string effect = "effect printed from Blockade Object";
// };

// class Airlift : public Order {
//         public:
//         Airlift();
//         ~Airlift();
//         friend std ::ostream &operator<<(std::ostream &output, const Airlift &airlift);

//     private:
//         bool valid;
//         std::string effect = "effect printed from Airlift Object";
// };

// class Negotiate : public Order {
//     public:
//         Negotiate();
//         ~Negotiate();
//         friend std ::ostream &operator<<(std::ostream &output, const Negotiate &negotiate);

//     private:
//         bool valid;
//         std::string effect = "effect printed from Negotiate Object";
// };

// class OrderList {
//     public:
//         OrderList();

//         OrderList(const OrderList &exsistingOrderList);

//         ~OrderList();

//         // Sets the order of the list
//         void set_order_list(Order *an_order);
//         vector<Order *> *get_order_list();
//         // Remove order from list
//         void remove(Order *oneOrder);
//         // Move position
//         void move(int position, int newPosition);

//         OrderList &operator=(const OrderList &orderList);

//         friend std ::ostream &operator<<(std::ostream &output, const OrderList &orderlist);

//     private:
//         std::vector<Order *> vec_order_list; // store the orders
//         std::string effect = "effect printed from OrderList Object";
// };

// // free function
// void testOrdersList();

// #endif



#ifndef ORDERS_H
#define ORDERS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Player; // Forward declaration for Player class
class Territory; // Forward declaration for Territory class

class Order {
protected:
    int typeID;
    std::vector<std::string> vecType;
    bool valid;

public:
    Order();
    virtual ~Order();
    Order(const Order& O);
    virtual void validate();
    virtual void execute();
    void setTypeID(int num);
    std::string getType();
    friend std::ostream& operator<<(std::ostream& output, const Order& order);
};

class OrderList {
private:
    std::vector<Order*> vec_order_list;

public:
    OrderList();
    ~OrderList();
    OrderList(const OrderList& existingOrderList);
    void set_order_list(Order* an_order);
    std::vector<Order*>* get_order_list();
    void remove(Order* oneOrder);
    void move(int position, int newPosition);
    OrderList& operator=(const OrderList& orderList);
    friend std::ostream& operator<<(std::ostream& output, const OrderList& orderList);
};

class Deploy : public Order {
private:
    Player* orderOwner;
    int armyUnits;
    Territory* territory;

public:
    Deploy();
    Deploy(Player* orderOwner, int armyUnits, Territory* territory);
    virtual ~Deploy();
    std::string* getType();
    friend std::ostream& operator<<(std::ostream& output, const Deploy& deploy);
};

class Advance : public Order {
public:
    Advance();
    virtual ~Advance();
    friend std::ostream& operator<<(std::ostream& output, const Advance& advance);
};

class Bomb : public Order {
public:
    Bomb();
    virtual ~Bomb();
    friend std::ostream& operator<<(std::ostream& output, const Bomb& bomb);
};

class Blockade : public Order {
public:
    Blockade();
    virtual ~Blockade();
    friend std::ostream& operator<<(std::ostream& output, const Blockade& blockade);
};

class Airlift : public Order {
public:
    Airlift();
    virtual ~Airlift();
    friend std::ostream& operator<<(std::ostream& output, const Airlift& airlift);
};

class Negotiate : public Order {
public:
    Negotiate();
    virtual ~Negotiate();
    friend std::ostream& operator<<(std::ostream& output, const Negotiate& negotiate);
};


//free function
void testOrdersList();

#endif // ORDERS_H
