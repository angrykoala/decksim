//Programmed by Demiurgos
//Decksim: deck.cpp
//Version:V0.6
//This is only a test for deck.h and do not show a real application to deck.h
#include <iostream>
#include <deque>
#include <set>
#include <string>
#include <map>
#include <vector>
#include <cstdlib>
#include <fstream>
using namespace std;
#include "deck.h"

int main() {
    deck_config cnf=poker_deck_generator(true); //Generates full poker deck configuration (with jokers) using generator
    deck poker(cnf); //generates de deck using configuration
    cout<<poker<<endl; //show the deck
    poker.american_shuffle(4); //american shuffle with 4 cards error
    poker.remove("Spades"); //removes all the cards that are of spades
    cout<<poker<<endl;
    cout<<poker.count("Hearts")<<endl; //counts all the heart cards (should be 13)
    cin.get();
}

