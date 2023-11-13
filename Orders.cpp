//
// Created by hengy on 11/10/2023.
//

#include "Orders.h"
#include "Map.h"
#include "Player.h"
#include <algorithm>
#include <iterator>
#include <math.h>



// Custom comparator to sort Orders by priority
bool compareOrders(Order* order1, Order* order2)
{
    return order1->getPriority() < order2->getPriority();
}

// Helper function to check whether a territory can be attacked by a specific player.
// Returns `true` if the attacker already owns the target territory
// OR
// if there is no diplomacy between the attacker and the owner of the target.
bool canAttack(Player* attacker, Territory* target)
{
    Player* ownerOfTarget = target->getTerritoryOwner();
    std::vector<Player*> diplomaticRelations = Order::getDiplomaticRelations();
    bool diplomacyWithOwnerOfTarget = find(diplomaticRelations.begin(), diplomaticRelations.end(), ownerOfTarget) != diplomaticRelations.end();

    if (diplomacyWithOwnerOfTarget)
    {
        cout << attacker->getPlayerID() << " and " << ownerOfTarget << " cannot attack each other for the rest of this turn. ";
    }

    return attacker == ownerOfTarget || !diplomacyWithOwnerOfTarget;
}



Order::Order(): issuePlayer(nullptr), priority(4) {}

Order::Order(Player* issuer, int priority) : issuePlayer(issuer), priority(priority) {}

Order::Order(const Order &order) : issuePlayer(order.issuePlayer), priority(order.priority) {}

// Operator overloading
const Order &Order::operator=(const Order &order)
{
    issuePlayer = order.issuePlayer;
    priority = order.priority;
    return *this;
}

ostream &operator<<(ostream &output, const Order &order)
{
    return order.print_(output);
}

void Order::setTypeID(int num)
{
    typeID = num;
}

string Order::getType()
{
    return vecType.at(typeID);
}

// Validate and execute the Order. Invalid orders will have no effect.
void Order::execute()
{
    if (validate())
    {
        execute_();
    }
    else
    {
        cout << "Order invalid. Skipping..." << endl;
    }
}

// Get order priority
int Order::getPriority() const
{
    return priority;
}

Order::~Order() {
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

std::ostream& operator<<(std::ostream& output, const OrderList &list) {
    std::vector<Order*> temp = list.vec_order_list;
    for (int i = 0; !temp.empty(); i++) {
        Order* obj = temp.front();
        cout << to_string(i) << endl;
        cout << *obj << endl;
        temp.erase(temp.begin()); // Remove the printed order from the temp vector
    }
    return output;
}

void OrderList::addOrder(Order *order) {
    vec_order_list.push_back(order);
}

Deploy::Deploy() : Order(nullptr, 1), numberOfArmy(0), target(nullptr) {}

Deploy::Deploy(Player* issuer, int numberOfArmies, Territory* destination) : Order(issuer, 1), numberOfArmy(numberOfArmies), target(destination) {}

Deploy::Deploy(const Deploy &order) : Order(order), numberOfArmy(order.numberOfArmy), target(order.target) {}

// Operator overloading
const Deploy &Deploy::operator=(const Deploy &order)
{
    Order::operator=(order);
    numberOfArmy = order.numberOfArmy;
    target; order.target;
    return *this;
}

ostream &Deploy::print_(ostream &output) const
{
    output << "[DeployOrder]";

    if (target != nullptr)
    {
        output << " " << numberOfArmy << " armies to " << target->getTerritoryName();
    }

    return output;
}

// Return a pointer to a new instance of DeployOrder.
Order* Deploy::clone() const
{
    return new Deploy(*this);
}

// Add a number of armies to deploy to the order
void Deploy::addArmies(int additional)
{
    numberOfArmy += additional;
}

// Checks that the DeployOrder is valid.
bool Deploy::validate() const
{
    if (issuePlayer == nullptr || target == nullptr)
    {
        return false;
    }
    vector<Territory*> currentPlayerTerritories = issuePlayer->getTerritoryList();
    return find(currentPlayerTerritories.begin(), currentPlayerTerritories.end(), target) != currentPlayerTerritories.end();
}

// Executes the DeployOrder.
void Deploy::execute_()
{
    target->setNumOfArmies(numberOfArmy);
    cout << "Deployed " << numberOfArmy << " armies to " << target->getTerritoryName() << "." << endl;
}

Deploy::~Deploy()= default;

Advance::Advance() : Order(), numberOfArmy(0), source(nullptr), target(nullptr) {}

Advance::Advance(Player* issuer, int numberOfArmies, Territory* source, Territory* destination)
        : Order(issuer, 4), numberOfArmy(numberOfArmies), source(source), target(destination) {}

Advance::Advance(const Advance &order)
        : Order(order), numberOfArmy(order.numberOfArmy), source(order.source), target(order.target) {}

// Operator overloading
const Advance &Advance::operator=(const Advance &order)
{
    Order::operator=(order);
    numberOfArmy = order.numberOfArmy;
    source = order.source;
    target = order.target;
    return *this;
}

ostream &Advance::print_(ostream &output) const
{
    output << "[AdvanceOrder]";

    if (source != nullptr && target != nullptr)
    {
        output << " " << numberOfArmy << " armies from " << source->getTerritoryName() << " to " << target->getTerritoryName();
    }

    return output;
}

// Return a pointer to a new instace of AdvanceOrder
Order* Advance::clone() const
{
    return new Advance(*this);
}

// Checks that the AdvanceOrder is valid.
bool Advance::validate() const
{
    if (issuePlayer == nullptr || source == nullptr || target == nullptr)
    {
        return false;
    }

    vector<Territory*> currentPlayerTerritories = issuePlayer->getTerritoryList();
    //bool hasAdjacent = source->isADJ(source->getTerritoryName(), target->getTerritoryName());
    bool validSourceTerritory = find(currentPlayerTerritories.begin(), currentPlayerTerritories.end(), source) != currentPlayerTerritories.end();
    bool hasAnyArmiesToAdvance = source->getNumOfArmies() > 0;
    return validSourceTerritory && hasAnyArmiesToAdvance && canAttack(issuePlayer, target);
}

// Executes the AdvanceOrder.
void Advance::execute_()
{

    Player* defender = target->getTerritoryOwner();
    bool offensive = issuePlayer != defender;

    // Recalculate how many armies could actually be moved (in case the state of the territory has changed due to an attack)
    int movableArmiesFromSource = min(source->getNumOfArmies(), numberOfArmy);

    if (offensive)
    {
        source->setNumOfArmies(source->getNumOfArmies()-movableArmiesFromSource);

        int defendersKilled = round(movableArmiesFromSource * 0.6);
        int attackersKilled = round(target->getNumOfArmies() * 0.7);

        int survivingAttackers = max(movableArmiesFromSource - attackersKilled, 0);
        int survivingDefenders = max(target->getNumOfArmies() - defendersKilled, 0);
        target->setNumOfArmies(target->getNumOfArmies()-defendersKilled);

        if (survivingDefenders > 0 || survivingAttackers <= 0)
        {
            source->setNumOfArmies(source->getNumOfArmies()+survivingAttackers);
            cout << "Failed attack on " << target->getTerritoryName() << " with " << survivingDefenders << " enemy armies left standing.";

            if (survivingAttackers > 0)
            {
                cout << " Retreating " << survivingAttackers << " attacking armies back to " << source->getTerritoryName() << endl;
            }
            else
            {
                cout << endl;
            }
        }
        else
        {
            //auto pos = std::find(defender->getTerritoryList().begin(), defender->getTerritoryList().end(), target->getTerritoryName());
            //issuePlayer->getTerritoryList().push_back(target);
            //defender->getTerritoryList().erase(defender->getTerritoryList().begin()+pos);
            target->setNumOfArmies(target->getNumOfArmies()+survivingAttackers);
            cout << "Successful attack on " << target->getTerritoryName() << ". " << survivingAttackers << " armies now occupy this territory." << endl;

        }
    }
    else
    {
        source->setNumOfArmies(source->getNumOfArmies()-movableArmiesFromSource);
        target->setNumOfArmies(target->getNumOfArmies()-movableArmiesFromSource);
        cout << "Advanced " << movableArmiesFromSource << " armies from " << source->getTerritoryName() << " to " << target->getTerritoryName() << "." << endl;
    }

}

Advance::~Advance()= default;

Bomb::Bomb() : Order(), target(nullptr) {}

Bomb::Bomb(Player* issuer, Territory* target) : Order(issuer, 4), target(target) {}

Bomb::Bomb(const Bomb &order) : Order(order), target(order.target) {}

// Operator overloading
const Bomb &Bomb::operator=(const Bomb &order)
{
    Order::operator=(order);
    target = order.target;
    return *this;
}

ostream &Bomb::print_(ostream &output) const
{
    output << "[BombOrder]";

    if (target != nullptr)
    {
        output << " Target: " << target->getTerritoryName();
    }

    return output;
}

// Return a pointer to a new instance of BombOrder.
Order* Bomb::clone() const
{
    return new Bomb(*this);
}

// Checks that the BombOrder is valid.
bool Bomb::validate() const
{
    if (issuePlayer == nullptr || issuePlayer == nullptr)
    {
        return false;
    }

    vector<Territory*> currentPlayerTerritories = issuePlayer->getTerritoryList();
    //bool isAdjacent = target->isADJ(target->getTerritoryName(), issuePlayer->getTerritoryList());
    bool validTargetTerritory = find(currentPlayerTerritories.begin(), currentPlayerTerritories.end(), target) == currentPlayerTerritories.end();
    return validTargetTerritory && canAttack(issuePlayer, target);
}

// Executes the BombOrder.
void Bomb::execute_()
{
    int armiesOnTarget = target->getNumOfArmies();
    target->setNumOfArmies(target->getNumOfArmies()- (armiesOnTarget / 2));
    cout << "Bombed " << armiesOnTarget / 2 << " enemy armies on " << target->getTerritoryName() << ". ";
    cout << target->getNumOfArmies() << " remaining." << endl;
}

Bomb::~Bomb() = default;

Blockade::Blockade() : Order(nullptr, 3), territory(nullptr) {}

Blockade::Blockade(Player* issuer, Territory* territory) : Order(issuer, 3), territory(territory) {}

Blockade::Blockade(const Blockade &order) : Order(order), territory(order.territory) {}

// Operator overloading
const Blockade &Blockade::operator=(const Blockade &order)
{
    Order::operator=(order);
    territory = order.territory;
    return *this;
}

ostream &Blockade::print_(ostream &output) const
{
    output << "[BlockadeOrder]";

    if (territory != nullptr)
    {
        output << " Territory: " << territory->getTerritoryName() << " (" << territory->getNumOfArmies() << " present)";
    }

    return output;
}

// Return a pointer to a new instance of BlockadeOrder.
Order* Blockade::clone() const
{
    return new Blockade(*this);
}

// Checks that the BlockadeOrder is valid.
bool Blockade::validate() const
{
    if (issuePlayer == nullptr || territory == nullptr)
    {
        return false;
    }

    vector<Territory*> currentPlayerTerritories = issuePlayer->getTerritoryList();
    return find(currentPlayerTerritories.begin(), currentPlayerTerritories.end(), territory) != currentPlayerTerritories.end();
}

// Executes the BlockadeOrder.
void Blockade::execute_()
{
    territory->setNumOfArmies(territory->getNumOfArmies());
    territory->setTerritoryOwner(nullptr); // Neutral
    cout << "Blockade called on " << territory->getTerritoryOwner()->getPlayerID() << ". ";
    cout << territory->getNumOfArmies() << " neutral armies now occupy this territory." << endl;
}

Blockade::~Blockade()  = default;

Airlift::Airlift() : Order(nullptr, 2), numberOfArmy(0), source(nullptr), target(nullptr) {}

Airlift::Airlift(Player* issuer, int numberOfArmies, Territory* source, Territory* destination)
        : Order(issuer, 2), numberOfArmy(numberOfArmies), source(source), target(destination) {}

Airlift::Airlift(const Airlift &order) : Order(order), numberOfArmy(order.numberOfArmy), source(order.source), target(order.target) {}

// Operator overloading
const Airlift &Airlift::operator=(const Airlift &order)
{
    Order::operator=(order);
    numberOfArmy = order.numberOfArmy;
    source = order.source;
    target = order.source;
    return *this;
}

ostream &Airlift::print_(ostream &output) const
{
    output << "[AirliftOrder]";

    if (source != nullptr && target != nullptr)
    {
        output << " " << numberOfArmy << " armies from " << source->getTerritoryName() << " to " << target->getTerritoryName();
    }

    return output;
}

// Return a pointer to a new instance of AirliftOrder.
Order* Airlift::clone() const
{
    return new Airlift(*this);
}

// Checks that the AirliftOrder is valid.
bool Airlift::validate() const
{
    if (issuePlayer == nullptr || source == nullptr || target == nullptr || source == target)
    {
        return false;
    }

    auto currentPlayerTerritories = issuePlayer->getTerritoryList();

    bool validSourceTerritory = find(currentPlayerTerritories.begin(), currentPlayerTerritories.end(), source) != currentPlayerTerritories.end();
    bool validDestinationTerritory = find(currentPlayerTerritories.begin(), currentPlayerTerritories.end(), target) != currentPlayerTerritories.end();
    bool hasAnyArmiesToAirlift = source->getNumOfArmies() > 0;
    return validSourceTerritory && validDestinationTerritory && hasAnyArmiesToAirlift;
}

// Executes the AirliftOrder.
void Airlift::execute_()
{
    // Recalculate how many armies could actually be moved in case the state of the territory has changed due to an attack
    int movableArmiesFromSource = min(source->getNumOfArmies(), numberOfArmy);

    source->setNumOfArmies(source->getNumOfArmies()-movableArmiesFromSource);
    target->setNumOfArmies(target->getNumOfArmies()+movableArmiesFromSource);

    cout << "Airlifted " << movableArmiesFromSource << " armies from " << source->getTerritoryName() << " to " << target->getTerritoryName() << "." << endl;
}

Airlift ::~Airlift()  = default;

Negotiate::Negotiate() : Order(), targetPlayer(nullptr) {}

Negotiate::Negotiate(Player* issuer, Player* target) : Order(issuer, 4), targetPlayer(target) {}

Negotiate::Negotiate(const Negotiate &order) : Order(order), targetPlayer(order.targetPlayer) {}

// Operator overloading
const Negotiate &Negotiate::operator=(const Negotiate &order)
{
    Order::operator=(order);
    targetPlayer = order.targetPlayer;
    return *this;
}

ostream &Negotiate::print_(ostream &output) const
{
    output << "[NegotiateOrder]";

    if (issuePlayer != nullptr && targetPlayer != nullptr)
    {
        output << " Initiator: " << issuePlayer->getPlayerID() << ", Target: " << targetPlayer->getPlayerID();
    }

    return output;
}

// Return a pointer to a new instance of NegotiateOrder.
Order* Negotiate::clone() const
{
    return new Negotiate(*this);
}

// Checks that the NegotiateOrder is valid.
bool Negotiate::validate() const
{
    if (issuePlayer == nullptr || targetPlayer == nullptr)
    {
        return false;
    }

    return issuePlayer != targetPlayer;
}

// Executes the NegotiateOrder.
void Negotiate::execute_()
{
    addDiplomaticRelation(issuePlayer);
    addDiplomaticRelation(targetPlayer);
    cout << "Negotiated diplomacy between " << issuePlayer->getPlayerID()<< " and " << targetPlayer->getPlayerID() << "." << endl;
}

Negotiate :: ~Negotiate() = default;

std::vector<Player*> Order::diplomaticRelations;

std::vector<Player*> Order::getDiplomaticRelations() {
    return diplomaticRelations;
}

void Order::addDiplomaticRelation(Player* player) {
    diplomaticRelations.push_back(player);
}


















