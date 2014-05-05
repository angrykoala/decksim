//Programmed by Demiurgos
//Decksim: deck.h
//Version:0.2
//Emulates a deck of cards
#include "cio.h"
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
        if(conf.full_pint==true) { //generates a deck, filling each pint with a card for every value
            for(unsigned int i=0; i<(conf.pints).size(); i++) {
                for(unsigned int j=1; j<=conf.max_value; j++) {
                    if((conf.erased_numbers).find(j)==(conf.erased_numbers).end()) {
                        card c;
                        map<card_num,card_name>::const_iterator it;
                        c.num=j;
                        c.pint=(conf.pints)[i];
                        it=(conf.card_names).find(c.num);
                        if(it!=(conf.card_names).end()) c.name=(*it).second;
                        deck_cards.push_back(c);
                    }
                }
            }
        }
        else {
            map<pint_name,vector<card_num> >::const_iterator it;
            for(it=(conf.deck_cards).begin(); it!=(conf.deck_cards).end(); it++) {
                for(unsigned int i=0; i<((*it).second).size(); i++) {
                    card c;
                    c.num=((*it).second)[i];
                    c.pint=(*it).first;
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
    //MODIFICATION
    //true if added
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
    //ACCESS
    unsigned int size() const {
        return deck_cards.size();
    }
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
    //removes n cards from top and places down in the deck (+-err)
    void cut_and_complete(unsigned int n,unsigned short err=0) {
        deck d2;
        d2=cut(n,err); //cuts the deck
        (*this)+=d2; //put d2 at the end of the deck
    }
    //Divides the deck in the packs, A-B-C, and complete the deck changing the order of these
    void triple_cut_CAB(unsigned int n,unsigned short err) {
        deck a,b;
        a=cut(n,err);
        b=cut(n,err);
        a+=b; //A-B
        (*this)+=a; //C-A-B
    }
    void triple_cut_CBA(unsigned int n,unsigned short err) {
        deck a,b;
        a=cut(n,err);
        b=cut(n,err);
        b+=a; //B-A
        (*this)+=b; //C-B-A
    }
    void triple_cut_BCA(unsigned int n,unsigned short err) {
        deck a,b;
        a=cut(n,err);
        b=cut(n,err);
        (*this)=b+(*this); //B-C
        (*this)+=a; //B-C-A
    }
    //makes a fair shuffle to the deck (completely random) (Fisher-yates shuffle)
    void random_shuffle() {
        //srand(time(NULL)); //new seed;
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
    //A shuffle makes by cutting and mixing 1-1 (+- err)
    //similar to american shuffle
    void riffle_shuffle(unsigned short err) {
        deck d2=cut(size()/2,err); //cuts half the deck
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
        if(this!=&d2) deck_cards=d2.deck_cards;
        return (*this);
    }
    //operator +,+=
    //add the second deck at the end of the first
    deck operator+(const deck &d2) const {
        deck d1(*this);
        d1.deck_cards.insert((d1.deck_cards).end(),(d2.deck_cards).begin(),(d2.deck_cards).end());
        return d1;
    }
    deck &operator+=(const deck &d2) {
        deck_cards.insert(deck_cards.end(),(d2.deck_cards).begin(),(d2.deck_cards).end());
        return (*this);
    }

private:

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
    //operator <<, show the operations os the standard output
    friend ostream  &operator<< (ostream &out, const deck &d2) {
        unsigned int siz=d2.size();
        for(unsigned int i=0; i<siz; i++) {
            card c;
            c=d2.get_card(i);
            out<<"[";
            if((c.name).empty()==false) out<<c.name;
            else out<<c.num;
            if((c.pint).empty()==false) {
                out<<",";
                out<<c.pint;
            }
            out<<"] ";
            if((i+1)%6==0) out<<endl;
        }
        return out;
    }
    //Check the deck is correct
    void check() const {
    }
};
