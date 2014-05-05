//Programmed by Demiurgos
//Decksim: deck.cpp
//Version:V0.2
//This is only a test for deck.h
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
    deck poker(poker_deck_generator(false));
    srand(time(NULL));
    poker.random_shuffle();
    cout<<poker<<endl<<endl;
    poker.faro_shuffle(); //makes a perfect faro
    cout<<poker<<endl<<endl;
    //  poker.overhand_shuffle(6,4);
    //  cout<<poker<<endl<<endl;
    cin.get();
    return 0;
}

