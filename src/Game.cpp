#include "Game.hpp"

Game::Game() {
    this->listPemain = new Pemain[3];
    Petani Petani1;
    Peternak Peternak1;
    Walikota Walikota;
    listPemain[0] = Petani1;
    listPemain[1] = Peternak1;
    listPemain[2] = Walikota;
}