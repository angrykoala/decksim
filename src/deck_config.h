//Programmed by Demiurgos
//Decksim: deck_config.h
//Version:0.5.1
//Stores the information to generate a deck of cards

struct deck_config {
    map<card_num,card_name> card_names; //names of cards
    set<card_num> erased_numbers; //numbers under max_value that are not in the deck
    vector<suit_name> suits; //names of suits (in the order of the suit)
    map<suit_name,vector<card_num> > deck_cards; //if full_suit==false, this map mark the cards in each suit
    vector<card_name> extra_cards; //cards with no suit nor name (for example jokers)
    string name; //name of configuration
    card_num max_value; //max value of card per suit
    bool full_suit; //true if each suit has all numbers of cards  (except erased_numbers)
    //check if the deck config is correct
    bool check()const {
        bool b=true;
        if(full_suit==true && deck_cards.empty()==false) b=false;
        else if(full_suit==false && suits.empty()==false) b=false;
        else if(full_suit==false && deck_cards.empty()==true) b=false;
        else if(full_suit==false && erased_numbers.empty()==true) b=false;
        else if(erased_numbers.empty()==false) {
            if((*(erased_numbers.begin()))<=0) b=false;
            else if((*(erased_numbers.end()--))>max_value) b=false;
        }
        return b;
    }
    //I/O FIXME
    //write the basic unit in a binary file
    void write(ofstream &out) const {
        if(check()==false) cout<<"Warning, check failed when writting deck_config\n";
        binary_write(name,out); //writes name
        binary_write(full_suit,out); //writes full_suit
        binary_write(max_value,out); //writes max_value
        binary_write(extra_cards,out); //writes extra cards vector
        binary_write(card_names,out); //writes card_names
        if(full_suit==true) {
            binary_write(suits,out);
            binary_write(erased_numbers,out);
        }
        else {
            binary_write(deck_cards,out);
        }
    }
    void read(ifstream &input) {
        binary_read(name,input); //reads name
        binary_read(full_suit,input); //reads full_suit
        binary_read(max_value,input); //reads max_value
        binary_read(extra_cards,input); //reads extra cards vector
        binary_read(card_names,input); //reads card_names
        if(full_suit==true) {
            binary_read(suits,input); //reads suits
            binary_read(erased_numbers,input); //reads erased_numbers
        }
        else {
            binary_read(deck_cards,input); //reads deck_cards
        }
        if(check()==false) cout<<"Warning, check failed when reading deck_config\n";
    }
};
//deck_config with full_suit=true
deck_config generate_deck(const string &name,card_num max_value,const vector<suit_name> &suits,const map<card_num,card_name> &card_names,const set<card_num> &erased_numbers,const vector<card_name> &extra_cards) {
    deck_config dc;
    dc.full_suit=true;
    dc.max_value=max_value;
    dc.name=name;
    dc.suits=suits;
    dc.card_names=card_names;
    dc.erased_numbers=erased_numbers;
    dc.extra_cards=extra_cards;
    if(dc.check()==false) cout<<"Warning: deck_config check()==false\n";
    return dc;
}
//deck_config with full_suit=false
deck_config generate_deck(const string &name,const map<suit_name,vector<card_num> > &deck_cards,const map<card_num,card_name> &card_names,const vector<card_name> &extra_cards) {
    deck_config dc;
    dc.full_suit=false;
    dc.name=name;
    dc.deck_cards=deck_cards;
    dc.card_names=card_names;
    dc.extra_cards=extra_cards;
    if(dc.check()==false) cout<<"Warning: deck_config check()==false\n";
    return dc;
}

