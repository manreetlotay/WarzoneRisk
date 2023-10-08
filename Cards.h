#pragma once

/////////////////////////////////////////////////////////
//
//      CARDS.H
//
// Header file, CARDS.CPP is IMPLEMENTATION FILE
//
//////////////////////////////////////////////////////////

// INCLUDE ///////////////////////////////////////////////
#include<iostream>
#include<vector>


// CARD CLASS ////////////////////////////////////////////
class Card
{
    private:
        char cardvalue;                                     // cardvalue as a character {B,R,D,A,L}
        std::string cardaction;                             // card action i.e. 'B' -> "BOMB"

    public:
        Card();                                             // Default Constructor
        Card(char cardvalue);                               // Constructor/Initialize by cardvalue
        Card(const Card& acard);                            // Constructor

        char getValue();                                    // getter for cardvalue
        std::string getAction();                            // getter for getaction

        Card& operator = (const Card& acard);               // Assignment operator 

        friend std::ostream& operator<<(std::ostream& stream, const Card& acard);       // Stream operator

        void Play();                                        // Play() method
};
///////////////////////////////////////////////////////////


// CLASS DECK /////////////////////////////////////////////
class Deck
{
private:
    std::vector<Card*> cards;

public:
    Deck();                                                // Default constructor
    Deck(int N);                                           // Constructor Init. Size of Deck
    Deck(const Deck& otherdeck);                           // Copy Constructor
    Deck& operator = (const Deck& otherdeck);              // Assignment Operator

    ~Deck();                                               // Terminator for Deck 

    void Draw(std::vector<Card*>& hand);                   // Draw a card to the hand vector         
    void addCard(Card* c);                                 // add a card pointer                               
    void printDeck();                                      // printDeck() in the state that its in                            
    std::vector<Card*>* getcards();                        // getcards() returns the vector<Card*>* to cards

};
///////////////////////////////////////////////////////////////////////


// CLASS HAND /////////////////////////////////////////////////////////
class Hand :public Deck                                    // Inherit the properties of deck in hand.
{
    private:

    public:
        std::vector<Card*> hand;                           // Data Member should be pointer type vector<Card*>* 

        Hand();                                            // Default constructor
        Hand(const Hand& otherhand);                       // Copy Constructor
        Hand& operator = (const Hand& otherhand);          // Assignment operator 
        ~Hand();                                           // Terminator for the hand object
         
        Card* removeHand(char c);                          // remove a particular card from the hand  
        void returnToDeck(Card* c, Deck* d);               // return a card to the deck    

        Deck PlayAll(Deck d);                              // PlayAll in hand, return cards to Deck
        void printHand();                                  // print the hand
};



// PROTO - FREE FUNCTION TESTCARDS ///////////////
void testCards();