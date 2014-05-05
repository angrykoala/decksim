//Programmed by Demiurgos
//Decksim: card.h
//Version:0.3
//Stores the information of a card

typedef unsigned short card_num;
typedef string suit_name,card_name;

struct card {
    suit_name suit;
    card_name name; //name of card, if it has
    card_num num; //Number of card

    bool operator==(const card &c) const {
        bool b=true;
        if(suit!=c.suit) b=false;
        else if(name!=c.name) b=false;
        else if(num!=c.num) b=false;
        return b;
    }
};

//creates a card
card create_card(card_num num,const suit_name &pn) {
    card c;
    c.num=num;
    c.suit=pn;
    return c;
}
//creates a card with name
card create_card(card_num num,const suit_name &pn,const card_name &nam) {
    card c;
    c.num=num;
    c.suit=pn;
    c.name=nam;
    return c;
}
