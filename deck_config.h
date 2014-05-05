//Programmed by Demiurgos
//Decksim: deck.h
//Version:0.2
//Stores the information to generate a deck of cards

struct deck_config {
    map<card_num,card_name> card_names; //names of cards
    set<card_num> erased_numbers; //numbers under max_value that are not in the deck
    vector<pint_name> pints; //names of pints (in the order of the pint)
    map<pint_name,vector<card_num> > deck_cards; //if full_pint==false, this map mark the cards in each pint
    vector<card_name> extra_cards; //cards with no pint nor name (for example jokers)
    string name; //name of configuration
    card_num max_value; //max value of card per pint
    bool full_pint; //true if each pint has all numbers of cards  (except erased_numbers)
    //check if the deck config is correct
    bool check()const {
        bool b=true;
        if(full_pint==true && deck_cards.empty()==false) b=false;
        else if(full_pint==false && pints.empty()==false) b=false;
        else if(full_pint==false && deck_cards.empty()==true) b=false;
        else if(full_pint==false && erased_numbers.empty()==true) b=false;
        else if(erased_numbers.empty()==false) {
            if((*(erased_numbers.begin()))<=0) b=false;
            else if((*(erased_numbers.end()--))>max_value) b=false;
        }
        return b;
    }
    //I/O
    //write the basic unit in a binary file
    void write(ofstream &out) const {
        // if(check()==false) cout<<"Warning, check failed when writting deck_config\n";
        //TODO
    }
    void read(ifstream &input) {
        //TODO
        // if(check()==false) cout<<"Warning, check failed when reading deck_config\n";
    }
};
//deck_config with full_pint=true
deck_config generate_deck(const string &name,card_num max_value,const vector<pint_name> &pints,const map<card_num,card_name> &card_names,const set<card_num> &erased_numbers,const vector<card_name> &extra_cards) {
    deck_config dc;
    dc.full_pint=true;
    dc.max_value=max_value;
    dc.name=name;
    dc.pints=pints;
    dc.card_names=card_names;
    dc.erased_numbers=erased_numbers;
    dc.extra_cards=extra_cards;
    if(dc.check()==false) cout<<"Warning: deck_config check()==false\n";
    return dc;
}
//deck_config with full_pint=false
deck_config generate_deck(const string &name,const map<pint_name,vector<card_num> > &deck_cards,const map<card_num,card_name> &card_names,const vector<card_name> &extra_cards) {
    deck_config dc;
    dc.full_pint=false;
    dc.name=name;
    dc.deck_cards=deck_cards;
    dc.card_names=card_names;
    dc.extra_cards=extra_cards;
    if(dc.check()==false) cout<<"Warning: deck_config check()==false\n";
    return dc;
}

