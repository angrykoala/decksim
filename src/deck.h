//Programmed by Demiurgos
//Decksim: deck.h
//Version:0.5.1
//Emulates a deck of cards
#include "rwbin.h"
#include "card.h"
#include "deck_config.h"
#include "deck_gen.h"
class deck {
private:
    deque<card> deck_cards;
public:
    //default constructor
    deck() {
    }
    //constructor from a deck_config
    deck(const deck_config &conf) {
        if(conf.check()==false) cout<<"Warning: deck_config check()==false\n";
        if(conf.full_suit==true) { //generates a deck, filling each suit with a card for every value
            for(unsigned int i=0; i<(conf.suits).size(); i++) {
                for(unsigned int j=1; j<=conf.max_value; j++) {
                    if((conf.erased_numbers).find(j)==(conf.erased_numbers).end()) {
                        card c;
                        map<card_num,card_name>::const_iterator it;
                        c.num=j;
                        c.suit=(conf.suits)[i];
                        it=(conf.card_names).find(c.num);
                        if(it!=(conf.card_names).end()) c.name=(*it).second;
                        deck_cards.push_back(c);
                    }
                }
            }
        }
        else {
            map<suit_name,vector<card_num> >::const_iterator it;
            for(it=(conf.deck_cards).begin(); it!=(conf.deck_cards).end(); it++) {
                for(unsigned int i=0; i<((*it).second).size(); i++) {
                    card c;
                    c.num=((*it).second)[i];
                    c.suit=(*it).first;
                    map<card_num,card_name>::const_iterator it2;
                    it2=(conf.card_names).find(c.num);
                    if(it2!=(conf.card_names).end()) c.name=(*it2).second;
                    deck_cards.push_back(c);
                }
            }
        }
        //add extra cards (for example, jokers)
        for(unsigned int i=0; i<(conf.extra_cards).size(); i++) {
            card c;
            c.name=(conf.extra_cards)[i];
            deck_cards.push_back(c);
        }
    }
    //constructor from a deque
    deck(const deque<card> &cards2) {
        deck_cards=cards2;
        check();
    }
    //copy constructor
    deck(const deck &d) {
        (*this)=d;
    }
    //constructor from one card
    deck(const card &c) {
        (*this)=c;
    }
    //MODIFICATION
    void clear() {
        deck_cards.clear();
    }
    void add_bottom(const card &c) {
        deck_cards.push_back(c);
    }
    void add_top(const card &c) {
        deck_cards.push_front(c);
    }
    //takes "top" card (erasing from deck)
    card take_card() {
        card c;
        c=top();
        deck_cards.pop_front();
        return c;
    }
    //takes bottom card
    card take_bottom_card() {
        card c;
        c=bottom();
        deck_cards.pop_back();
        return c;
    }
    //removes the card of pos p from the deck
    card remove_card(unsigned int pos) {
        card c;
        if(pos<size()) {
            c=deck_cards[pos];
            deck_cards.erase(deck_cards.begin()+pos);
        }
        return c;
    }
    //ACCESS
    unsigned int size() const {
        return deck_cards.size();
    }
    //gets the information about the card, but dont remove the card
    card get_card(unsigned int pos) const {
        return deck_cards[pos];
    }
    card top() const {
        return deck_cards.front();
    }
    card bottom() const {
        return deck_cards.back();
    }
    bool empty() const {
        return deck_cards.empty();
    }
    //if exists a card
    bool is_card(const card &c) const {
        bool found=false;
        deque<card>::const_iterator it;
        for(it=deck_cards.begin(); it!=deck_cards.end() && found==false; it++) {
            if(c==(*it)) found=true;
        }
        return found;
    }
    //if exists a card with the suit
    bool is_suit(const suit_name &n) const {
        bool found=false;
        deque<card>::const_iterator it;
        for(it=deck_cards.begin(); it!=deck_cards.end() && found==false; it++) {
            if(n==(*it).suit) found=true;
        }
        return found;
    }
    //JOBS
    //removes the top package of n cards (+- err)
    deck cut(unsigned int n,unsigned short err=0) {
        deck d2;
        if(n>0) {
            deque<card>::iterator it1,it2;
            it1=deck_cards.begin();
            n=error_number(n,err);
            if(n>=size()) n=size()-1; //cant cut all the cards
            it2=deck_cards.begin()+n;
            (d2.deck_cards).assign(it1,it2); //put the cards in the new deck;
            ((*this).deck_cards).erase(it1,it2); //removes the cards from this deck
        }
        return d2;
    }
    deck half_cut(unsigned short err=0) {
        deck d2;
        d2=cut((size()/2),err);
        return d2;
    }
    //removes n cards from top and places down in the deck (+-err)
    void cut_and_complete(unsigned int n,unsigned short err=0) {
        deck d2;
        d2=cut(n,err); //cuts the deck
        (*this)+=d2; //put d2 at the end of the deck
    }
    //changes the order of all the deck  (A-B-C  --> C-B-A)
    void invert_order() {
        unsigned int max=size()/2;
        unsigned int j=size()-1;
        card t;
        for(unsigned int i=0; i<max; i++) {
            t=deck_cards[i];
            deck_cards[i]=deck_cards[j];
            deck_cards[j]=t;
            j--;
        }
    }
    //takes n cards (similar to cut wuth err=0)
    deck take_cards(unsigned int n) {
        return cut(n,0);
    }
    //Divides the deck in the packs, A-B-C, and complete the deck changing the order of these
    void triple_cut_CAB(unsigned short err) {
        deck a,b;
        unsigned int n=size()/3;
        a=cut(n,err);
        b=cut(n,err);
        a+=b; //A-B
        (*this)+=a; //C-A-B
    }
    void triple_cut_CBA(unsigned short err) {
        deck a,b;
        unsigned int n=size()/3;
        a=cut(n,err);
        b=cut(n,err);
        b+=a; //B-A
        (*this)+=b; //C-B-A
    }
    void triple_cut_BCA(unsigned short err) {
        deck a,b;
        unsigned int n=size()/3;
        a=cut(n,err);
        b=cut(n,err);
        (*this)=b+(*this); //B-C
        (*this)+=a; //B-C-A
    }
    //makes a fair shuffle to the deck (completely random) (Fisher-yates shuffle)
    void random_shuffle() {
        unsigned int siz=size();
        card c;
        unsigned int r;
        for(unsigned int i=0; i<siz; i++) {
            r=rand()%siz;
            c=deck_cards[i];
            deck_cards[i]=deck_cards[r];
            deck_cards[r]=c;
        }
    }
    //repeat random_shuffle n times
    void random_shuffle(unsigned int n) {
        for(unsigned int i=0; i<n; i++) random_shuffle();
    }
    //A shuffle makes by cutting and mixing 1-1 (+- err)
    //similar to american shuffle
    void riffle_shuffle(unsigned short err) {
        deck d2=half_cut(err); //cuts half the deck
        riffle_merge(d2,err); //merge the two decks with american shuffle
    }
    //small "cuts" that are placed down of a new deck, similar to hindu shuffle
    //ncuts indicates the number of cuts made (< ncards), these cuts are not necessarily equal
    //similar to hindu shuffle
    void overhand_shuffle(unsigned int ncuts,unsigned short err) {
        unsigned int n;
        unsigned int siz=size();
        deck d2;
        if(ncuts>siz) ncuts=siz; //the number of cuts should be <= than size
        n=siz/ncuts; //number of cards per cut
        while(size()>n) {
            d2=cut(n,err)+d2; //cut some cards and put on top of deck 2
        }
        d2=(*this)+d2;
        (*this)=d2;
    }
    //similar to american shuffle, but perfect mix
    void faro_shuffle() {
        riffle_shuffle(0);
    }
    //same as overhand_shuffle
    void hindu_shuffle(unsigned int ncuts,unsigned short err) {
        overhand_shuffle(ncuts,err);
    }
    //same as riffle
    void american_shuffle(unsigned short err) {
        riffle_shuffle(err);
    }

    //merge two decks card by card (from bottom) (starts with first package)
    //err indicates the range from 1 to err+1
    //d2 will be empty at the end of this
    void riffle_merge(deck &d2,unsigned short err) {
        deque<card> dc;
        unsigned short n;
        deque<card>::iterator it1,it2;
        while(d2.size()>0 && size()>0) {
            //first package
            n=rand()%(err+1)+1; //the error is in [1,err+1]
            if(n>size())n=size();
            it2=deck_cards.end();
            it1=it2-n;
            dc.insert(dc.begin(),it1,it2);              //insert n cards in the new deck(at the bottom)
            deck_cards.erase(it1,it2);
            //second package
            n=rand()%(err+1)+1; //the error is in [1,err+1]
            if(n>d2.size()) n=d2.size();
            it2=(d2.deck_cards).end();
            it1=it2-n;
            dc.insert(dc.begin(),it1,it2);              //insert n cards in the new deck(at the bottom)
            (d2.deck_cards).erase(it1,it2);
        }
        if(empty()==false) {
            dc.insert(dc.begin(),deck_cards.begin(),deck_cards.end());
            deck_cards.clear();
        }
        if(d2.empty()==false) {
            dc.insert(dc.begin(),(d2.deck_cards).begin(),(d2.deck_cards).end());
            (d2.deck_cards).clear();
        }
        deck_cards=dc;
    }
    //will add a card to the middle of the deck (+-err)
    void add_to_the_middle(const card &c,unsigned short err) {
        deck d2;
        d2=half_cut(err); //cut the deck in the half
        add_top(c); //add card
        (*this)=d2+(*this); //put d2 over the card
    }
    void add_to_the_middle(const deck &d,unsigned short err) {
        deck d2;
        d2=half_cut(err);
        (*this)=d2+(*this);
        (*this)=d+(*this);
    }

    void write(ofstream &out) const {
        check();
        binary_write(deck_cards,out);
    }
    void read(ifstream &input) {
        binary_read(deck_cards,input);
        check();
    }


    //OPERATORS
    //operator==
    bool operator==(const deck &d2) const {
        return deck_cards==d2.deck_cards;
    }
    // operator!=
    bool operator!=(const deck &d2) const {
        return !((*this)==d2);
    }
    // operator=
    deck &operator=(const deck &d2) {
        clear();
        if(this!=&d2) deck_cards=d2.deck_cards;
        return (*this);
    }
    //creates a deck from one card
    deck &operator=(const card &c) {
        clear();
        add_top(c);
        return (*this);
    }
    //operator +
    //add the second deck at the end of the first
    deck operator+(const deck &d2) const {
        deck d1(*this);
        d1.deck_cards.insert((d1.deck_cards).end(),(d2.deck_cards).begin(),(d2.deck_cards).end());
        return d1;
    }
    //add a card to the bottom (deck+card)
    deck operator+(const card &c) const {
        deck d(*this);
        d.add_bottom(c);
        return d;
    }
    //add the second deck at the end of the first
    deck &operator+=(const deck &d2) {
        if(this!=&d2)
            deck_cards.insert(deck_cards.end(),(d2.deck_cards).begin(),(d2.deck_cards).end());
        return (*this);
    }
    //deck+=card; add card to the bottom
    deck &operator+=(const card &c) {
        add_bottom(c);
        return (*this);
    }
    //--deck removes the first card
    deck &operator--() {
        take_card();
        return (*this);
    }
    //deck-- removes the last card
    deck operator--(int) {
        deck d(*this);
        take_bottom_card();
        return d;
    }
    card &operator[](unsigned int pos) {
        return deck_cards[pos];
    }
    const card &operator[](unsigned int pos)const {
        return deck_cards[pos];
    }

private:
    //operator <<, show the operations os the standard output
    friend ostream  &operator<< (ostream &out, const deck &d2) {
        unsigned int siz=d2.size();
        for(unsigned int i=0; i<siz; i++) {
            card c;
            c=d2.get_card(i);
            out<<c;
            if((i+1)%6==0) out<<endl;
        }
        return out;
    }
    //calculares a "random" number in [n-err,n+err] (always positive)
    unsigned int error_number(unsigned int n,unsigned int err) const {
        if(n!=0 && err!=0) { //if n==0, return 0,if err==0, return n
            if(err>n) err=n; //the error will never be biggest than n
            int err2=rand()%(err*2)+1; //the error is in [-err,+err]
            err2=err2-err;
            n=n+err2;
            if(n==0) n=1; //n cant be 0 after error
        }
        return n;
    }
    //Check the deck is correct
    void check() const {
        //Nothing here yet
    }
};

//generates a deck from two cards
deck operator+(const card &c1,const card &c2) {
    deck d(c1);
    d.add_bottom(c2);
    return d;
}
//add card to the top (card+deck)
deck operator+(const card &c, const deck &b) {
    deck d(b);
    d.add_top(c);
    return d;
}
