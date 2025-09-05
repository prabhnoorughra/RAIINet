#include "board.h"
#include <algorithm>
#include <utility>

using namespace std;

const int notFound = -1;

Link *Board::getLink(char symbol) const { //must be a valid search, player can't move a link thats not on the board anymore
	for(auto it = board.begin(); it != board.end(); ++it) {
		if((*it)->getSymbol() == symbol) {
			return (*it).get();
		} else {
			continue;
		}
	}
	return nullptr;
}

void Board::firewall(int player, int row, int col) { //can only be used on an index that stores an empty link
	int index = (8 * row) + col;
	if(board[index]->getType() != "empty") {
		return;
	} else {
		board[index] = make_unique<Firewall>(index, player);
		changes[index] = true;
		notifyObservers();
		changes[index] = false;
	}
}

void Board::barrier(int player, int row, int col) { //can only be used on an index that stores an empty link
	int index = (8 * row) + col;
	if(board[index]->getType() != "empty") {
		return;
	} else {
		board[index] = make_unique<Barrier>(index, player);
		changes[index] = true;
		notifyObservers();
		changes[index] = false;
	}
}

void Board::stun(char symbol) { //can only be used on opponent link
	Link *target = getLink(symbol);
	target->setStunned(true);
}

void Board::linkBoost(char symbol) { //can only be used on links you control
	Link *target = getLink(symbol);
	target->setBoosted(true);
}

void Board::strengthBoost(char symbol) {//can only be used on links you control, does not change player link vector since we don't want other player to know which link we have boosted
	Link *target = getLink(symbol);
	target->setStrength(5);
}

void Board::scan(char symbol) { //Can only be used on opponents Data/Virus Link, doesnt make sense to use on your own, simply Reveals targeted Data/Virus Link
	Link *target = getLink(symbol);
	int p = target->getPlayer();
	if(p == 1) {
		player1->revealLink(symbol);
	} else {
		player2->revealLink(symbol);
	}
	notifyObservers();
}

void Board::downloadAbility(char symbol) { // Targeted OPPONENT's Data/Virus downloaded (based on the download ability, not a regular download method)
	Link *target = getLink(symbol);
	int opp = target->getPlayer();
	string type = target->getType();
	int index = target->index;
	if(opp == 1) {
		int player = 2;
		download(target, player);
	} else {
		int player = 1;
		download(target, player);
	}
	changes[index] = true;
	notifyObservers();
	changes[index] = false;
}

void Board::polarize(char symbol) { //Targeted Data/Virus Link is turned into the opposite, changes reflected in both Board and Player link vectors
	Link *target = getLink(symbol);
	int p = target->getPlayer();
	int i = target->index;
	if(target->getType() == "data") {
		board[i] = make_unique<Virus>(i, symbol, p, target->getStrength(), target->getRevealed(), target->getBoosted(), target->getStunned(), target->getOnFirewall());
		board[i]->fire = target->fire;
		if(p == 1) {
			Link *l = player1->getLink(symbol);
			int j = 0;
			for(auto it = player1->links.begin(); it != player1->links.end(); ++it) {
				if((*it)->getSymbol() == l->getSymbol()) {
					break;
				}
				++j;
			}
			player1->links[j] = make_unique<Virus>(l->index, symbol, p, l->getStrength(), l->getRevealed(), l->getBoosted(), l->getStunned(), l->getOnFirewall());
			player1->links[j]->fire = l->fire;
		} else {
			Link *l = player2->getLink(symbol);
			int j = 0;
			for(auto it = player2->links.begin(); it != player2->links.end(); ++it) {
				if((*it)->getSymbol() == l->getSymbol()) {
					break;
				}
				++j;
			}
			player2->links[j] = make_unique<Virus>(l->index, symbol, p, l->getStrength(), l->getRevealed(), l->getBoosted(), l->getStunned(), l->getOnFirewall());
			player2->links[j]->fire = l->fire;
		}
	} else {
		board[i] = make_unique<Data>(i, symbol, p, target->getStrength(), target->getRevealed(), target->getBoosted(), target->getStunned(), target->getOnFirewall());
		board[i]->fire = target->fire;
		if(p == 1) {
			Link *l = player1->getLink(symbol);
			int j = 0;
			for(auto it = player1->links.begin(); it != player1->links.end(); ++it) {
				if((*it)->getSymbol() == l->getSymbol()) {
					break;
				}
				++j;
			}
			player1->links[j] = make_unique<Data>(l->index, symbol, p, l->getStrength(), l->getRevealed(), l->getBoosted(), l->getStunned(), l->getOnFirewall());
			player1->links[j]->fire = l->fire;

		} else {
			Link *l = player2->getLink(symbol);
			int j = 0;
			for(auto it = player2->links.begin(); it != player2->links.end(); ++it) {
				if((*it)->getSymbol() == l->getSymbol()) {
					break;
				}
				++j;
			}
			player2->links[j] = make_unique<Data>(l->index, symbol, p, l->getStrength(), l->getRevealed(), l->getBoosted(), l->getStunned(), l->getOnFirewall());
			player2->links[j]->fire = l->fire;
		}
	}
	changes[i] = true;
	notifyObservers();
	changes[i] = false;
}

void Board::download(Link *l, int playerdownloading) { //must be data or virus, reveals the Link, increments data/virus count and turns that part of the board to empty link
	char s = l->getSymbol();
	int owner = l->getPlayer();
	string t = l->getType();

	if(l->getOnFirewall()) {
		board[l->index] = make_unique<Firewall>(l->index, l->fire);
		if(owner == 1) {
			player1->revealLink(s);
			if(t == "data") {
				if(playerdownloading == 1) {
					player1->addDataCount();
					return;
				} else {
					player2->addDataCount();
					return;
				}
			} else {
				if(playerdownloading == 1) {
					player1->addVirusCount();
					return;
				} else {
					player2->addVirusCount();
					return;
				}
			}
		} else {
			player2->revealLink(s);
			if(t == "data") {
				if(playerdownloading == 1) {
					player1->addDataCount();
					return;
				} else {
					player2->addDataCount();
					return;
				}
			} else {
				if(playerdownloading == 1) {
					player1->addVirusCount();
					return;
				} else {
					player2->addVirusCount();
					return;
				}
			}
		}
	}

	board[l->index] = make_unique<Empty>(l->index);
	if(owner == 1) {
		player1->revealLink(s);
		if(t == "data") {
			if(playerdownloading == 1) {
				player1->addDataCount();
			} else {
				player2->addDataCount();
			}
		} else {
			if(playerdownloading == 1) {
				player1->addVirusCount();
			} else {
				player2->addVirusCount();
			}
		}
	} else {
		player2->revealLink(s);
		if(t == "data") {
			if(playerdownloading == 1) {
				player1->addDataCount();
			} else {
				player2->addDataCount();
			}
		} else {
			if(playerdownloading == 1) {
				player1->addVirusCount();
			} else {
				player2->addVirusCount();
			}
		}
	}
}

Board::Board(Player *player1, Player *player2): player1{player1}, player2{player2}, turn{1} {
	int linkindex = 0;
	Link *tmp;
	for (int i = 0; i < 64; ++i) {
		changes.emplace_back(true);
		if (i >= 0 && i <= 2) {
			tmp = player1->links[linkindex].get();
			if (tmp->getType() == "data") {
				board.emplace_back(make_unique<Data>(tmp->index, tmp->getSymbol(), tmp->getPlayer(), tmp->getStrength()));
			} else {
				board.emplace_back(make_unique<Virus>(tmp->index, tmp->getSymbol(), tmp->getPlayer(), tmp->getStrength()));
			}
			++linkindex;
			if (linkindex == 3) linkindex = 5;
		} else if (i >= 5 && i <= 7) {
			tmp = player1->links[linkindex].get();
			if (tmp->getType() == "data") {
				board.emplace_back(make_unique<Data>(tmp->index, tmp->getSymbol(), tmp->getPlayer(), tmp->getStrength()));
			} else {
				board.emplace_back(make_unique<Virus>(tmp->index, tmp->getSymbol(), tmp->getPlayer(), tmp->getStrength()));
			}
			++linkindex;
			if (linkindex == 8) linkindex = 3;
		}else if (i == 3 || i == 4) {
			board.emplace_back(make_unique<Server>(i, 1));
		} else if (i == 59 || i == 60) {
			board.emplace_back(make_unique<Server>(i, 2));
		} else if (i == 11 || i == 12) {
			tmp = player1->links[linkindex].get();
			if (tmp->getType() == "data") {
				board.emplace_back(make_unique<Data>(tmp->index, tmp->getSymbol(), tmp->getPlayer(), tmp->getStrength()));
			} else {
				board.emplace_back(make_unique<Virus>(tmp->index, tmp->getSymbol(), tmp->getPlayer(), tmp->getStrength()));
			}
			++linkindex;
			if (linkindex == 5) linkindex = 3;
		} else if (i == 51 || i == 52) {
			tmp = player2->links[linkindex].get();
			if (tmp->getType() == "data") {
				board.emplace_back(make_unique<Data>(tmp->index, tmp->getSymbol(), tmp->getPlayer(), tmp->getStrength()));
			} else {
				board.emplace_back(make_unique<Virus>(tmp->index, tmp->getSymbol(), tmp->getPlayer(), tmp->getStrength()));
			}
			++linkindex;
			if (linkindex == 5) linkindex = 0;
		} else if (i >= 56 && i <= 58) {
			tmp = player2->links[linkindex].get();
			if (tmp->getType() == "data") {
				board.emplace_back(make_unique<Data>(tmp->index, tmp->getSymbol(), tmp->getPlayer(), tmp->getStrength()));
			} else {
				board.emplace_back(make_unique<Virus>(tmp->index, tmp->getSymbol(), tmp->getPlayer(), tmp->getStrength()));
			}
			++linkindex;
			if (linkindex == 3) linkindex = 5;
		} else if (i >= 61 && i <= 63) {
			tmp = player2->links[linkindex].get();
			if (tmp->getType() == "data") {
				board.emplace_back(make_unique<Data>(tmp->index, tmp->getSymbol(), tmp->getPlayer(), tmp->getStrength()));
			} else {
				board.emplace_back(make_unique<Virus>(tmp->index, tmp->getSymbol(), tmp->getPlayer(), tmp->getStrength()));
			}
			++linkindex;
		} else {
			board.emplace_back(make_unique<Empty>(i));
		}
	}
}

Board::~Board() {}

void Board::revealLink(Link *l) {
	if(l->getPlayer() == 1) {
		player1->revealLink(l->getSymbol());
	} else {
		player2->revealLink(l->getSymbol());
	}
}

void Board::battle(int index1, int index2) {
	board[index1]->setRevealed(true);
	board[index2]->setRevealed(true);
	revealLink(board[index1].get()); //reveals both links in each player links vector easily
	revealLink(board[index2].get());
	if (board[index2].get()->getStrength() > board[index1].get()->getStrength()) {
		this->download(board[index1].get(), board[index2]->getPlayer()); //other player wins (who is not currently doing their turn)
		return;
	} else {
		this->download(board[index2].get(), board[index1]->getPlayer()); //current player wins
		if((board[index1]->getOnFirewall()) && (board[index2]->getType() == "firewall")) { //if both links were on firewalls
			char old = board[index1]->fire;
			board[index1]->fire = board[index2]->getSymbol();
			swap(board[index1], board[index2]);
			swap(board[index1]->index, board[index2]->index);
			board[index1] = make_unique<Firewall>(board[index1]->index, old);
			return;
		}
		if(board[index1]->getOnFirewall()) { //handles if index1 was onFirewall and it won the battle
			swap(board[index1], board[index2]);
			swap(board[index1]->index, board[index2]->index);
			board[index1] = make_unique<Firewall>(board[index1]->index, board[index2]->fire);
			board[index2]->setOnFirewall(false);
			board[index2]->fire = 'x';
			return;
		}
		if(board[index2]->getType() == "firewall") { //handles if the moving link won and index2 was on a firewall
			board[index1]->setOnFirewall(true);
			board[index1]->fire = board[index2]->getSymbol();
			swap(board[index1], board[index2]);
			swap(board[index1]->index, board[index2]->index);
			board[index1] = make_unique<Empty>(board[index1]->index);
			return;

		}
		swap(board[index1], board[index2]);
		swap(board[index1]->index, board[index2]->index);
	}
}

bool Board::move(string linktomove, string dir, int playerturn) {
	int index = 0;
	for (auto it = board.begin(); it != board.end(); ++it) {
		if ((*it)->getSymbol() == linktomove[0]) {
			break;
		}
		++index; //index of link specified
	}
	if(board[index]->getPlayer() != playerturn) {
		cout << "Invalid move. You can only move your links. Re-enter link to move and direction." << endl;
		return false;
	}
	int posindex = 0; //position index link wants to move to

	Link *linkatpos;
	if (dir == "up") {
		if (((index - 8) < 0) && (playerturn == 1)) {
			cout << "Invalid move. Re-enter link to move and direction." << endl;
            return false;
		}
		posindex = index - 8; // minus 8 to index to move up
		if(board[index]->getBoosted()) { //minuses 8 again if boosted
			posindex -= 8;
		}
	} else if (dir == "down") {
		if (((index + 8) > 63) && (playerturn == 2)) {
			cout << "Invalid move. Re-enter link to move and direction." << endl;
            return false;
		}
		posindex = index + 8; // add 8 from index to move down
		if(board[index]->getBoosted()) { //adds 8 again if boosted
			posindex += 8;
		}
	} else if (dir == "left") {
		if (index % 8 == 0) {
            cout << "Invalid move. Re-enter link to move and direction." << endl;
            return false;
        }
		posindex = index - 1; // minus 1 from index to move left
		if(board[index]->getBoosted()) { //minuses 1 again if boosted
			if(index % 8 == 1) {
				cout << "Invalid move. Re-enter link to move and direction." << endl;
            	return false;
			}
			--posindex;
		}
	} else if (dir == "right") {
		if (index % 8 == 7) {
            cout << "Invalid move. Re-enter link to move and direction." << endl;
            return false;
        }
		posindex = index + 1; // add 1 to index to move right
		if(board[index]->getBoosted()) { //adds 1 again if boosted
			if(index % 8 == 6) {
				cout << "Invalid move. Re-enter link to move and direction." << endl;
            	return false;
			}
			++posindex;
		}
	} else {
			cout << "Invalid direction. Re-enter link to move and direction." << endl;
            return false;
	}

	if((posindex < 0 && playerturn == 2) || (posindex > 63 && playerturn == 1)) { //checks if one is moving their link off the opponents side
		download(board[index].get(), board[index]->getPlayer());
		turn = (turn == 1) ? 2 : (turn == 2 ? 1 : turn);
		notifyObservers();
		return true;
	}

	linkatpos = board[posindex].get(); //linkatpos of where we are moving

	if(board[index]->getStunned()) { //if a link is stunned we don't move, but we unstun it
		board[index]->setStunned(false);
		turn = (turn == 1) ? 2 : (turn == 2 ? 1 : turn);
		notifyObservers();
		return true;
	}

	if(linkatpos->getType() == "barrier") { //if the spot we want to move to is a barrier, we don't move, but replace that spot with an empty link
		board[posindex] = make_unique<Empty>(linkatpos->index);
		turn = (turn == 1) ? 2 : (turn == 2 ? 1 : turn);
		changes[index] = true;
		changes[posindex] = true;
		setPlayerLinks(true);
		notifyObservers();
		setPlayerLinks(false);
		changes[index] = false;
		changes[posindex] = true;
		return true;
	}


	if((linkatpos->getType() == "data" || linkatpos->getType() == "virus") && linkatpos->getOnFirewall()) { //moving onto a Link thats on a firewall
		if((board[index]->getPlayer() == 1 && linkatpos->fire == 'm') || (board[index]->getPlayer() == 2 && linkatpos->fire == 'w')) { //if moving link owns the firewall
			this->battle(index, linkatpos->index);
			turn = (turn == 1) ? 2 : (turn == 2 ? 1 : turn);
			changes[index] = true;
			setPlayerLinks(true);
			notifyObservers();
			setPlayerLinks(false);
			changes[index] = false;
			return true;
		} else { //if moving link does not own the firewall
			if(board[index]->getType() == "virus") { //if moving link is a virus, instantly download
				download(board[index].get(), board[index]->getPlayer());
				turn = (turn == 1) ? 2 : (turn == 2 ? 1 : turn);
				changes[index] = true;
				setPlayerLinks(true);
				notifyObservers();
				setPlayerLinks(false);
				changes[index] = false;
				return true;
			} else {
				this->battle(index, linkatpos->index);
				turn = (turn == 1) ? 2 : (turn == 2 ? 1 : turn);
				changes[index] = true;
				setPlayerLinks(true);
				notifyObservers();
				setPlayerLinks(false);
				changes[index] = false;
				return true;
			}
		}
	}


	if(linkatpos->getType() == "firewall") { //the spot we want to move to is a firewall
		if(board[index]->getPlayer() == linkatpos->getPlayer()) { //owned by the same player
			if(board[index]->getOnFirewall()) { //the link moving was on another firewall
				swap(board[index], board[posindex]);
				swap(board[index]->index, board[posindex]->index);
				char old = board[index]->getSymbol();
				board[index] = make_unique<Firewall>(board[index]->index, board[posindex]->fire);
				board[posindex]->fire = old;
				turn = (turn == 1) ? 2 : (turn == 2 ? 1 : turn);
				changes[index] = true;
				setPlayerLinks(true);
				notifyObservers();
				setPlayerLinks(false);
				changes[index] = false;
				return true;
			} else { //the link moving is on nothing
				swap(board[index], board[posindex]);
				swap(board[index]->index, board[posindex]->index);
				board[posindex]->setOnFirewall(true);
				board[posindex]->fire = board[index]->getSymbol();
				board[index] = make_unique<Empty>(board[index]->index);
				turn = (turn == 1) ? 2 : (turn == 2 ? 1 : turn);
				changes[index] = true;
				setPlayerLinks(true);
				notifyObservers();
				setPlayerLinks(false);
				changes[index] = false;
				return true;
			}
		} else { //the firewall is owned by opposing player
			if(board[index]->getType() == "virus") { //the link moving onto the firewall is a virus
				download(board[index].get(), board[index]->getPlayer());
				turn = (turn == 1) ? 2 : (turn == 2 ? 1 : turn);
				changes[index] = true;
				setPlayerLinks(true);
				notifyObservers();
				setPlayerLinks(false);
				changes[index] = false;
				return true;
			} else if(board[index]->getOnFirewall()) { //the link is a data thats on a firewall currently
				revealLink(board[index].get());
				board[index]->setRevealed(true);
				char old = board[index]->fire;
				board[index]->fire = board[posindex]->getSymbol();
				swap(board[index], board[posindex]);
				swap(board[index]->index, board[posindex]->index);
				board[index] = make_unique<Firewall>(board[index]->index, old);
				turn = (turn == 1) ? 2 : (turn == 2 ? 1 : turn);
				changes[index] = true;
				setPlayerLinks(true);
				notifyObservers();
				setPlayerLinks(false);
				changes[index] = false;
				return true;
			} else { //the link moving onto the firewall is a data not on a firewall
				revealLink(board[index].get());
				board[index]->setRevealed(true);
				board[index]->setOnFirewall(true);
				board[index]->fire = board[posindex]->getSymbol();
				swap(board[index], board[posindex]);
				swap(board[index]->index, board[posindex]->index);
				board[index] = make_unique<Empty>(board[index]->index);
				turn = (turn == 1) ? 2 : (turn == 2 ? 1 : turn);
				changes[index] = true;
				setPlayerLinks(true);
				notifyObservers();
				setPlayerLinks(false);
				changes[index] = false;
				return true;
			}
		}
	}



	if (linkatpos->getType() == "empty") { //move link if place is empty
		if(board[index]->getOnFirewall()) { //if the link we are moving was on a firewall
			swap(board[index], board[posindex]);
			swap(board[index]->index, board[posindex]->index);
			board[index] = make_unique<Firewall>(board[index]->index, board[posindex]->fire);
			board[posindex]->setOnFirewall(false);
			board[posindex]->fire = 'x';
			turn = (turn == 1) ? 2 : (turn == 2 ? 1 : turn);
			changes[index] = true;
			setPlayerLinks(true);
			notifyObservers();
			setPlayerLinks(false);
			changes[index] = false;
			return true;
		}
		swap(board[index], board[posindex]);
		swap(board[index]->index, board[posindex]->index);
	}
	if (linkatpos->getType() == "data" || linkatpos->getType() == "virus") { //checks if link at position is a data or virus
		if (linkatpos->getPlayer() != playerturn) { //checks if the data or virus link belongs to opposing player
			this->battle(index, linkatpos->index); //should work as long as linkatpos is not a firewall
			turn = (turn == 1) ? 2 : (turn == 2 ? 1 : turn);
			changes[index] = true;
			setPlayerLinks(true);
			notifyObservers();
			setPlayerLinks(false);
			changes[index] = false;
			return true;
		}
	}
	if(linkatpos->getType() == "server") {
		if(linkatpos->getPlayer() != playerturn) { //makes sure the server port is owned by opposing player
			if(playerturn == 1) { //the opposing player downloads the link
				download(board[index].get(), 2);
			} else {
				download(board[index].get(), 1);
			}
		}
	}
	turn = (turn == 1) ? 2 : (turn == 2 ? 1 : turn);
	changes[index] = true;
	setPlayerLinks(true);
	notifyObservers();
	setPlayerLinks(false);
	changes[index] = false;
	return true;
}

Board* Board::getState() {
	return this;
}

void Board::resetChanges() {
	for (int i = 0; i < 64; ++i) {
		changes[i] = false;
	}
}

int Board::getLinkIndex(char symbol) {
	for (int i = 0; i < 64; ++i) {
		if (board[i]->getSymbol() == symbol) return i;
	}
	return notFound;
}

void Board::setPlayerLinks(bool toSet) {
	for (char symbol = 'a'; symbol <= 'h'; ++symbol) {
		int index = getLinkIndex(symbol);
		if (index != notFound) {
			changes[index] = toSet;
		}
	}
	for (char symbol = 'A'; symbol <= 'H'; ++symbol) {
		int index = getLinkIndex(symbol);
		if (index != notFound) {
			changes[index] = toSet;
		}
	}
}
