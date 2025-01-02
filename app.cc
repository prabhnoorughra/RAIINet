#include "app.h"
#include "textdisplay.h"
#include <fstream>
#include <random>
#include <algorithm>
#include <iterator>
#include "observer.h"
#include "textobserver.h"
#include "graphicalobserver.h"

using namespace std;

App::App() {}

void App::assignLinksToPlayer(string filename, int player) {
    ifstream file{filename};
    string initializingLink;
    string inputStrength;
    int index = 0;
    int strength;
    char sym1 = 'a';
    char sym2 = 'A';
    if (player == 1) {
        index = 0;
    } else {
        index = 56;
    }
    int tempindex = index;
    while (file >> initializingLink) {
        inputStrength = initializingLink[1];
        istringstream iss{inputStrength};
        iss >> strength;
        if (initializingLink[0] == 'V') {
            if (index == 3) index = 11;
            else if (index == 4) index = 12;
            else if (index == 59) index = 51;
            else if (index == 60) index = 52;
            if (player == 1) {
                player1->assignLinks(index, sym1, player, strength, 'V');
                ++sym1;
            }
            else {
                player2->assignLinks(index, sym2, player, strength, 'V');
                ++sym2;
            }
        }
        if (initializingLink[0] == 'D') {
            if (index == 3) index = 11;
            else if (index == 4) index = 12;
            else if (index == 59) index = 51;
            else if (index == 60) index = 52;
            if (player == 1) {
                player1->assignLinks(index, sym1, player, strength, 'D');
                ++sym1;
            }
            else {
                player2->assignLinks(index, sym2, player, strength, 'D');
                ++sym2;
            }
        }
        index = tempindex;
        ++index;
        ++tempindex;
    }
}

void App::assignAbilitiesToPlayer(string order, int player) {
    for (int i = 0; i < 5; ++i) {
        if (player == 1) {
            player1->assignAbilities(order[i]);
        } else {
            player2->assignAbilities(order[i]);
        }
    }
}

// Defines and shuffles a vector of all 8 link strengths/types.
void App::randomizePlayerLinks(int player) {
    vector<string> placements = { "V1", "V2", "V3", "V4", "D1", "D2", "D3", "D4" };
    random_device rd;
    mt19937 g(rd());
    shuffle(placements.begin(), placements.end(), g);

    if (player == 1) {
        string filename = "player1Random.txt";
        ofstream outFile(filename);
        std::copy(placements.begin(), placements.end(), std::ostream_iterator<std::string>(outFile, " "));
        outFile.close();
        assignLinksToPlayer(filename, 1);
    } else {
        string filename = "player2Random.txt";
        std::ofstream outFile(filename);
        std::copy(placements.begin(), placements.end(), std::ostream_iterator<std::string>(outFile, " "));
        outFile.close();
        assignLinksToPlayer(filename, 2);
    }
}

void App::start(bool addGraphics) {
    b = make_unique<Board>(player1.get(), player2.get());
    std::vector<unique_ptr<Observer>> observers;
    observers.emplace_back(make_unique<TextObserver>(b.get()));
    b->attach((observers.back()).get());
    TextDisplay t{b.get()};
    if (addGraphics) {
        observers.emplace_back(make_unique<GraphicalObserver>(b.get()));
        b->attach((observers.back()).get());
    }
    string command;
    string linktomove;
    string dir;
    int abilityIndex = 0;
    char specifiedLink;
    int row = 0;
    int col = 0;
    int playerturn = 1;
    bool abilityused = false;
    bool sequenceGiven = false;
    string sequenceFile;
    ifstream f;
    istream *in = &cin;
    b->notifyObservers();
    b->resetChanges();
    cout << "It is Player " << playerturn << "'s turn" << endl;
    while (*in >> command) {
        Player *currentPlayer;
        if (playerturn == 1) {
            currentPlayer = player1.get();
        } else {
            currentPlayer = player2.get();
        }
        if (command == "move") {
            bool successful = false;
            while (!successful) {
                *in >> linktomove >> dir;
                successful = b->move(linktomove, dir, playerturn);
            }
            if (playerturn == 1) {
                playerturn = 2; //switch to player 2's turn
                abilityused = false;
            } else {
                playerturn = 1; //switch to player 1's turn
                abilityused = false;
            }
        } else if (command == "ability") {
            *in >> abilityIndex;
            if (abilityIndex == 0 && currentPlayer->abilities[0] != 0 && !abilityused) { 
                *in >> specifiedLink;
                b->linkBoost(specifiedLink);
                currentPlayer->minusAbility(0);
                abilityused = true;
            } else if (abilityIndex == 1 && currentPlayer->abilities[1] != 0 && !abilityused) {
                //call some function to place firewall
                *in >> row >> col;
                b->firewall(playerturn, row, col);
                currentPlayer->minusAbility(1);
                abilityused = true;
            } else if (abilityIndex == 2 && currentPlayer->abilities[2] != 0 && !abilityused) {
                *in >> specifiedLink;
                b->downloadAbility(specifiedLink);
                currentPlayer->minusAbility(2);
                abilityused = true;
            } else if (abilityIndex == 3 && currentPlayer->abilities[3] != 0 && !abilityused) {
                *in >> specifiedLink;
                if (playerturn == 1 && (specifiedLink <= 96 || specifiedLink >= 105)) {
                    b->scan(specifiedLink);
                    currentPlayer->minusAbility(3);
                    abilityused = true;
                } else if (playerturn == 2 && (specifiedLink <= 64 || specifiedLink >= 73)) {
                    b->scan(specifiedLink);
                    currentPlayer->minusAbility(3);
                    abilityused = true;
                } else {
                    cout << "cannot scan your own link" << endl;
                }
            } else if (abilityIndex == 4 && currentPlayer->abilities[4] != 0 && !abilityused) {
                *in >> specifiedLink;
                b->polarize(specifiedLink);
                currentPlayer->minusAbility(4);
                abilityused = true;
            } else if (abilityIndex == 5 && currentPlayer->abilities[5] != 0 && !abilityused) {
                *in >> specifiedLink;
                if (playerturn == 1 && (specifiedLink <= 96 || specifiedLink >= 105)) {
                    b->stun(specifiedLink);
                    currentPlayer->minusAbility(5);
                    abilityused = true;
                } else if (playerturn == 2 && (specifiedLink <= 64 || specifiedLink >= 73)) {
                    b->stun(specifiedLink);
                    currentPlayer->minusAbility(5);
                    abilityused = true;
                } else {
                    cout << "cannot stun your own link" << endl;
                }
            } else if (abilityIndex == 6 && currentPlayer->abilities[6] != 0 && !abilityused) {
                //call some function for barrier
                *in >> row >> col;
                b->barrier(playerturn, row, col);
                currentPlayer->minusAbility(6);
                abilityused = true;
            } else if (abilityIndex == 7 && currentPlayer->abilities[7] != 0 && !abilityused) {
                if (playerturn == 1 && (specifiedLink <= 104 || specifiedLink >= 97)) {
                    *in >> specifiedLink;
                    b->strengthBoost(specifiedLink);
                    currentPlayer->minusAbility(7);
                    abilityused = true;
                } else if (playerturn == 2 && (specifiedLink <= 72 || specifiedLink >= 65)) {
                    *in >> specifiedLink;
                    b->strengthBoost(specifiedLink);
                    currentPlayer->minusAbility(7);
                    abilityused = true;
                } else {
                    cout << "cannot boost other's link" << endl;
                }
            } else {
                if(abilityused) {
                    cout << "you already used an ability, please move a link" << endl;
                    continue;
                } else {
                    cout << "invalid ability index" << endl;
                    continue;
                }
            }
        } else if (command == "abilities") {
            t.printAbilities(currentPlayer);
        } else if (command == "board") {
            b->notifyObservers();
        } else if (command == "sequence") {
            *in >> sequenceFile;
            f.open(sequenceFile);
            in = &f;
            sequenceGiven = true;
        } else if (command == "quit") {
            break;
        } else {
            cout << "invalid command" << endl;
        }
        if (player1->getDataCount() == 4 || player1->getVirusCount() == 4 || player2->getDataCount() == 4 || player2->getVirusCount() == 4) {
            break;
        }
        cout << "It is Player " << playerturn << "'s turn" << endl;
    }
    if (sequenceGiven == true) {
        f.close();
    }
    Player *temp;
    if (player1->getDataCount() == 4 || player2->getVirusCount() == 4) {
        temp = player1.get();
        t.printWinner(temp, 1);
    }
    if (player2->getDataCount() == 4 || player1->getVirusCount() == 4) {
        temp = player2.get();
        t.printWinner(temp, 2);
    }
}

App::~App() {}
