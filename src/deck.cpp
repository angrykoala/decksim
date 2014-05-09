//Programmed by Demiurgos
//Decksim: deck.cpp
//Version:V0.5
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
    deck_config cnf,cnf2;
    ofstream out("poker.deck");
    cnf=poker_deck_generator(false);
    cnf.write(out);
    out.close();
    ifstream input("poker.deck"); //reads database (if exists)
    if(input) cnf2.read(input);
    input.close();
    deck poker(cnf2);
    ofstream out2("poker2.deck");
    poker.write(out2);
    out2.close();
    deck poker2;
    ifstream input2("poker2.deck"); //reads database (if exists)
    if(input2) poker2.read(input2);
    input2.close();
    srand(time(NULL));
    cout<<poker2<<endl;
    return 0;
}

