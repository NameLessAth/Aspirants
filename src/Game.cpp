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
    Game::currentPemain = (Game::currentPemain + 1) % listPemain.size();
}

int Game::getCurrentPemain() {
    return Game::currentPemain;
}

vector<Pemain*> Game::getListPemain() {
    return listPemain;
}

void Game::start(){
    cout << "Selamat datang di Kelola Kerajaan Bersama Labpro\n";
    cout << "Apakah anda ingin memuat state? (y/n)\n\n> ";
    char* input;
    cin >> input;

    if(input != "y" || input != "Y" || input != "n" || input != "N"){
        throw InvalidInput();
    }

    if(input == "y" || input == "Y"){
        cout << "Masukkan lokasi berkas state : ";
        cin >> input;
        //Load::loadState(input);
    } else {
        Game game;
    }
}

void Game::main(){
    string input;
    while(1){
        cout << "> ";   
        cin >> input;

        if (input == "NEXT"){
            Game::next();
        } else if (input == "CETAK_PENYIMPANAN"){
            
        } else if (input == "PUNGUT_PAJAK"){
            
        } else if (input == "CETAK_LADANG"){
            
        } else if (input == "CETAK_PETERNAKAN"){
            
        } else if (input == "TANAM"){
            
        } else if (input == "TERNAK"){
            
        } else if (input == "BANGUN"){
            
        } else if (input == "MAKAN"){
            
        } else if (input == "KASIH_MAKAN"){
            
        } else if (input == "BELI"){
            
        } else if (input == "JUAL"){
            
        } else if (input == "PANEN"){
            
        } else if (input == "SIMPAN"){
            
        } else if (input == "TAMBAH_PEMAIN"){
            
        } else {
            throw InvalidInput();
        }
    }
}
