#include "firewall.h"
#include <string>
#include <stdexcept>
using namespace std;

Firewall::Firewall(int index, int player): Link{index, 'U', "firewall"}, player{player} {
	if(player == 1) {
		symbol = 'm';
	} else {
		symbol = 'w';
	}
}

Firewall::Firewall(int index, char symbol): Link{index, symbol, "firewall"},  player{0} {
	if(symbol == 'm') {
		player = 1;
	} else {
		player = 2;
	}
}

char Firewall::getSymbol() const {
	return this->symbol;
}

string Firewall::getType() const {
	return this->type;
}

int Firewall::getPlayer() const {
	return player;
}

int Firewall::getStrength() const {
	return 0;
}

void Firewall::setRevealed(bool reveal) {
	return;
}

bool Firewall::getRevealed() const {
	return false;
}
bool Firewall::getBoosted() const {
	return false;
}

bool Firewall::getStunned() const {
	return false;
}
string Firewall::print() const {
	return "F";
}

void Firewall::setBoosted(bool boost) {
	return;
}

void Firewall::setStunned(bool stun) {
	return;
}

void Firewall::setStrength(int x) {
	return;
}

bool Firewall::getOnFirewall() const {
	return false;
}

void Firewall::setOnFirewall(bool onFirewall) {
	return;
}
