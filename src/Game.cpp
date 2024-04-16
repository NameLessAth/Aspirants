#include "Game.hpp"

int Game::currentPemain = 0;
int Game::goldRequirement = 0;
int Game::weightRequirement = 0;
pair<int,int> Game::ukuranPenyimpanan(0,0);
pair<int,int> Game::ukuranLadang(0,0);
pair<int,int> Game::ukuranTernak(0,0);

void Game::next() {
    Game::currentPemain = (Game::currentPemain + 1) % Pemain::getListPemain().size();
}

int Game::getCurrentPemain() {
    return Game::currentPemain;
}

void Game::start(){
    vector<int> temp = Load::loadMisc();
    Game::goldRequirement = temp[0];
    Game::weightRequirement = temp[1];
    Game::ukuranPenyimpanan.first = temp[2];
    Game::ukuranPenyimpanan.second = temp[3];
    Game::ukuranLadang.first = temp[4];
    Game::ukuranLadang.second = temp[5];
    Game::ukuranTernak.first = temp[6];
    Game::ukuranTernak.second = temp[7];

    cout << "Selamat datang di Kelola Kerajaan Bersama Labpro\n";
    cout << "Apakah anda ingin memuat state? (y/n)\n\n> ";
    string input;
    cin >> input;

    if(input != "y" || input != "Y" || input != "n" || input != "N"){
        throw InvalidInput();
    }

    if(input == "y" || input == "Y"){
        cout << "Masukkan lokasi berkas state : ";
        cin >> input;
        Load::loadState(input);
    } else {
        Petani Petani1;
        Peternak Peternak1;
        Walikota Walikota;

        // Sudah dilakukan oleh constructor Pemain
        // Pemain::listPemain.push_back(&Petani1);
        // Pemain::listPemain.push_back(&Peternak1);
        // Pemain::listPemain.push_back(&Walikota);
    }
}

void Game::main(){
    string input;
    bool win = false;
    while(!win){
        cout << "> ";
        cin >> input;

        if (input == "NEXT"){
            Game::next();
        } else if (input == "CETAK_PENYIMPANAN"){
            
        } else if (dynamic_cast<Walikota*>(Pemain::getListPemain()[currentPemain]) && input == "PUNGUT_PAJAK"){
            
        } else if (dynamic_cast<Petani*>(Pemain::getListPemain()[currentPemain]) && input == "CETAK_LADANG"){
            
        } else if (dynamic_cast<Peternak*>(Pemain::getListPemain()[currentPemain]) && input == "CETAK_PETERNAKAN"){
            
        } else if (dynamic_cast<Petani*>(Pemain::getListPemain()[currentPemain]) && input == "TANAM"){
            
        } else if (dynamic_cast<Peternak*>(Pemain::getListPemain()[currentPemain]) && input == "TERNAK"){
            
        } else if (dynamic_cast<Walikota*>(Pemain::getListPemain()[currentPemain]) && input == "BANGUN"){
            
        } else if (input == "MAKAN"){
            
        } else if (dynamic_cast<Peternak*>(Pemain::getListPemain()[currentPemain]) && input == "KASIH_MAKAN"){
            
        } else if (input == "BELI"){
            
        } else if (input == "JUAL"){
            
        } else if ((dynamic_cast<Walikota*>(Pemain::getListPemain()[currentPemain]) || dynamic_cast<Walikota*>(Pemain::getListPemain()[currentPemain])) && input == "PANEN"){
            
        } else if (input == "SIMPAN"){
            
        } else if (dynamic_cast<Walikota*>(Pemain::getListPemain()[currentPemain]) && input == "TAMBAH_PEMAIN"){
            
        } else {
            throw InvalidInput();
        }

        if(Pemain::getListPemain()[currentPemain]->getUang() >= Game::goldRequirement && Pemain::getListPemain()[currentPemain]->getBerat() >= Game::weightRequirement){
            cout << "Pemain " << Pemain::getListPemain()[currentPemain]->getName() << " Memenangkan Permainan\nPermainan berakhir.";
            win = true;
        }
    }
}
