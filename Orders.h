#pragma once
#ifndef ORDER_H
#define ORDER_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "LoggingObserver.h"
using namespace std;

class Order : public Subject, public ILoggable
{
public :

    Order();

    // Destrcutor
    ~Order();

    //copy constructor
    Order(const Order& O);

    //assignment construtor
    Order& operator = (const Order &O);

    //Check if Order is valid
    void validate();
    //Execute Order
    void execute();

    //set type of the subclass
    void setTypeID(int num);

    string getType();

    string stringToLog() override;
    // Stream instertion operator
    friend std :: ostream& operator<<(std::ostream& output, const Order& order);

private :
    bool valid;
    vector<string> vecType = { "deploy", "advance", "bomb", "blockade", "airlift", "negotiate" };
    int typeID;
    std:: string effect = "effect printed from Order Object";
};

class Deploy : public Order
{

public:
    Deploy();
    ~Deploy();
    string* getType();
    friend std :: ostream& operator<<(std::ostream& output, const Deploy &deploy);
private:
    bool valid;
    string type1 = { "deploy" };
    std:: string effect = "effect printed from Deploy Object";
};

class Advance : public Order {
public:
    Advance();
    ~Advance();
    friend std :: ostream& operator<<(std::ostream& output, const Advance &advance);

private:
    bool valid;
    std:: string effect = "effect printed from Advnace Object";
};

class Bomb : public Order
{
public:
    Bomb();
    ~Bomb();
    bool valid;
private:
    std:: string effect = "effect printed from Bomb Object";

};

class Blockade : public Order
{
public:
    Blockade();
    ~Blockade();
    friend std :: ostream& operator<<(std::ostream& output, const Blockade &blockade);
private:
    bool valid;
    std:: string effect = "effect printed from Blockade Object";
};

class Airlift : public Order
{
public:
    Airlift();
    ~Airlift();
    friend std :: ostream& operator<<(std::ostream& output, const Airlift &airlift);
private:
    bool valid;
    std:: string effect = "effect printed from Airlift Object";
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

class OrderList : public Subject, public ILoggable
{
public:

    OrderList();

    OrderList(const OrderList& exsistingOrderList);

    ~OrderList();

    // Sets the order of the list
    void set_order_list(Order* an_order);
    vector<Order*>* get_order_list();
    //Remove order from list
    void remove(Order* oneOrder);
    //Move position
    void move(int position, int newPosition);

    string stringToLog() override;

    OrderList& operator=(const OrderList& orderList);

    friend std :: ostream& operator<<(std::ostream& output, const OrderList &orderlist);

private:
    std::vector<Order*> vec_order_list; //store the orders
    std:: string effect = "effect printed from OrderList Object";
};


//free function 
void testOrdersList();

#endif