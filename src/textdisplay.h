#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "board.h"
#include "player.h"

using namespace std;

class TextDisplay {
    Board *b;
    public:
    TextDisplay(Board *b);
    void printAbilities(Player *p);
    void printWinner(Player *p, int player);
    ~TextDisplay();
};

#endif
