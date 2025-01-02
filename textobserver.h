#ifndef TEXTOBSERVER_H
#define TEXTOBSERVER_H

#include "observer.h"
#include "subject.h"
#include "board.h"
using namespace std;

class Board;

// This class defines a TextObserver, which outputs text to std::cout
// based on the data it recieves from its subject.
class TextObserver : public Observer {
    Subject *subject;
    void printPlayer(Board *theBoard, int player, int turn);
    void printBoard(Board *theBoard);

 public:
    // Constructor for a TextObserver
    TextObserver(Subject *s);

    // Outputs/renders recived data from subject to std::cout
    void notify() override;

    ~TextObserver();
};

#endif
