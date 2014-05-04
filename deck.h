//Programmed by demiurgosoft
//Decksim: deck.h
//Version:beta 0.1

typedef unsigned short card_num;
typedef string pint_name,card_name;

struct card {
    pint_name pint;
    card_name name; //name of card, if it has
    card_num num; //Number of card

    bool operator==(const card &c) const {
        bool b=true;
        if(pint!=c.pint) b=false;
        else if(name!=c.name) b=false;
        else if(num!=c.num) b=false;
        return b;
    }
};

//creates a card
card create_card(card_num num,const pint_name &pn) {
    card c;
    c.num=num;
    c.pint=pn;
    return c;
}
//creates a card with name
card create_card(card_num num,const pint_name &pn,const card_name &nam) {
    card c;
    c.num=num;
    c.pint=pn;
    c.name=nam;
}


/*===================================================================================*/
//a deck stores cards in a certain order
class deck {
private:
    deque<card> deck_cards;
public:
    deck() {
    }
    deck(const deque<card> &cards2) {
        deck_cards=cards2;
        check();
    }
    deck(const deck &d) {
        (*this)=d;
    }
    //MODIFICATION
    //true if added
    void clear() {
        deck_cards.clear();
    }
    void add_card_bottom(const card &c) {
        deck_cards.push_back(c);
    }
    void add_card_top(const card &c) {
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
    void american_shuffle(unsigned short err) {
        deck d2=cut(size()/2,err); //cuts half the deck
        american_merge(d2,err); //merge the two decks with american shuffle
    }
    //small "cuts" that are placed down of a new deck,
    //ncuts indicates the number of cuts made (< ncards), these cuts are not necessarily equal
    void hindi_shuffle(unsigned short ncuts,unsigned short err) {
    }
    //similar to american shuffle, but perfect mix
    void faro_shuffle() {
        american_shuffle(0);
    }

    //merge two decks card by card (from bottom) (starts with first package)
    //err indicates the range from 1 to err+1
    void american_merge(const deck &d2,unsigned short err) {
        deque<card> dc;
        unsigned short n;
        deque<card>::iterator it1,it2;
        while(d2.size()>0 && (*this).size()>0) {
            //first package
            n=rand()%(err+1)+1; //the error is in [1,err+1]
            if(n>(*this).size())n=(*this).size();
            //insert
            //second package
            n=rand()%(err+1)+1; //the error is in [1,err+1]
            if(n>d2.size()) n=d2.size();
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
        return (*this);
    }
    deck &operator+=(const deck &d2) {
        deck_cards.insert(deck_cards.end(),(d2.deck_cards).begin(),(d2.deck_cards).end());
        return (*this);
    }



    //operator <<
    /*   ostream& operator<< (ostream &out, const deck &d2) {
           unsigned int siz=d2.size();
           for(unsigned int i=0;i<siz;i++){
                        card c;
                        c=d2.get_card(i);
                        out<<"[";
                        if((c.name).empty()==false) out<<c.name;
                        else out<<c.num;
                        out<<",";
                        out<<c.pint;
                        }
           return out;
       }*/
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
    /*friend ostream  &operator<< (ostream &out, const deck &d2) {
        unsigned int siz=d2.size();
        for(unsigned int i=0;i<siz;i++){
                     card c;
                     c=d2.get_card(i);
                     out<<"[";
                     if((c.name).empty()==false) out<<c.name;
                     else out<<c.num;
                     out<<",";
                     out<<c.pint;
                     }
        return out;
    }*/
    //Check the deck is correct
    void check() const {
    }
};

