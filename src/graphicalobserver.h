#ifndef GRAPHICALOBSERVER_H
#define GRAPHICALOBSERVER_H

#include "observer.h"
#include "subject.h"
#include "window.h"
#include "board.h"

class Board;

// This class defines a GraphicalObserver, which graphically responds
// to and renders the data it recieves from its subject.
class GraphicalObserver: public Observer {
    Subject *subject;
    Xwindow window;

    void renderGraphics(Board *theBoard, int turn);
    void renderPlayerData(Board *theBoard, int player, int turn);
    public:
        // Constructs a GraphicalObserver
        GraphicalObserver(Subject *s);

        // Outputs/renders recived data from subject to Xwindow.
        void notify() override;

        ~GraphicalObserver();
};

#endif
