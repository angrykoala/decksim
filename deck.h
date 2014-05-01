//Programmed by demiurgosoft
//Decksim: deck.h
//Version:beta 0.1
//each card has a pint and his number
typedef unsigned short card_num;
typedef string pint_name;


struct card {
    pint_name pint
    card_num num
};
//configuration for a certain deck
struct deck_config {
    unsigned short max_number; //highest number possible in each pint

    bool repeated_pint; //true if allow pints repeated on a deck
    bool repeated_numbers; //true if allows numbers repeated
    bool full_pint; //if each pint is contains a card with each number
};



/*===================================================================================*/
//a deck stores cards in a certain order
class deck {
private:
    deque<card> deck_cards;
    deck_config conf; //configuration of the deck
    set<pint_name> pints; //pints in deck
    map<card_num,string> card_names//stores numbers with different names (i.e 1=A,11=J);
    set<card_num> taken_numbers; //stores numbers "taken" from the deck (i.e decks without some numbers in the middle)
public:
    deck() {
    }
    deck(const deque<card> &cards2,deck_config conf2,map<card_num,string> cn,vector<pint_name> p,set<card_num> tn) {
        deck_cards=cards2;
        conf=conf2;
        card_names=cn;
        pints=p;
        taken_numbers=tn;
        check();
    }

    //MODIFICATION
    void add_pint(const pint_name &p) {
        pints.insert(p);
    }
    //true if added
    bool add_card(const card &c) {
        if(deck_config.max_number>=c.num && c.num!=0)
            if(is_pint(c.pint)) deck_cards.push_back(
            }
    void clear() {
        deck_cards.clear();
        pints.clear();
        card_names.clear();
        taken_numbers.clear();
        config.max_number=0;
    }



    //ACCESS
    bool is_pint(const pint_name &n) {
        ¡ const {
            if(pints.find(n)!=pints.end()) return true;
            else return false;
        }
private:
        //inserts (and overrides) a name for a number in deck_config
        void set_number_name(unsigned short num,string name) {
            card_names.erase(num); //erase the name of the card if it exists
            card_names.insert(make_pair(num,name)); //inserts name;
        }
        //returns the string of the card number according to conf
        //(if exists a certain name, return that name, if not, returns a string of the number
        string get_number_name(unsigned short num) const {
            string res;
            map<unsigned_short,string>::const_iterator it;
            it=card_names.find(num);
            if(it!=(card_names.end()) res=(*it).second; //name found
                    else res<<num; //name will be the number
                        return res;
            }
    //returns the standard_config for a full deck for a number of pints and cards
    deck_config full_deck_config(unsigned short numpints,unsigned short maxnum) const {
            deck_config dc;
            dc.max_number=maxnum;
            dc.repeated_pint=false;
            dc.repeated_numbers=false;
            dc.full_pint=true;
            return dc;
        }
        //returns standard deck_config for a not-full deck
        deck_config parcial_deck_config(unsigned short numpints,unsigned short maxnum) const {
            deck_config dc;
            dc.max_number=maxnum;
            dc.repeated_pint=true;
            dc.repeated_numbers=true;
            dc.full_pint=false;
            return dc;
        }
        //Check the deck is correct
        bool check() const {
            bool b=true;
            return b; //TODO
        }
    };
