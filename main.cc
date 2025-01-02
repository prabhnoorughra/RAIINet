#include "board.h"
#include "link.h"
#include "app.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {
	unique_ptr<App> a = make_unique<App>();
	string link1command = "-link1";
	string link2command = "-link2";
	string ability1command = "-ability1";
	string ability2command = "-ability2";
	string graphicsCommand = "-graphics";
	bool player1AbilityGiven = false;
	bool player2AbilityGiven = false;
	bool player1OrderGiven = false;
	bool player2OrderGiven = false;
	bool graphics = false;
	string defaultorder = "LFDSP"; //default order
	string order;
	string filename = "";
	for (int i = 1; i < argc; ++i) {
		if (argv[i] == ability1command) {
			i = i + 1;
			filename = argv[i];
			player1AbilityGiven = true;
			ifstream f{filename};
			f >> order;
			a->assignAbilitiesToPlayer(order, 1);
			//call a function in app that will assign the abilities for player 1
		} else if (argv[i] == ability2command) {
			i = i + 1;
			filename = argv[i];
			player2AbilityGiven = true;
			ifstream f{filename};
			f >> order;
			a->assignAbilitiesToPlayer(order, 2);
			//call a function in app that will assign the abilities for player 2
		} else if (argv[i] == link1command) {
			i = i + 1;
			filename = argv[i];
			player1OrderGiven = true;
			a->assignLinksToPlayer(filename, 1);
			//call function in app that will assign links for player 1 with given file
		} else if (argv[i] == link2command) {
			i = i + 1;
			filename = argv[i];
			player2OrderGiven = true;
			a->assignLinksToPlayer(filename, 2);
			//call function in app that will assign links for player 1 with given file
		} else if (argv[i] == graphicsCommand) {
			graphics = true;
			//call function in app to intiialize graphics
		} else {

		}
	}
		if (player1AbilityGiven == false) {
			a->assignAbilitiesToPlayer(defaultorder, 1);
		}
		if (player2AbilityGiven == false) {
			a->assignAbilitiesToPlayer(defaultorder, 2);
		}
		if (player1OrderGiven == false) {
			//call function in app to randomize links for player 1
			a->randomizePlayerLinks(1);
		}
		if (player2OrderGiven == false) {
			//call function in app to randomize links for player 2
			a->randomizePlayerLinks(2);
		}
	a->start(graphics); //test harness
}
