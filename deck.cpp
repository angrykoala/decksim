//Programmed by Demiurgos
//Decksim: deck.cpp
//Version:V0.4
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
    cout<<poker<<endl<<endl;
    poker.invert_order();
    cout<<poker<<endl<<endl;
    return 0;
}

