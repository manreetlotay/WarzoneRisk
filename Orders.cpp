//
// Created by hengy on 11/9/2023.
//
#include "Orders.h"

#include <utility>


Order::Order()
{
    std::cout<<"Order default constructor called"<< endl;
}

Order::~Order()
{

}
Order::Order(const Order& O)
{
    this->effect = O.effect;
    this->vecType = *new vector<string>(O.vecType);
    this->typeID = *new int(O.typeID);
}

Order &Order::operator=(const Order &O) {
    description = O.description;
    isExecuted = O.isExecuted;
    return *this;
}

std::string Order::getDescription() const {
    return description;
}

bool Order::hasExecuted() const {
    return isExecuted;
}

bool Order::validate()
{
    cout << "Validating Order" << endl;
    valid = true;
}

void Order::execute()
{
    if (valid) {
        cout << "Executing Action" << endl;
    }
}

void Order::setTypeID(int num)
{
    typeID = num;
}

string Order::getType()
{
    return vecType.at(typeID);
}

std :: ostream& operator<<(std::ostream& output, const Order &order){
    cout << "Object order"<< endl;
    if (order.valid){
        cout << "Order attribute"<< endl;
    }
    return output;
}

OrderList:: OrderList(){
    std :: cout<<"Orderlist object created"<<endl;
}

OrderList :: ~OrderList(){
    for(Order* order: vec_order_list){
        order = nullptr;
    }
}

OrderList :: OrderList(const OrderList& exsistingOrderList){
    this-> vec_order_list = exsistingOrderList.vec_order_list;
}

void OrderList::set_order_list(Order* an_order)
{
    vec_order_list.push_back(an_order); //add an order
}

vector<Order*>* OrderList::get_order_list()
{
    return &vec_order_list;
}

void OrderList::remove(Order* oneOrder)
{
    for (int i = 0; i < vec_order_list.size(); i++) {
        if (oneOrder->getType() == vec_order_list.at(i)->getType()) {
            cout << "Removing order " << oneOrder->getType() << endl;
            vec_order_list.erase(vec_order_list.begin() + i);
            return;
        }
    }
}

void OrderList::move(int position, int newPosition)
{
    if (position >= 0 && position < vec_order_list.size() && newPosition >= 0 && newPosition < vec_order_list.size())
    {
        vec_order_list.insert(vec_order_list.begin() + newPosition, vec_order_list.at(position));
        vec_order_list.erase(vec_order_list.begin() + position);
    }
    else if (newPosition == vec_order_list.size()  )
    {
        vec_order_list.push_back(vec_order_list.at(position));
        vec_order_list.erase(vec_order_list.begin() + position);
    }
    else {
        cout << "\n not valid position" << endl;
    }
}

OrderList& OrderList ::operator=(const OrderList& orderList){
    this->vec_order_list = orderList.vec_order_list;
    return *this;
}

std :: ostream& operator<<(std::ostream& output, const OrderList &orderList){
    std:: vector<Order*> temp = orderList.vec_order_list;
    for (int i = 0; !temp.empty(); i++){
        Order* obj = temp.front();
        cout<<to_string(i)<< endl;
        cout<<*obj<<endl;
    }
    return output;
}

void OrderList::addOrder(Order *order) {
    vec_order_list.push_back(order);
}


Deploy::Deploy()
{
    cout << "Deploying..." << endl;
    setTypeID(0);
}

Deploy::~Deploy()
{
}

string* Deploy::getType()
{
    return &type1;
}


std :: ostream& operator<<(std::ostream& output, const Deploy &deploy){
    cout << "Object Deploy"<< endl;
    if (deploy.valid){
        cout << "Deploy attribute"<< endl;
    }
    return output;
}

Advance::Advance()
{
    cout << "Advancing..." << endl;
    setTypeID(1);
}

Advance::~Advance()
{
}

std :: ostream& operator<<(std::ostream& output, const Advance &advance){
    cout << "Object Advnace"<< endl;
    if (advance.valid){
        cout << "Advacne attribute"<< endl;
    }
    return output;
}

Bomb::Bomb()
{
    cout << "Bombing..." << endl;
    setTypeID(2);
}

Bomb::~Bomb()
{
}
std :: ostream& operator<<(std::ostream& output, const Bomb &bomb){
    cout << "Object Bomb"<< endl;
    if (bomb.valid){
        cout << "Bomb attribute"<< endl;
    }
    return output;
}

Blockade::Blockade()
{
    cout << "Bloackade incoming..." << endl;
    setTypeID(3);
}

Blockade::~Blockade()
{
}

std :: ostream& operator<<(std::ostream& output, const Blockade &blockade){
    cout << "Object Blockade"<< endl;
    if (blockade.valid){
        cout << "Blockade attribute"<< endl;
    }
    return output;
}

Airlift::Airlift()
{
    cout << "Airlifitng..." << endl;
    setTypeID(4);
}

Airlift::~Airlift()
{
}

std :: ostream& operator<<(std::ostream& output, const Airlift &airlift){
    cout << "Object Airlift"<< endl;
    if (airlift.valid){
        cout << "Airlift attribute"<< endl;
    }
    return output;
}

Negotiate::Negotiate()
{
    cout << "Negotiating..." << endl;
    setTypeID(5);
}

Negotiate::~Negotiate()
{
}

std :: ostream& operator<<(std::ostream& output, const Negotiate &negotiate){
    cout << "Negotiate Deploy"<< endl;
    if (negotiate.valid){
        cout << "Negotiate attribute"<< endl;
    }
    return output;
}

Advance::Advance(Territory *source, Territory *target, int armies, Map* gameMap, std::string  player)
        : sourceTerritory(source), targetTerritory(target), numberOfArmies(armies), gameMap(gameMap), issuingPlayer(std::move(player))
{
    description = "Advance " + std::to_string(armies) + " from " + source->getName() + " to " + target->getName() + " by player " + issuingPlayer;
}

Advance &Advance::operator=(const Advance &other) {
    isExecuted = other.isExecuted;
    sourceTerritory = other.sourceTerritory;
    targetTerritory = other.targetTerritory;
    numberOfArmies = other.numberOfArmies;
}

bool Advance::validate() {
    if(sourceTerritory->getPlayer() != issuingPlayer){
        return false;
    }
    valid = false;
    vector<string> adjacent= gameMap->getAdjacent(sourceTerritory->getName());
    for(auto elem: adjacent) if(elem == targetTerritory->getName()) valid = true;
    return valid;
}

void Advance::execute() {
    if(valid){
        if (targetTerritory->getPlayer() != issuingPlayer){
            cout<<" Commencing Battle"<<endl;
        }
        else{
            sourceTerritory->setArmies(sourceTerritory->getArmies() - numberOfArmies);
            targetTerritory->setArmies(targetTerritory->getArmies() - numberOfArmies);
        }
        isExecuted = true;
    } else{
        std::cout<<"Advance order is invalid"<<std::endl;
    }
}

Airlift::Airlift(Territory *source, Territory *target, int armies, std::string  player)
        : sourceTerritory(source), targetTerritory(target), numberOfArmies(armies), issuingPlayer(std::move(player))
{
    description = "Airlift " + std::to_string(armies) + " from " + source->getName() + " to " + target->getName() + " by " + issuingPlayer;
}

Airlift &Airlift::operator=(const Airlift &other) {
    isExecuted = other.isExecuted;
    sourceTerritory = other.sourceTerritory;
    targetTerritory = other.targetTerritory;
    numberOfArmies = other.numberOfArmies;
}

bool Airlift::validate() {
    if(sourceTerritory == nullptr || targetTerritory == nullptr){
        return false;
    }
    return sourceTerritory->getPlayer() == issuingPlayer && targetTerritory->getPlayer() == issuingPlayer;
}

void Airlift::execute() {
    if(valid){
        if (valid){
            int currentSArmy = sourceTerritory->getArmies();
            int currentTArmy = targetTerritory->getArmies();

            if(numberOfArmies <= currentSArmy){
                sourceTerritory->setArmies(currentSArmy - numberOfArmies);
                targetTerritory->setArmies(currentTArmy + numberOfArmies);
                isExecuted = true;
            } else{
                std::cout <<"Not enough army to execute airlift" << std::endl;
            }
        }else{
            std::cout<<"Airlift order is invalid"<< std::endl;
        }
    }
}

Blockade::Blockade(Territory *target, std::string  player)
        : targetTerritory(target), issuingPlayer(std::move(player))
{
    description = "Blockade " + target->getName() + " by " + issuingPlayer;
}

bool Blockade::validate() {
    if(targetTerritory == nullptr){
        return false;
    }
    return targetTerritory->getPlayer() == issuingPlayer;
}

void Blockade::execute() {
    if(validate()){
        targetTerritory->setArmies(targetTerritory->getArmies() * 2);
        targetTerritory->setPlayer("Neurtral");
        isExecuted = true;
        cout <<"Block executed "<< targetTerritory->getName() <<" Armies doubled and ownership transferred to Neutral." << endl;

    }else{
        cout<<"Blockade order invalid"<< endl;
    }
}

Bomb::Bomb(Territory *target, std::string  player, Map* gameMap)
        : targetTerritory(target), issuingPlayer(std::move(player)), gameMap(gameMap) {
    description = "Bomb " + target->getName() + " by " + issuingPlayer;
}

Bomb &Bomb::operator=(const Bomb &other) {
    if(this != &other){
        isExecuted = other.isExecuted;
        targetTerritory = other.targetTerritory;
        issuingPlayer = other.issuingPlayer;
        gameMap = other.gameMap;
    }
    return *this;
}

bool Bomb::validate() {
    if(targetTerritory == nullptr){
        return false;
    }
    if(targetTerritory->getPlayer() == issuingPlayer){
        return false;
    }
    for(Territory* owned : gameMap->getTerritories()){
        if(owned != nullptr && owned->getPlayer() == issuingPlayer){
            vector<string> adjacent = gameMap->getAdjacent(owned->getName());
            for(auto i : adjacent) if(i == targetTerritory->getName()) return true;
        }
    }
    return false;
}

void Bomb::execute() {
    if(validate()){
        int currentArmy = targetTerritory->getArmies();
        targetTerritory->setArmies(currentArmy/2);
        isExecuted = true;
        std::cout<<"Successfully bombed" << targetTerritory->getName() << "Armies reduce to" << targetTerritory->getArmies() << std::endl;
    } else {
        std::cout<< "Bomb order is invalid" << std::endl;
    }
}









