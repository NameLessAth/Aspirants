#include "Game.hpp"

int Game::currentPemain = 0;

Game::Game() {

    Petani Petani1;
    Peternak Peternak1;
    Walikota Walikota;

    this->listPemain.push_back(&Petani1);
    this->listPemain.push_back(&Peternak1);
    this->listPemain.push_back(&Walikota);

    Game::currentPemain = 0;
    
}

void Game::next() {
    Game::currentPemain = (Game::currentPemain + 1) % this->listPemain.size();
}

int Game::getCurrentPemain() {
    return Game::currentPemain;
}

vector<Pemain*> Game::getListPemain() {
    return this->listPemain;
}

