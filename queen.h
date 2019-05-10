// Michael Trinh
// Team: TEAM++
// CS 4200 Project 3: Game(Isolation)
// Professor Atanasio
// Due 5/5/2019
#include <iostream>
#include "misc.h"
using namespace std;

#ifndef CS4200P3_QUEEN_H
#define CS4200P3_QUEEN_H

class Queen {
private:
    int xPos, yPos;
    char qSymbol; // X or O representation
    char opponentSymbol; // symbol of opponent
public:
    Queen(){};
    Queen(int x,int y,char symbol,char oSymbol) : xPos(x),yPos(y),qSymbol(symbol),opponentSymbol(oSymbol){};
    int getX() const {return xPos;};
    int getY() const {return yPos;};
    char getSymbol() {return qSymbol;};
    char getRivalSymbol() { return  opponentSymbol;};
    void printPosition() const;
    void setPosition(int x,int y) {xPos = x; yPos = y;};
};

void Queen::printPosition() const {
    cout << translateToAlphabetic(xPos) << yPos+1 << endl;
}

#endif //CS4200P3_QUEEN_H
