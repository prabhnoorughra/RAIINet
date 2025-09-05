#include "graphicalobserver.h"
#include "board.h"
#include <string>

using namespace std;

GraphicalObserver::GraphicalObserver(Subject *s)
    : subject{s}, window{400, 610} {}

void GraphicalObserver::renderPlayerData(Board *theBoard, int player, int turn) {
    int xOffset = 10;
    int yOffset = (player == 1) ? 10 : 520; // Player 1 and Player 2 data positions

    // Render player label and basic information
    window.drawString(xOffset, yOffset, "Player " + to_string(player) + ":", 0);
    string dataCount = to_string(player == 1 ? theBoard->player1->getDataCount() : theBoard->player2->getDataCount()) + "D"; 
    string virusCount = to_string(player == 1 ? theBoard->player1->getVirusCount() : theBoard->player2->getVirusCount()) + "V";
    window.drawString(xOffset, yOffset + 20, "Downloaded: " + dataCount + ", " + virusCount, 0);

    // Render abilities
    int abilityCount = 0;
    if (player == 1) {
        for (int val : theBoard->player1->abilities) abilityCount += val;
    } else {
        for (int val : theBoard->player2->abilities) abilityCount += val;
    }
    window.drawString(xOffset, yOffset + 40, "Abilities: " + to_string(abilityCount), 0);

    // Render links
    int linkYOffset = yOffset + 60;
    int col = xOffset; // X position for each column
    int rowOffset = 20; // Line spacing

    if (player == 1) {
        for (char cur = 'a'; cur <= 'h'; ++cur) {
            Link *l = theBoard->player1->getLink(cur);
            string linkStr = (turn == 1 || l->getRevealed()) ? cur + string(": ") + l->print() : cur + string(": ?");
            window.drawString(col, linkYOffset, linkStr, 0);

            // Move to the next row after 'd'
            if (cur == 'd') {
                linkYOffset += rowOffset;
                col = xOffset;
            } else {
                col += 80;
            }
        }
    } else {
        for (char cur = 'A'; cur <= 'H'; ++cur) {
            Link *l = theBoard->player2->getLink(cur);
            string linkStr = (turn == 2 || l->getRevealed()) ? cur + string(": ") + l->print() : cur + string(": ?");
            window.drawString(col, linkYOffset, linkStr, 0);

            // Move to the next row after 'D'
            if (cur == 'D') {
                linkYOffset += rowOffset;
                col = xOffset;
            } else {
                col += 80;
            }
        }
    }
}

void GraphicalObserver::renderGraphics(Board *theBoard, int turn) {
    const int squareSize = 50;  // Size of each square
    const int lineThickness = 2;  // Thickness of the grid lines

    int vecIdx = 0;  // Tracks the index in the board vector
    for (int i = 100; i < 500; i += squareSize) {
        for (int j = 0; j < 400; j += squareSize) {
            char linkSymbol = theBoard->board[vecIdx]->getSymbol();
            string linkType = theBoard->board[vecIdx]->getType();
            bool revealed = theBoard->board[vecIdx]->getRevealed();  // Check if the link is revealed
            bool needsChange = theBoard->changes.at(vecIdx);
            int playerAssociated = theBoard->board[vecIdx]->getPlayer();
            int color;
            string identifier;

            if (needsChange) {
                if (linkSymbol == 'S') {
                    color = Xwindow::Black;
                    identifier = "Server";
                } else if (linkSymbol == 'w' || linkSymbol == 'm') {
                    color = 16;
                    identifier = "Firewall";
                } else if (linkSymbol == 'X') {
                    color = 10;
                    identifier = "Barrier";
                } else if (linkSymbol == '.') {
                    color = Xwindow::White;
                    identifier = "";
                } else if (!revealed && playerAssociated != turn) {
                    // If not revealed, display as blue (unknown)
                    color = Xwindow::Blue;
                    identifier = {linkSymbol};
                } else {
                    // Determine color and identifier based on type
                    if (linkType == "data") {
                        color = Xwindow::Green;  // Revealed data links are green
                    } else if (linkType == "virus") {
                        color = Xwindow::Red;  // Revealed viruses are red
                    } else {
                        color = Xwindow::White;  // Default background
                    }
                    identifier = {linkSymbol};
                }

                // Fill the square with the determined color
                window.fillRectangle(j, i, squareSize, squareSize, color);

                // Draw grid lines
                window.fillRectangle(j, i, squareSize, lineThickness, Xwindow::Black); // Top border
                window.fillRectangle(j, i, lineThickness, squareSize, Xwindow::Black); // Left border
                window.fillRectangle(j + squareSize - lineThickness, i, lineThickness, squareSize, Xwindow::Black); // Right border
                window.fillRectangle(j, i + squareSize - lineThickness, squareSize, lineThickness, Xwindow::Black); // Bottom border

                // Add the identifier
                if (identifier == "Server") {
                    window.drawString(j + 5, i + 25, identifier, Xwindow::White);
                } else {
                    window.drawString(j + 5, i + 25, identifier);
                }
            }

            ++vecIdx;
        }
    }
}

void GraphicalObserver::notify() {
    Board *theBoard = static_cast<Board*>(subject->getState());
    renderPlayerData(theBoard, 1, theBoard->turn);
    renderGraphics(theBoard, theBoard->turn);
    renderPlayerData(theBoard, 2, theBoard->turn);
}

GraphicalObserver::~GraphicalObserver() {
    subject->detach(this);
}
