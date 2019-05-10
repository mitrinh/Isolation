// Michael Trinh
// Team: TEAM++
// CS 4200 Project 3: Game(Isolation)
// Professor Atanasio
// Due 5/5/2019
#include <chrono>
#include <istream>
#include <iostream>
#include <random>
#include <vector>
using namespace std;

#ifndef CS4200P3_MISC_H
#define CS4200P3_MISC_H

void clearInput(){
    cin.clear();
    cin.ignore(256,'\n');
}

template <class T>
void test(T me){
    cout << "value: " << me << endl;
}

int translate(char coordinate){ // converts board coordinates to true coordinates
    int temp = (int)coordinate - 49; // ascii from (char)1 -> (int)0 = 49
    if(temp >= 0 && temp <= 8)
        return temp;
    else{
        temp -= 16; // ascii from (char)A -> (int)0 = 65; 49 - 65= -16
        if(temp >= 0 && temp <= 8)
            return temp;
        cout << "Invalid position" << endl;
        return -1;
    }
}

char translateToAlphabetic(int num){
    return (char)(num + 65);
}

string translatePositionToString(int x,int y){
    string result;
    result.push_back(translateToAlphabetic(x));
    result += to_string(y+1);
    return result;
}

void printCoordinateVector(vector<int> vec){
    cout << translateToAlphabetic(vec.at(0)) << vec.at(1)+1 << " ";
}

void printVector(vector<vector<int>> vec){
    for(auto i = vec.begin(); i < vec.end(); i++){
        printCoordinateVector(*i);
    }
    cout << endl;
}

int maximum(int num1, int num2){
    if(num1 >= num2) return num1;
    return num2;
}

int minimum(int num1, int num2){
    if(num1 <= num2) return num1;
    return num2;
}

/* create random number generator;
    * regular srand(seed) with rand() is not a good randomizer, stdlib random is better
    * random num generator code taken from:
    * http://www.cplusplus.com/reference/random/linear_congruential_engine/operator()/
*/
minstd_rand0 createRandomGenerator(){
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    minstd_rand0 generator (seed);
    return generator;
}

#endif //CS4200P3_MISC_H
