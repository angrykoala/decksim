//Programmed by Demiurgos
//Decksim: deck.cpp
//Version:V0.7

//This program is only for testing purposes

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


//Using decksim, this program will generate a poker deck
int main() {
    deck_config cnf=poker_deck_generator(false); //new poker deck generator
    deck poker(cnf); //generates de deck using configuration
    cout<<poker<<endl<<endl; //show deck
    poker.american_shuffle(4); //american shuffle with 4 cards error
    deck d2; //new empty deck
    d2=poker.cut(26); //d2 will be the top cut of first deck
    cout<<poker<<endl<<endl; //show the deck (bottom half)
    cout<<d2<<endl; //show top half
}

