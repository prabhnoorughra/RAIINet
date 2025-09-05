#include "empty.h"
#include <string>
#include <stdexcept>
using namespace std;

Empty::Empty(int index): Link{index, '.', "empty"} {}

char Empty::getSymbol() const {
	return this->symbol;
}

string Empty::getType() const {
	return this->type;
}

int Empty::getPlayer() const {
	return 0;
}

int Empty::getStrength() const {
	return 0;
}

void Empty::setRevealed(bool reveal) {
	return;
}

bool Empty::getRevealed() const {
	return false;
}

bool Empty::getBoosted() const {
	return false;
}

bool Empty::getStunned() const {
	return false;
}

string Empty::print() const {
	return ".";
}

void Empty::setBoosted(bool boost) {
	return;
}

void Empty::setStunned(bool stun) {
	return;
}

void Empty::setStrength(int x) {
	return;
}

bool Empty::getOnFirewall() const {
	return false;
}

void Empty::setOnFirewall(bool onFirewall) {
	return;
}
