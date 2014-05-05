//Programmed by Demiurgos
//Decksim: card.h
//Version:beta 0.1
//Stores the information of a card

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
    return c;
}
