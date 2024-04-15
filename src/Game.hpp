#ifndef __GAME_H__
#define __GAME_H__

#include "Pemain.hpp"
#include "Load.hpp"
#include <vector>
#include <iostream>
using namespace std;

class Game {
private:
    static vector<Pemain*> listPemain;
    static int currentPemain;
public:
    Game();
    static void next();
    static int getCurrentPemain();
    static vector<Pemain*> getListPemain();
    static void start();
    static void main();
};

#endif
