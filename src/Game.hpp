#ifndef __GAME_H__
#define __GAME_H__

#include "Pemain.hpp"
#include <vector>
#include <iostream>
using namespace std;

class Game {
private:
    vector<Pemain*> listPemain;
    static int currentPemain;
public:
    Game();
    void next();
    static int getCurrentPemain();
    vector<Pemain*> getListPemain();
};

#endif
