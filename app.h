#ifndef APP_H
#define APP_H
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <memory>
#include "board.h"
#include "player.h"
#include "link.h"
#include "data.h"
#include "virus.h"
#include "server.h"
#include "empty.h"

using namespace std;

class App {
    unique_ptr<Board> b;
    unique_ptr<Player> player1 = make_unique<Player>();
	unique_ptr<Player> player2 = make_unique<Player>();
    public:
        App();
        void assignLinksToPlayer(string filename, int player);
        void assignAbilitiesToPlayer(string order, int player);
        void randomizePlayerLinks(int player);
        void start(bool addGraphics);
        ~App();
};
#endif
