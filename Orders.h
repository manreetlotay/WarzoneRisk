//
// Created by hengy on 11/10/2023.
//
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Map.h"
#include "LoggingObserver.h"

#include "Player.h"
using namespace std;
class Player;
//class Territory;
//class Continent;
//class Map;

class Order : public Subject, public ILoggable
{
public:
    virtual ~Order();
    friend ostream &operator<<(ostream &output, const Order & order);
    virtual Order* clone() const = 0;
    void execute();
    virtual bool validate() const = 0;
    int getPriority() const;
    string getType();
    static std::vector<Player*> getDiplomaticRelations();
    static void addDiplomaticRelation(Player* player);
    string stringToLog() override;
    int typeID;

protected:
    Order();
    Order(Player* issuePlayer, int priority);
    Order(const Order &order);
    const Order &operator=(const Order &order);
    virtual void execute_() = 0;
    virtual ostream &print_(ostream &output) const = 0;
    Player* issuePlayer;

private:
    int priority;
    vector<string> vecType = { "deploy", "advance", "bomb", "blockade", "airlift", "negotiate" };
    //int typeID;
    void setTypeID(int num);
    static std::vector<Player*> diplomaticRelations;
    Map *gameMap;
};

class OrderList : public Subject, public ILoggable
{
public:

    OrderList();
    OrderList(const OrderList& list);
    ~OrderList();
    void addOrder(Order* order);
    void set_order_list(Order* an_order);
    vector<Order*>* get_order_list();
    void remove(Order* oneOrder);
    void move(int position, int newPosition);
    OrderList& operator=(const OrderList& orderList);
    friend std :: ostream& operator<<(std::ostream& output, const OrderList &list);
    string stringToLog() override;
    std::vector<Order*> vec_order_list; //store the orders

private:
    //std::vector<Order*> vec_order_list; //store the orders
    std:: string effect = "effect printed from OrderList Object";
};

class Deploy : public Order{
public:
    Deploy();
    Deploy(Player* issuer, int numberOfArmy, Territory* target);
    Deploy(const Deploy &order);
    const Deploy &operator=(const Deploy &order);
    Order* clone() const;
    void addArmies(int additional);
    bool validate() const;
    ~Deploy();
    string stringToLog() override;

protected:
    void execute_();
    ostream &print_(ostream &output) const;

private:
    int numberOfArmy;
    Territory* target;
};

class Advance : public Order{
    Advance(const Advance &order);
    const Advance &operator=(const Advance &order);
    Order* clone() const;

public:
    Advance();

    Advance(Player* issuer, int numberOfArmy, Territory* source, Territory* target);

    ~Advance();

    bool validate() const;
    string stringToLog() override;

protected:
    void execute_();
    ostream &print_(ostream &output) const;

private:
    int numberOfArmy;
    Territory* source;
    Territory* target;
};

class Bomb : public Order
{
public:
    Bomb();
    Bomb(Player* issuer, Territory* target);
    Bomb(const Bomb &order);
    const Bomb &operator=(const Bomb &order);
    Order* clone() const;
    bool validate() const;
    ~Bomb();
    string stringToLog() override;

protected:
    void execute_();
    ostream &print_(ostream &output) const;

private:
    Territory* target;
};

class Blockade : public Order
{
public:
    Blockade();
    Blockade(Player* issuer, Territory* territory);
    Blockade(const Blockade &order);
    const Blockade &operator=(const Blockade &order);
    Order* clone() const;
    bool validate() const;
    ~Blockade();
    string stringToLog() override;

protected:
    void execute_();
    ostream &print_(ostream &output) const;

private:
    Territory* territory;
};

class Airlift: public Order
{
public:
    Airlift();
    Airlift(Player* issuer, int numberOfArmies, Territory* source, Territory* destination);
    Airlift(const Airlift &order);
    const Airlift &operator=(const Airlift &order);
    Order* clone() const;
    bool validate() const;
    ~Airlift();
    string stringToLog() override;

protected:
    void execute_();
    ostream &print_(ostream &output) const;

private:
    int numberOfArmy;
    Territory* source;
    Territory* target;
};

class Negotiate : public Order
{
public:
    Negotiate();
    Negotiate(Player* issuer, Player* target);
    Negotiate(const Negotiate &order);
    const Negotiate &operator=(const Negotiate &order);
    Order* clone() const;
    bool validate() const;
    ~Negotiate();
    string stringToLog() override;

protected:
    void execute_();
    ostream &print_(ostream &output) const;

private:
    Player* targetPlayer;
};


void testOrderExecution();