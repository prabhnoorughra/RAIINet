#include "textdisplay.h"

using namespace std;

TextDisplay::TextDisplay(Board *b): b{b} {}

void TextDisplay::printAbilities(Player *p) {
    for (int i = 0; i < 8; ++i) {
        if (i == 0) {
            cout << i << "L(linkboost): " << p->abilities[i] << " remaining (" << p->usedAbilities[i] << " was used)" << endl;
        }
        else if (i == 1) {
            cout << i << "F(firewall): " << p->abilities[i] << " remaining (" << p->usedAbilities[i] << " was used)" << endl;
        } else if (i == 2) {
            cout << i << "D(download): " << p->abilities[i] << " remaining (" << p->usedAbilities[i] << " was used)" << endl;
        } else if (i == 3) {
            cout << i << "S(scan): " << p->abilities[i] << " remaining (" << p->usedAbilities[i] << " was used)" << endl;
        } else if (i == 4) {
            cout << i << "P(polarize): " << p->abilities[i] << " remaining (" << p->usedAbilities[i] << " was used)" << endl;
        } else if ( i == 5) {
            cout << i << "T(stun): " << p->abilities[i] << " remaining (" << p->usedAbilities[i] << " was used)" << endl;
        } else if (i == 6) {
            cout << i << "B(barrier): " << p->abilities[i] << " remaining (" << p->usedAbilities[i] << " was used)" << endl;
        } else {
            cout << i << "G(strengthboost): " << p->abilities[i] << " remaining (" << p->usedAbilities[i] << " was used)" << endl;
        }
    }
}

void TextDisplay::printWinner(Player *p, int player) {
        cout << "Player" << player << " has won the game" << endl;
}

TextDisplay::~TextDisplay() {}
