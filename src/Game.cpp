#include "Game.hpp"

int Game::currentPemain = 0;
int Game::goldRequirement = 0;
int Game::weightRequirement = 0;
pair<int,int> Game::ukuranPenyimpanan(0,0);
pair<int,int> Game::ukuranLadang(0,0);
pair<int,int> Game::ukuranTernak(0,0);

void Game::next() {
    Game::currentPemain = (Game::currentPemain + 1) % ListPemain::getListPemain().size();
}

int Game::getCurrentPemain() {
    return Game::currentPemain;
}

void Game::main(){
    vector<int> temp = Load::loadMisc();
    Game::goldRequirement = temp[0];
    Game::weightRequirement = temp[1];
    Game::ukuranPenyimpanan.first = temp[2];
    Game::ukuranPenyimpanan.second = temp[3];
    Game::ukuranLadang.first = temp[4];
    Game::ukuranLadang.second = temp[5];
    Game::ukuranTernak.first = temp[6];
    Game::ukuranTernak.second = temp[7];

    vector<Hewan> temp2 = Load::loadAnimal();
    for(int i=0;i<temp2.size();i++){
        Toko::insertItem(temp2[i],0);
    }

    vector<Tanaman> temp3 = Load::loadPlant();
    for(int i=0;i<temp3.size();i++){
        Toko::insertItem(temp3[i],0);
    }

    vector<Produk> temp4 = Load::loadProduct();
    for(int i=0;i<temp4.size();i++){
        Toko::insertItem(temp4[i],0);
    }

    vector<Bangunan> temp5 = Load::loadRecipe();
    for(int i=0;i<temp5.size();i++){
        Toko::insertItem(temp5[i],0);
    }

    cout << "Selamat datang di Kelola Kerajaan Bersama Labpro\n";
    cout << "Apakah anda ingin memuat state? (y/n)\n\n> ";
    string input;
    cin >> input;

    if(input != "y" && input != "Y" && input != "n" && input != "N"){
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

        ListPemain::pushPemain(&Petani1);
        ListPemain::pushPemain(&Peternak1);
        ListPemain::pushPemain(&Walikota);
    }
    cout << "Sekarang adalah giliran " << (ListPemain::getListPemain()[Game::currentPemain])->getName() << "!\n";
    bool win = false;
    while(!win){
        
        cout << "\n> ";
        cin >> input;

        if (input == "NEXT"){
            Game::next();
            cout << "Sekarang adalah giliran " << (ListPemain::getListPemain()[Game::currentPemain])->getName() << "!\n";
        } else if (input == "CETAK_PENYIMPANAN"){
            ListPemain::getListPemain()[currentPemain]->getPenyimpanan().printSimpananMatrix();
        } else if (input == "PUNGUT_PAJAK" && dynamic_cast<Walikota*>(ListPemain::getListPemain()[currentPemain])){
            
        } else if (input == "CETAK_LADANG" && dynamic_cast<Petani*>(ListPemain::getListPemain()[currentPemain])){
            
        } else if (input == "CETAK_PETERNAKAN" && dynamic_cast<Peternak*>(ListPemain::getListPemain()[currentPemain])){
            
        } else if (input == "TANAM" && dynamic_cast<Petani*>(ListPemain::getListPemain()[currentPemain])){
            
        } else if (input == "TERNAK" && dynamic_cast<Peternak*>(ListPemain::getListPemain()[currentPemain])){
            
        } else if (input == "BANGUN" && dynamic_cast<Walikota*>(ListPemain::getListPemain()[currentPemain])){
            
        } else if (input == "MAKAN"){
            
        } else if (input == "KASIH_MAKAN" && dynamic_cast<Peternak*>(ListPemain::getListPemain()[currentPemain])){
            
        } else if (input == "BELI"){
            ListPemain::getListPemain()[currentPemain]->beli();
        } else if (input == "JUAL"){
            
        } else if (input == "PANEN" && (dynamic_cast<Walikota*>(ListPemain::getListPemain()[currentPemain]) || dynamic_cast<Walikota*>(ListPemain::getListPemain()[currentPemain]))){
            
        } else if (input == "SIMPAN"){
            
        } else if (input == "TAMBAH_PEMAIN" && dynamic_cast<Walikota*>(ListPemain::getListPemain()[currentPemain])){
            
        } else {
            throw InvalidInput();
        }

        if(ListPemain::getListPemain()[currentPemain]->getUang() >= Game::goldRequirement && ListPemain::getListPemain()[currentPemain]->getBerat() >= Game::weightRequirement){
            cout << "Pemain " << ListPemain::getListPemain()[currentPemain]->getName() << " Memenangkan Permainan\nPermainan berakhir.";
            win = true;
        }
    }
}
