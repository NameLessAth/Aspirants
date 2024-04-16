#ifndef __GAME_H__
#define __GAME_H__

#include "Pemain.hpp"
#include "Load.hpp"
#include <vector>
#include <iostream>
using namespace std;

class Game {
private:
    static int currentPemain;
    static int goldRequirement;
    static int weightRequirement;
    static pair<int,int> ukuranPenyimpanan;
    static pair<int,int> ukuranLadang;
    static pair<int,int> ukuranTernak;
public:
    static void next();
    static int getCurrentPemain();
    static void main();
};

#endif
