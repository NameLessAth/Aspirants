#include "Pemain.hpp"
#include <iostream>
using namespace std;

// Pemain
int Pemain::jumlahPemain = 0;
int Pemain::barisPenyimpanan = 10; // Berdasarkan berkas
int Pemain::kolomPenyimpanan = 10; // Berdasarkan berkas

Pemain::Pemain() : penyimpanan(Pemain::barisPenyimpanan, Pemain::kolomPenyimpanan) {
    Pemain::jumlahPemain++;
    this->username = "Pemain" + to_string(Pemain::jumlahPemain);
    this->uang = 50;
    this->beratBadan = 40;
}   

void Pemain::printPenyimpanan() {
    this->penyimpanan.printSimpananMatrix();
}

// Walikota
Walikota::Walikota() : Pemain() {
    this->username = "Walikota";
    cout << "Walikota " << this->username << " siap bermain!" << endl;
}

// Petani
int Petani::jumlahPetani = 0;
int Petani::barisLadang = 10; // Berdasarkan berkas
int Petani::kolomLadang = 10; // Berdasarkan berkas

Petani::Petani() : Pemain(), ladang(Petani::barisLadang, Petani::kolomLadang) {
    Petani::jumlahPetani++;
    this->username = "Petani" + to_string(Petani::jumlahPetani);
    cout << "Petani " << this->username << " siap bermain!" << endl;

}

// Peternak
int Peternak::jumlahPeternak = 0;
int Peternak::barisTernak = 10; // Berdasarkan berkas
int Peternak::kolomTernak = 10; // Berdasarkan berkas

Peternak::Peternak() : Pemain(), peternakan(Peternak::barisTernak, Peternak::kolomTernak) {
    Peternak::jumlahPeternak++;
    this->username = "Peternak" + to_string(Peternak::jumlahPeternak);
    cout << "Peternak " << this->username << " siap bermain!" << endl;
}