#include "player.h"

using namespace std;

Player::Player(int virusCount, int dataCount) {}

int Player::getVirusCount() const {
    return virusCount;
}

void Player::addVirusCount() {
    virusCount = virusCount + 1;
}

int Player::getDataCount() const {
    return dataCount;
}

void Player::addDataCount() {
    dataCount = dataCount + 1;
}

void Player::assignLinks(int index, char sym, int player, int strength, char type) {
    if (type == 'V') {
        links.emplace_back(make_unique<Virus>(index, sym, player, strength));
    } else {
        links.emplace_back(make_unique<Data>(index, sym, player, strength));
    }
}

void Player::assignAbilities(char abilitySym) {
    if (abilitySym == 'L') {
        abilities[0] = abilities[0] + 1;
    } else if (abilitySym == 'F') {
        abilities[1] = abilities[1] + 1;
    } else if (abilitySym == 'D') {
        abilities[2] = abilities[2] + 1;
    }  else if (abilitySym == 'S') {
        abilities[3] = abilities[3] + 1;
    } else if (abilitySym == 'P') {
        abilities[4] = abilities[4] + 1;
    } else if (abilitySym == 'T') {
        abilities[5] = abilities[5] + 1;
    } else if (abilitySym == 'B') {
        abilities[6] = abilities[6] + 1;
    } else if (abilitySym == 'G') {
        abilities[7] = abilities[7] + 1;
    } 
}

void Player::minusAbility(int index) {
    abilities[index] = abilities[index] - 1;
    usedAbilities[index] = usedAbilities[index] + 1;
}

void Player::revealLink(char symbol) {
    for(auto it = links.begin(); it != links.end(); ++it) {
        if((*it)->getSymbol() == symbol) {
            (*it)->setRevealed(true);
            break;
        }
    }
}

Link *Player::getLink(char symbol) {
    for(auto it = links.begin(); it != links.end(); ++it) {
        if((*it)->getSymbol() == symbol) {
            return (*it).get();
        } else {
            continue;
        }
    }
    return nullptr;
}

Player::~Player() {}
