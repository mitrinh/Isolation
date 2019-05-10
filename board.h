// Michael Trinh
// Team: TEAM++
// CS 4200 Project 3: Game(Isolation)
// Professor Atanasio
// Due 5/5/2019
#include <iostream>
#include <vector>
#include "misc.h"
#include "queen.h"
using namespace std;

#ifndef CS4200P3_BOARD_H
#define CS4200P3_BOARD_H
#define SIZE 8
#define UNUSEDSYMBOL '-'
#define USEDSYMBOL '#'

class Board {
private:
    char board[SIZE][SIZE]{};
    void initializeBoard(char);
    static void printBoardHelper(vector<string>,vector<string>,int);
public:
    Board(){initializeBoard(UNUSEDSYMBOL);};
    char getSpace(int x,int y){return board[x][y];};
    void printBoard(const vector<string>&,const vector<string>&);
    void setSpace(int x,int y,char symbol){board[x][y] = symbol;};
};

void Board::initializeBoard(char symbol){
    for(auto & i : board) {
        for (char & j : i) {
            j = symbol;
        }
    }
}

void Board::printBoard(const vector<string>& compLog, const vector<string>& oppLog) {
    cout << "  ";
    for(int n=1; n<=SIZE; n++){ cout << n << " ";} // print "1-8"
    cout << '\t' << "Computer vs. Opponent" << endl;
    for(int i=0; i<SIZE; i++){ // 0-7
        cout << translateToAlphabetic(i) << " "; // print "A-H"
        for(int j=0; j<SIZE; j++){
            cout << board[i][j] << " ";
        }
        printBoardHelper(compLog,oppLog,i);
    }
    for(int i=SIZE; i<compLog.size(); i++){ // 8-...
        cout << "\t\t";
        printBoardHelper(compLog,oppLog,i);
    }
    cout << endl;
}

void Board::printBoardHelper(vector<string> compLog, vector<string> oppLog, int i) {
    if(compLog.size() > i) {
        cout << '\t' << i+1 << ". " << compLog.at(i);
        if(oppLog.size() > i){
            cout << "\t\t" << oppLog.at(i);
        }
    }
    cout << endl;
}
#endif //CS4200P3_BOARD_H
