decksim V0.5
============
Programmed by Demiurgosoft

Deck simulator with real shufle methods to emulate a real deck, for any type of deck and game

card.h: card struct, with number,name and suit
deck_config.h: stores the minimun data required to generate a full deck of cards of any kind (except the order of the cards)
deck.h: a deck is stored as a deque of cards, deck class implements all necessary methods to create and modify a deck of cards, as well as the different emulation of shuffles and techniques with a real deck
deck_gen.h: different pre-programmed decks to test deck.h

decksim uses cbio.h v1.1, as binary input/output methods for read/writing

The different pre-programmed decks included in deck_config.h for testing are:
Poker deck: standard poker deck with 52 cards in 4 suits, with all the cards from ace to K, with option to add 2Jokers as extra cards
Spanish_deck: spanish deck with 48 cards in 4 suits, from 1 to Rey cards, with option to add 2 comodines as extra cards and remove 8-9 cards to generate a 40-cards deck spanish deck
French deck: similar to a poker deck, with different options and without jokers
German deck: deck with 36 cards in 4 suits, cards from 6 to 14(Daus)



Some of the methods implemented in deck class to emulate real card manipulations are:
-cut: Extract in a new deck the first n cards.
-cut and complete: Extrack n cards and insert again at the bottom of the deck.
-invert order: Invert the order of all the cards (A-B-C --> C-B-A)
-triple cut: makes 3 cuts of a third of the deck and reorder them deppending on the triple cut (ABC --> CAB,CBA,BCA)
-riffle/american shuffle: cut half of the A deck in a new B deck, join A and B by mixing cards 1-1 (with an error)
-faro shuffle: same as riffle shuffle, but with a perfect cut and mix.
-overhand/hindu shuffle:makes small cuts of the deck and places them on another deck (at the top)

-Also, a fair random shuffle (fisher-yates shuffle) is incorpored thought this dont emulate a real deck manipulation

(most of these methods works with an error of n cards, given by user)


decksim is open-source and available for download at:
https://github.com/demiurgosoft/decksim
