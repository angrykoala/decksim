//Programmed by Demiurgos
//Decksim: Deck Generators
//Version:0.3
//Some deck generators

//generates a full poker deck to test deck class
//if jokers==true, generates two extra cards on the deck (jokers)
deck_config poker_deck_generator(bool jokers) {
    string n="Poker";
    card_num max=13;
    vector<suit_name> p;
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
    return generate_deck(n,max,p,m,erased,extra);
}

//generates a full spanish_deck of 48 cards
//if short_deck==true, it erases the 8 and 9 cards, being the deck of 40 cards
//if comodin==true, adds two extra cards on the deck (comodines)
deck_config spanish_deck_generator(bool short_deck,bool comodin) {
    string n="Spanish";
    card_num max=12;
    vector<suit_name> p;
    p.push_back("Oros");
    p.push_back("Bastos");
    p.push_back("Espadas");
    p.push_back("Copas");
    map<card_num,card_name> m;
    m.insert(make_pair(10,"Sota"));
    m.insert(make_pair(11,"Caballo"));
    m.insert(make_pair(12,"Rey"));
    set<card_num> erased;
    if(short_deck==true) {
        erased.insert(8);
        erased.insert(9);
    }
    vector<card_name> extra;
    if(comodin==true) {
        extra.push_back("Comodin");
        extra.push_back("Comodin");
    }
    return generate_deck(n,max,p,m,erased,extra);
}

//similar to the poker(english) deck, but without jokers and different names
deck_config french_deck_generator() {
    string n="French";
    card_num max=13;
    vector<suit_name> p;
    p.push_back("Pique");
    p.push_back("Coeur");
    p.push_back("Trefle");
    p.push_back("Carreau");
    map<card_num,card_name> m;
    m.insert(make_pair(11,"Valet"));
    m.insert(make_pair(12,"Dame"));
    m.insert(make_pair(13,"Roi"));
    set<card_num> erased;
    vector<card_name> extra;
    return generate_deck(n,max,p,m,erased,extra);
}

//German deck of 36 cards
deck_config german_deck_generator() {
    string n="German";
    card_num max=14;
    vector<suit_name> p;
    p.push_back("Schellen");
    p.push_back("Herz");
    p.push_back("Gras");
    p.push_back("Eichel");
    map<card_num,card_name> m;
    m.insert(make_pair(11,"Bauer"));
    m.insert(make_pair(12,"Dame"));
    m.insert(make_pair(13,"König"));
    m.insert(make_pair(14,"Daus"));
    set<card_num> erased;
    erased.insert(1);
    erased.insert(2);
    erased.insert(3);
    erased.insert(4);
    erased.insert(5);
    vector<card_name> extra;
    return generate_deck(n,max,p,m,erased,extra);
}