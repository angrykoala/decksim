//Programmed by Demiurgos
//Decksim: deck.cpp
//Version:beta 0.1
//This is only a test for deck.h and card.h
#include <iostream>
#include <deque>
#include <set>
#include <string>
#include <map>
#include <vector>
#include <cstdlib>
using namespace std;
#include "card.h"
#include "deck.h"

//generates a full poker deck to test deck class
deck poker_deck(bool jokers) {
    deck_config dc;
    string n="Poker";
    card_num max=13;
    vector<pint_name> p;
    p.push_back("Spades");
    p.push_back("Hearts");
    p.push_back("Clubs");
    p.push_back("Diamonds");
    map<card_num,card_name> m;
    m.insert(make_pair(1,"Ace"));
    m.insert(make_pair(11,"J"));
    m.insert(make_pair(12,"Q"));
    m.insert(make_pair(13,"K"));
    set<card_num> erased;
    vector<card_name> extra;
    if(jokers==true) {
        extra.push_back("Joker");
        extra.push_back("Joker");
    }
    dc=generate_deck(n,max,p,m,erased,extra);
    return deck(dc);
}
int main() {
    deck poker=poker_deck(false);
    cout<<poker<<endl<<endl;
    poker.faro_shuffle(); //makes a perfect faro
    cout<<poker<<endl<<endl;
    poker.overhand_shuffle(6,4);
    cout<<poker<<endl<<endl;
    return 0;
}

