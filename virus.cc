#include "virus.h"
#include <string>

using namespace std;

Virus::Virus(int index, char symbol, int player, int strength, bool revealed, bool boosted, bool stunned, bool onFirewall): Link{index, symbol,
"virus"}, player{player}, strength{strength}, revealed{revealed}, boosted{boosted}, stunned{stunned}, onFirewall{onFirewall} {}

char Virus::getSymbol() const {
	return this->symbol;
}

string Virus::getType() const {
	return this->type;
}

int Virus::getPlayer() const {
	return this->player;
}

int Virus::getStrength() const {
	return this->strength;
}

void Virus::setRevealed(bool reveal) {
	revealed = reveal;
}

bool Virus::getRevealed() const {
	return this->revealed;
}

bool Virus::getBoosted() const {
	return this->boosted;
}

bool Virus::getStunned() const {
	return this->stunned;
}

string Virus::print() const {
	string num = to_string(this->strength);
	string val = "V";
	string valnum = val + num;
	return valnum;
}

void Virus::setBoosted(bool boost) {
	boosted = boost;
}

void Virus::setStunned(bool stun) {
	stunned = stun;
}

void Virus::setStrength(int x) {
	strength = x;
}

bool Virus::getOnFirewall() const {
	return onFirewall;
}

void Virus::setOnFirewall(bool onFirewall) {
	this->onFirewall = onFirewall;
}
