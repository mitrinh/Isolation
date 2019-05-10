// Michael Trinh
// Team: TEAM++
// CS 4200 Project 3: Game(Isolation)
// Professor Atanasio
// Due 5/5/2019
#include <algorithm>
#include <ctime>
#include <istream>
#include <iostream>
#include <string>
#include <vector>
#include "board.h"
#include "misc.h"
#include "queen.h"
using namespace std;

#ifndef CS4200P3_GAME_H
#define CS4200P3_GAME_H
#define STANDARDTIMELIMIT 20
#define COMPUTER 'C'
#define COMPUTERSYMBOL 'X'
#define OPPONENTSYMBOL 'O'
#define INITIALDEPTH 4 // slower as depth is increased

class Game {
private:
    Board board;
    Queen queenX,queenO; // computer=X, opponent = y
    int timeLimit = STANDARDTIMELIMIT; // default: 20 second time limit
    char turn = COMPUTER; // default: Computer first
    string latestCMove,latestOMove;
    vector<string> computerLog, opponentLog;
    void addQueen(Queen);
    void startGame();
    void beginLoop();
    void inputTimeLimit();
    void inputFirst();
    void checkForWin(Queen);
    static void evaluateWinner(char);
    void checkTime(clock_t);
    void switchTurn(){turn = turn == COMPUTER ? OPPONENTSYMBOL : COMPUTER;};
    int evaluate(int,int); // evaluation function: most amount of moves from position
    int minimaxDecision(int,int,int,int,int,char); // returns move to make for computer (recursive)
    int getMax(const vector<vector<int>>&,int&,int&,int&);
    int getMin(const vector<vector<int>>&,int&,int&,int&);
    string computerTurn(); // minimax with a/b pruning
    string opponentTurn(); // return chess coordinates for logging
    /* function name convention uses Cartesian coordinates, separated due to direct moves only */
    void addLeft(vector<vector<int>> &, int, int);
    void addUp(vector<vector<int>> &, int, int);
    void addRight(vector<vector<int>> &, int, int);
    void addDown(vector<vector<int>> &, int, int);
    void addUpLeft(vector<vector<int>> &, int, int);
    void addUpRight(vector<vector<int>> &, int, int);
    void addDownLeft(vector<vector<int>> &, int, int);
    void addDownRight(vector<vector<int>> &, int, int);
    bool addToMoveList(vector<vector<int>> &, int, int);
public:
    Board getBoard(){return board;};
    vector<vector<int>> getAvailableMoves(int,int);
    Queen& getQueen(char);
    void moveQueen(char,int,int);
    Game();
};

Game::Game() {
    startGame();
    beginLoop();
}

void Game::startGame(){
    inputTimeLimit();
    cout << "time limit is " << timeLimit << " seconds." << endl;
    inputFirst();
    cout << "player to go first is " << turn << '.' << endl;
    if(turn == 'O'){
        queenO = Queen(0,0,COMPUTERSYMBOL,OPPONENTSYMBOL);
        queenX = Queen(7,7,OPPONENTSYMBOL,COMPUTERSYMBOL);    
    }
    else {
        queenX = Queen(0,0,COMPUTERSYMBOL,OPPONENTSYMBOL);
        queenO = Queen(7,7,OPPONENTSYMBOL,COMPUTERSYMBOL);   
    }
    addQueen(queenX);
    addQueen(queenO);
}

void Game::beginLoop() {
    float turnCount = 0;
    while(turnCount <= SIZE*SIZE){
        switch(turn){
            case COMPUTER:
                latestCMove = computerTurn();
                computerLog.push_back(latestCMove);
                board.printBoard(computerLog,opponentLog);
                cout << "Computer's move is: " << latestCMove << endl;
                break;
            case OPPONENTSYMBOL:
                latestOMove = opponentTurn();
                opponentLog.push_back(latestOMove);
                break;
            default: return;
        }
        Queen queen = getQueen(turn); // update queen's position to check for win condition.
        checkForWin(queen); // for case of self trap
        checkForWin(getQueen(queen.getRivalSymbol())); // check if opponent is trapped
        switchTurn();
        turnCount += 0.5; // (8*8)-2 max possible moves w/o WC, infinite loop till win is same.
    }
}

void Game::inputTimeLimit() {
    cout << "Enter time limit for the computer to move (in seconds): ";
    cin >> timeLimit;
    clearInput();
}

void Game::inputFirst() {
    char first = 'a';
    while(first != COMPUTER && first != OPPONENTSYMBOL) {
        cout << "Who goes first, C for computer, O for opponent: ";
        cin >> first;
        clearInput();
    }
    turn = first;
}

void Game::checkForWin(Queen queen) {
    // checks if queen has no moves
    if(getAvailableMoves(queen.getX(),queen.getY()).empty()){
        evaluateWinner(queen.getRivalSymbol());
    }
}

void Game::evaluateWinner(char rival) {
    switch(rival){
        case COMPUTERSYMBOL:
            cout << "Computer Wins!" << endl;
            break;
        case OPPONENTSYMBOL:
            cout << "Opponent Wins!" << endl;
            break;
        default:
            cout << "Something happened..." << endl;
    }
    exit(0);
}

void Game::addQueen(Queen queen) {
    board.setSpace(queen.getX(),queen.getY(),queen.getSymbol());
}

Queen& Game::getQueen(char symbol) {
    switch(symbol){
        case COMPUTERSYMBOL:
        case COMPUTER:
            return queenX;
        case OPPONENTSYMBOL:
            return queenO;
        default:
            cout << "Invalid symbol" << endl;
            exit(0);
    }
}

void Game::checkTime(clock_t startTime) {
    clock_t endTime = clock();
    double timeToMakeMove = (endTime - startTime) / (double) CLOCKS_PER_SEC;
    if(timeToMakeMove > timeLimit){
        cout << "Ran out of time!" << endl;
        cout << "time elapsed: " << timeToMakeMove << " seconds. "
             << timeLimit-timeToMakeMove << " seconds from " << timeLimit << " second time limit." << endl;
        evaluateWinner(getQueen(turn).getRivalSymbol());
    }
}

// Note: clock_t is in clock ticks, requires conversion to seconds
void Game::moveQueen(char symbol, int x, int y) {
    Queen* queen = &getQueen(symbol);
    // set current space to used
    board.setSpace(queen->getX(),queen->getY(),'#');
    // move queen to specified coordinate
    queen->setPosition(x,y);
    board.setSpace(x,y,queen->getSymbol());
}

string Game::opponentTurn() {
    vector<vector<int>> moves = getAvailableMoves(queenO.getX(),queenO.getY());
    vector<int> coordinate(2);
    string newPosition;
    clock_t startTime = clock();
    while(true){
        cout << "Enter opponent's move: ";
        cin >> newPosition;
        transform(newPosition.begin(),newPosition.end(),newPosition.begin(),::toupper);
        clearInput();
        coordinate.at(0) = translate(newPosition.at(0));
        coordinate.at(1) = translate(newPosition.at(1));
        if(find(moves.begin(),moves.end(),coordinate) != moves.end()) break;
        else cout << "Invalid or Taken position." << endl;
    }
    moveQueen('O',coordinate.at(0),coordinate.at(1));
    return newPosition;
}

int Game::minimaxDecision(int x,int y,int depth,int a,int b,char symbol) {
    vector<vector<int>> moveList = getAvailableMoves(x,y);
    if(depth == 0 || moveList.empty()) {return evaluate(x,y);}
    if(symbol == 'X'){
        return getMax(moveList,depth,a,b);
    }
    else{
        return getMin(moveList,depth,a,b);
    }
}

int Game::getMax(const vector<vector<int>>& moveList,int& depth,int& a,int& b){
    int evaluation;
    int max = INT8_MIN;
    for(const auto & i : moveList){
        evaluation = minimaxDecision(i.at(0),i.at(1),depth-1,a,b,'O');
        max = maximum(max,evaluation);
        a = maximum(a,evaluation);
        if(a >= b) break;
    }
    return max;
}

int Game::getMin(const vector<vector<int>>& moveList,int& depth,int& a,int& b){
    int evaluation;
    int min = INT8_MAX;
    for(const auto & i : moveList){
        evaluation = minimaxDecision(i.at(0),i.at(1),depth-1,a,b,'X');
        min = minimum(min,evaluation);
        b = minimum(b,evaluation);
        if(a >= b) break;
    }
    return min;
}

string Game::computerTurn() {
    clock_t startTime = clock();
    vector<vector<int>> moves = getAvailableMoves(queenX.getX(),queenX.getY());
    int nextMoveX=0,nextMoveY=0,decision,bestDecision=INT8_MIN;
    for(const auto & i : moves){
        decision = minimaxDecision(i.at(0),i.at(1),INITIALDEPTH,INT8_MIN,INT8_MAX,'X');
        if(bestDecision < decision){
            bestDecision = decision;
            nextMoveX = i.at(0);
            nextMoveY = i.at(1);
        }
        else if(bestDecision == decision){ // 50% chance to choose another move if equal minimax value
            minstd_rand0 generator = createRandomGenerator(); // check misc.h for more info
            if(generator()%2 == 0){ // odd or even rand num = 50% chance
                bestDecision = decision;
                nextMoveX = i.at(0);
                nextMoveY = i.at(1);
            }
        }
    }
    checkTime(startTime);
    moveQueen('X',nextMoveX,nextMoveY);
    return translatePositionToString(nextMoveX,nextMoveY);
}

int Game::evaluate(int x, int y) {
    return getAvailableMoves(x,y).size();
}

/* returns a vector of all possible moves from a position as queen */
vector<vector<int>> Game::getAvailableMoves(int x, int y) {
    vector<vector<int>> moveList;
    addUp(moveList,x,y);
    addDown(moveList,x,y);
    addLeft(moveList,x,y);
    addRight(moveList,x,y);
    addUpLeft(moveList,x,y);
    addUpRight(moveList,x,y);
    addDownLeft(moveList,x,y);
    addDownRight(moveList,x,y);
    return moveList;
}

void Game::addUp(vector<vector<int>> &moveList, int x, int y)
{for(int i=x-1; i>=0; i--){ if(!addToMoveList(moveList,i,y)) break;}}

void Game::addDown(vector<vector<int>> &moveList, int x, int y)
{for(int i=x+1; i<SIZE; i++){ if(!addToMoveList(moveList,i,y)) break;}}

void Game::addLeft(vector<vector<int>> &moveList, int x, int y)
{for(int i=y-1; i>=0; i--){ if(!addToMoveList(moveList,x,i)) break;}}

void Game::addRight(vector<vector<int>> &moveList, int x, int y)
{for(int i=y+1; i<SIZE; i++){ if(!addToMoveList(moveList,x,i)) break;}}

void Game::addUpLeft(vector<vector<int>> &moveList, int x, int y)
{for(int i=x-1,j=y-1; i>=0 && j>=0; i--,j--){ if(!addToMoveList(moveList,i,j)) break;}}

void Game::addUpRight(vector<vector<int>> &moveList, int x, int y)
{for(int i=x-1,j=y+1; i>=0 && j<SIZE; i--,j++){ if(!addToMoveList(moveList,i,j)) break;}}

void Game::addDownLeft(vector<vector<int>> &moveList, int x, int y)
{for(int i=x+1,j=y-1; i<SIZE && j>=0; i++,j--){ if(!addToMoveList(moveList,i,j)) break;}}

void Game::addDownRight(vector<vector<int>> &moveList, int x, int y)
{for(int i=x+1,j=y+1; i<SIZE && j<SIZE; i++,j++){ if(!addToMoveList(moveList,i,j)) break;}}

bool Game::addToMoveList(vector<vector<int>> &moveList,int x,int y){
    vector<int> temp(2);
    char symbol = board.getSpace(x,y);
    if(symbol == UNUSEDSYMBOL){
        temp.at(0) = x;
        temp.at(1) = y;
        moveList.push_back(temp);
        return true;
    }
    return false;
}

#endif //CS4200P3_GAME_H
