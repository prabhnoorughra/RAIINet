#include "barrier.h"
#include <string>
#include <stdexcept>
using namespace std;

Barrier::Barrier(int index, int player): Link{index, 'X', "barrier"}, player{player} {}

char Barrier::getSymbol() const {
	return this->symbol;
}

string Barrier::getType() const {
	return this->type;
}

int Barrier::getPlayer() const {
	return player;
}

int Barrier::getStrength() const {
	return 0;
}

void Barrier::setRevealed(bool reveal) {
	return;
}

bool Barrier::getRevealed() const {
	return false;
}
bool Barrier::getBoosted() const {
	return false;
}

bool Barrier::getStunned() const {
	return false;
}
string Barrier::print() const {
	return "X";
}

void Barrier::setBoosted(bool boost) {
	return;
}

void Barrier::setStunned(bool stun) {
	return;
}

void Barrier::setStrength(int x) {
	return;
}

bool Barrier::getOnFirewall() const {
	return false;
}

void Barrier::setOnFirewall(bool onFirewall) {
	return;
}
