///////////////////////////////////////////////////
//
// CardDriver.cpp
//
//////////////////////////////////////////////////

// INCLUDES //////////////////////////////////////
#include "Cards.h"
#include<iostream>

// testCards() Free Function
//   this prints the full deck, draws 5 cards to the hand,
//   runs playAll() which plays all 5 cards in the hand and returns
//   them to the deck. The deck is printed again to show all the cards
//   have returned. Additionally, a method removeHand exists for removing
//   and playing one card at a time, should you want that functionality.
//   the test code for this is commented out. 
void testCards()
{
    // Creates a deck of cards objects as a vector.
    // d(N=10) means that 50 cards will be created, 10 of each type
    // of card. 
    Deck d(10);

    // Creates a hand object
    Hand h;

    // ADD/DRAW A CARD TO THE HAND *** colleague asked me about this. 
    // Fill the hand by repeated calls to draw()
    // each call d.Draw(h.hand) draws one card from
    // the deck and puts it in hand. 
    for (int i = 0; i < 5; ++i)
    {
        d.Draw(h.hand);
    }


    // Show the empty deck and the full hand
    // to demonstrate the state of both is different
    // after multiple draw operations
    std::cout << "Deck After Dealing out a Hand of 5 Cards : " << std::endl;
    d.printDeck();

    std::cout << "\n\n" << std::endl;

    std::cout << "A filled, 5 Card Hand and its print Method : " << std::endl;
    h.printHand();

    
    // REMOVING/PLAYING A SINGLE CARD IN HAND
    //std::cout<<"\n\n"<<std::endl;
    //Card* takencard = h.removeHand('A');
    //std::cout<<"The removed card is : "<<takencard->getValue()<<std::endl;
    // After one card is played, check again to see it was
    // properly returned to the deck.
    //std::cout << "\n\n" << std::endl;
    //std::cout << "Hand after REMOVING a single card : " << std::endl;
    //h.printHand(5);
    //std::cout << "\n\n" << std::endl;
    //std::cout << "Deck after RETURNING a single card : " << std::endl;
    //d.addCard(takencard);
    //d.printDeck(10);

    // Play all cards in the hand. 
    d = h.PlayAll(d);
    std::cout << "\n\n" << std::endl;

    // Show the HAND after removing all cards
    std::cout << "\n\n" << std::endl;
    std::cout << "Hand after REMOVING *ALL CARDS* : " << std::endl;
    h.printHand();

    // Show the DECK after removing all cards
    std::cout << "\n\n" << std::endl;
    std::cout << "Deck after RETURNING *ALL CARDS* : " << std::endl;
    d.printDeck();

}