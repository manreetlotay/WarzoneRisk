////////////////////////////////////////////
//
//      CARDS.CPP
//
// IMPLEMENTATION FILE FOR CARDS.H
//
////////////////////////////////////////////


// INCLUDES ////////////////////////////////
#include <iostream>
#include <random>
#include <stdio.h>
#include <string>
#include <cstring>
#include <array>

#include "Cards.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;



// CARD METHODS /////////////////////////////

// Card constructor which is initialized with a passed value : {B,R,L,A,D}
// Switch means whichever is passed also initializes a corresponding action.
Card::Card(char cardvalue) : cardvalue(cardvalue)
{
    switch (cardvalue) 
    {
        case 'B':
            cardaction = "Bomb";
            break;
        case 'R':
            cardaction = "Reinforcement";
            break;
        case 'L':
            cardaction = "Blockade";
            break;
        case 'A':
            cardaction = "Airlift";
            break;
        case 'D':
            cardaction = "Diplomacy";
            break;
    }
};

// Copy constructor - copies cardvalue of othercard and cardaction of othercard when called.
// CLASS::METHOD(constructor)(pass othercard by const reference):
// so othercard is a reference to a const Card value, that is, an address to a const Card type.
// 
Card::Card(const Card& othercard) : cardvalue(othercard.cardvalue), cardaction(othercard.cardaction)
{

};

// Assignment Operator
// https://www.geeksforgeeks.org/copy-constructor-vs-assignment-operator-in-c/
// Returns a reference to (an address of) Card type. For class Card, 
// operator reserved keyword means c1 = c2 is the same as c2.operator(c1)
Card& Card::operator=(const Card& othercard)
{
    // If "this" instanced card is the same as the passed card,
    // return only the address to this. 
    if (this == &othercard)
    {
        return *this;
    }
    // Otherwise, manually set the private values in this
    // object to othercard's attributes, and return the pointer
    // to the newly instanced object. 
    cardvalue = othercard.cardvalue;
    cardaction = othercard.cardaction;
    return *this;
};

// Stream operator overloads << to simplify output of Card object to cout stream.
// https://learn.microsoft.com/en-us/cpp/standard-library/overloading-the-output-operator-for-your-own-classes?view=msvc-170
// This allows cout to accept the object by overloading the << output stream operator.
// declared as a friend class in the header file so that private data cardvalue/cardaction can be
// accessed. 
std::ostream& operator<<(std::ostream& stream, const Card& card)
{
    stream << "Card " << card.cardvalue << ": " << card.cardaction;
    return stream;
};

// Card play just prints the value and the action.
void Card::Play()
{
    std::cout << "Card Played : " << cardvalue << " | Action : " << cardaction << std::endl;

};


///////////////////////////////////////////////////////////






// DECK ///////////////////////////////////////////////////

// Default constructor
Deck::Deck()
{}

// Deck Constructor w/ Initialization with size 5*N (one of each type of card)
Deck::Deck(int N)
{
    // Preload the deck with 5*N cards
    for (int i = 0; i < N; ++i)
    {
        cards.push_back(new Card('B'));
        cards.push_back(new Card('R'));
        cards.push_back(new Card('L'));
        cards.push_back(new Card('A'));
        cards.push_back(new Card('D'));
    }

    // Seed random number generator
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Pre-existing Shuffle Function between first cards value and last.
    std::random_shuffle(cards.begin(), cards.end());
};

// Deck Copy Constructor, when passed the address of
// another deck copy its contents into a new object.
// cards is the vector<Card*> in the instanced deck,
// its private but callable within the scope.
Deck::Deck(const Deck& otherdeck)
{
    for (Card* card : otherdeck.cards)
    {
        cards.push_back(new Card(*card));
    }
};

// Assignment Operator
Deck& Deck::operator=(const Deck& otherdeck)
{
    // If instancedClass has the same address as otherdeck, return the
    // address for instancedClass, since they are the same
    if (this == &otherdeck)
    {
        return *this;
    }

    // Delete any previous values in the private vector
    // cards of this instancedClass and clear
    for (Card* card : cards)
    {
        delete card;
    }
    cards.clear();

    // One by one add new card pointers from cards
    // to the cards that is in the instanced class
    for (Card* card : otherdeck.cards)
    {
        cards.push_back(new Card(*card));
    }

    // Return the pointer to this object. 
    return *this;
};

// Deck Destructor to free up memory from any instanced
// deck object. The destructor is automatically invoked.
Deck::~Deck()
{
    for (Card* card : cards)
    {
        delete card;
    }
    cards.clear();
};

// Draw a card from the deck, add it to the hand and remove it from the deck.
void Deck::Draw(std::vector<Card*>& hand)
{
    if (!cards.empty())
    {
        if (!cards.empty())
        {
            Card* carddrawn = cards.back();          // Copies drawn card
            hand.push_back(carddrawn);               // Adds card to hand
            cards.pop_back();                        // Deletes card from deck
        }
    }
};

// Getter for returning the cardvalue char
char Card::getValue()
{
    return cardvalue;
};

// Getter for returning the cardaction string describing the cards action
std::string Card::getAction()
{
    return cardaction;
};

// Print the deck as it is (ie cards removed)
void Deck::printDeck()
{

    for (int i = 0; i < cards.size(); i++)
    {
        Card* c = cards.at(i);
        string count = to_string(i);

        std::cout << "[" << count << "]" << c->getValue() << endl;
    }

    int sz = cards.size();
    string cSz = to_string(sz);
    cout << "Size of cards is " << cSz << endl;

};

// Add a Card* to the vector<Card*> cards inside the Deck.
void Deck::addCard(Card* c)
{
    cards.push_back(c);
};


//////////////////////////////////////////////////////////




// HANDS /////////////////////////////////////////////////

// Default constructor
Hand::Hand()
{}

// Copy Constructor
Hand::Hand(const Hand& otherhand)
{
    for (Card* card : otherhand.hand)
    {
        hand.push_back(new Card(*card));
    }
}

// Assignment Operator
Hand& Hand::operator=(const Hand& otherhand)
{
    if (this == &otherhand)
    {
        return *this;
    }
    for (Card* card : hand)
    {
        delete card;
    }
    hand.clear();
    for (Card* card : otherhand.hand)
    {
        hand.push_back(new Card(*card));
    }
    return *this;
}

// Destructor
Hand::~Hand()
{
    for (Card* card : hand)
    {
        delete card;
    }
    hand.clear();
}

// Return a pointer to the private cards in self
vector<Card*>* Deck::getcards()
{
    return &cards;
}

// Remove the first c character found from a hand
// and return the card pointer
Card* Hand::removeHand(char c)
{
    for (int i = 0; i < hand.size(); ++i)
    {
        Card* card = hand.at(i);
        if (card->getValue() == c)
        {
            std::cout << " remove the card " << c << " and return it as a card*" << std::endl;
            hand.erase(hand.begin() + i);
            return card;
        }
    }
}


// This plays all the cards in the hand and
// returns them to the deck.
Deck Hand::PlayAll(Deck d)
{
    for (int i = 0; i < hand.size(); ++i)
    {
        Card* card = hand.at(i);
        card->Play();                          // Play the card

        d.addCard(card);                 // Add the card pointer back into the deck vector

        //delete card;                           // Delete the card pointer
    }
    hand.clear();
    return d;
}


void Hand::printHand()
{
    for (int i = 0; i < hand.size(); ++i)
    {
        string count = to_string(i);

        std::cout << "[" << count << "]" << hand.at(i)->getValue() << endl;
    }

    int sz = hand.size();
    string cSz = to_string(sz);
    cout << "Size of hand is " << cSz << endl;
}