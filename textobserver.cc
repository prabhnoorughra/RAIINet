#include "textobserver.h"
#include <iostream>
#include "board.h"

TextObserver::TextObserver(Subject *s): subject{s} {}

//printing the playerinfo at the top and bottom depending on whose turn it is
void TextObserver::printPlayer(Board *theBoard, int player, int turn) {
	int ability1count = 0;
	int ability2count = 0;
    
	for (auto it = theBoard->player1->abilities.begin(); it != theBoard->player1->abilities.end(); ++it) {
		ability1count += *it;
	}
	for (auto it = theBoard->player2->abilities.begin(); it != theBoard->player2->abilities.end(); ++it) {
		ability2count += *it;
	}

	if (player == 1) {
		cout << "Player 1:" << endl;
		cout << "Downloaded: " << theBoard->player1->getDataCount() << "D" << ", " << theBoard->player1->getVirusCount() << "V" << endl;
		cout << "Abilities: " << ability1count << endl;
		if(turn == 1) {
			for(char cur = 'a'; cur <= 'h'; ++cur) {
				Link *l = theBoard->player1->getLink(cur);
				if(cur == 'd' || cur == 'h') {
					cout << cur << ": " << l->print() << endl;
				} else {
					cout << cur << ": " << l->print() << " ";
				}
			}
		} else {
			char hide = '?';
			for(char cur = 'a'; cur <= 'h'; ++cur) {
				Link *l = theBoard->player1->getLink(cur);
				bool rev = l->getRevealed();
				if(cur == 'd' || cur == 'h') {
					if(rev) {
						cout << cur << ": " << l->print() << endl;
					} else {
						cout << cur << ": " << hide << endl;
					}
				} else {
					if(rev) {
						cout << cur << ": " << l->print() << " ";
					} else {
						cout << cur << ": " << hide << " ";
					}
				}
			}
		}
	} else {
		cout << "Player 2:" << endl;
		cout << "Downloaded: " << theBoard->player2->getDataCount() << "D" << ", " << theBoard->player2->getVirusCount() << "V" << endl;
		cout << "Abilities: " << ability2count << endl;
		if(turn == 2) {
			for(char cur = 'A'; cur <= 'H'; ++cur) {
				Link *l = theBoard->player2->getLink(cur);
				if(cur == 'D' || cur == 'H') {
					cout << cur << ": " << l->print() << endl;
				} else {
					cout << cur << ": " << l->print() << " ";
				}
			}
		} else {
			char hide = '?';
			for(char cur = 'A'; cur <= 'H'; ++cur) {
				Link *l = theBoard->player2->getLink(cur);
				bool rev = l->getRevealed();
				if(cur == 'D' || cur == 'H') {
					if(rev) {
						cout << cur << ": " << l->print() << endl;
					} else {
						cout << cur << ": " << hide << endl;
					}
				} else {
					if(rev) {
						cout << cur << ": " << l->print() << " ";
					} else {
						cout << cur << ": " << hide << " ";
					}
				}
			}
		}
	}
}

void TextObserver::printBoard(Board *theBoard) {
    for(int j = 0; j < 8; ++j) {
		cout << '=';
	}
	cout << endl;
	int i = 0;
	for (auto it = theBoard->board.begin(); it != theBoard->board.end(); ++it) {
		if(i % 8 == 0 && i != 0) {
			cout << endl;
			cout << (*it)->getSymbol();
			++i;
		} else {
			cout << (*it)->getSymbol();
			++i;
		}
	}
	cout << endl;
	for(int x = 0; x < 8; ++x) {
		cout << '=';
	}
	cout << endl;
}

void TextObserver::notify() {
    Board *theBoard = static_cast<Board*>(subject->getState());
    printPlayer(theBoard, 1, theBoard->turn);
    printBoard(theBoard);
    printPlayer(theBoard, 2, theBoard->turn);
}

TextObserver::~TextObserver() {
    subject->detach(this);
}
