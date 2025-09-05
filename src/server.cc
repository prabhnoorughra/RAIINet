#include "server.h"
#include <string>
#include <stdexcept>
using namespace std;

Server::Server(int index, int player): Link{index, 'S', "server"}, player{player} {}

char Server::getSymbol() const {
	return this->symbol;
}

string Server::getType() const {
	return this->type;
}

int Server::getPlayer() const {
	return player;
}

int Server::getStrength() const {
	return 0;
}

void Server::setRevealed(bool reveal) {
	return;
}

bool Server::getRevealed() const {
	return false;
}
bool Server::getBoosted() const {
	return false;
}

bool Server::getStunned() const {
	return false;
}
string Server::print() const {
	return "S";
}

void Server::setBoosted(bool boost) {
	return;
}

void Server::setStunned(bool stun) {
	return;
}

void Server::setStrength(int x) {
	return;
}

bool Server::getOnFirewall() const {
	return false;
}

void Server::setOnFirewall(bool onFirewall) {
	return;
}
