#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "link.h"
#include "data.h"
#include "virus.h"

using namespace std;

class Player {
    int virusCount;
    int dataCount;
    public:
    vector <int> abilities = {0, 0, 0, 0, 0, 0, 0, 0};
    vector <int> usedAbilities = {0, 0, 0, 0, 0, 0, 0, 0};
    //index 0 is link boost (L), index 1 is Firewall (F), index 2 is Download (D)
    //index 3 is Scan (S), index 4 is Polarize (P), index 5 is Stun (T), index 6 is Barrier (B)
    //index 7 is StrengthBoost (G)
    public:
    vector <unique_ptr<Link>> links;
    Player(int virusCount = 0, int dataCount = 0);
    int getVirusCount() const;
    void addVirusCount();
    int getDataCount() const;
    void addDataCount();
    void assignLinks(int index, char sym, int player, int strength, char type); 
    void assignAbilities(char abilitySym);
    void minusAbility(int index);
    void revealLink(char symbol);
    Link *getLink(char symbol);
    ~Player();
};

#endif
