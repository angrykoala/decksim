//Programmed by Demiurgos
//Decksim: deck.cpp
//Version:V0.5.1
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
    deck_config cnf=poker_deck_generator(false);
    deck poker(cnf);
    cout<<poker;
}

