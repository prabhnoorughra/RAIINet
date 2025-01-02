#include "data.h"
#include <string>

using namespace std;

Data::Data(int index, char symbol, int player, int strength, bool revealed, bool boosted, bool stunned, bool onFirewall): Link{index, symbol,
"data"}, player{player}, strength{strength}, revealed{revealed}, boosted{boosted}, stunned{stunned}, onFirewall{onFirewall} {}

char Data::getSymbol() const {
	return this->symbol;
}

string Data::getType() const {
	return this->type;
}

int Data::getPlayer() const {
	return this->player;
}

int Data::getStrength() const {
	return this->strength;
}

void Data::setRevealed(bool reveal) {
	revealed = reveal;
}

bool Data::getRevealed() const {
	return this->revealed;
}

bool Data::getBoosted() const {
	return this->boosted;
}

bool Data::getStunned() const {
	return this->stunned;
}

string Data::print() const {
	string num = to_string(this->strength);
	string val = "D";
	string valnum = val + num;
	return valnum;
}

void Data::setBoosted(bool boost) {
	boosted = boost;
}

void Data::setStunned(bool stun) {
	stunned = stun;
}

void Data::setStrength(int x) {
	strength = x;
}

bool Data::getOnFirewall() const {
	return onFirewall;
}

void Data::setOnFirewall(bool onFirewall) {
	this->onFirewall = onFirewall;
}
