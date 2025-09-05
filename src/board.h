#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#include <string>
#include "link.h"
#include "data.h"
#include "virus.h"
#include "server.h"
#include "empty.h"
#include "barrier.h"
#include "firewall.h"
#include "player.h"
#include "subject.h"
#include "textobserver.h"
#include "graphicalobserver.h"
#include <memory>

using namespace std;

class Board: public Subject {
	Player *player1;
	Player *player2;
	void battle(int index1, int index2);
	void download(Link *l, int playerdownloading);
	void revealLink(Link *l);
	Link *getLink(char symbol) const;
	vector<bool> changes;
	public:
		vector<unique_ptr<Link>> board;
		int turn;
		Board(Player *player1, Player *player2);
		~Board();
		bool move(string linktomove, string dir, int playerturn);
		void polarize(char symbol);
		void downloadAbility(char symbol);
		void scan(char symbol);
		void strengthBoost(char symbol);
		void linkBoost(char symbol);
		void stun(char symbol);
		void firewall(int player, int row, int col);
		void barrier(int player, int row, int col);
		
		void resetChanges();
		void setPlayerLinks(bool toSet);
		int getLinkIndex(char symbol);
		Board *getState() override;
		friend class TextObserver;
		friend class GraphicalObserver;
};

#endif
