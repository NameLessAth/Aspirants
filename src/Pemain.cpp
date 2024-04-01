#include "Pemain.hpp"
#include <iostream>
using namespace std;

// Pemain
int Pemain::jumlahPemain = 0;

Pemain::Pemain() {
    Pemain::jumlahPemain++;
    this->username = "Pemain" + to_string(Pemain::jumlahPemain);
    this->uang = 50;
    this->beratBadan = 40;
}   

// Walikota
Walikota::Walikota() : Pemain() {
    this->username = "Walikota";
    cout << "Walikota " << this->username << " siap bermain!" << endl;
}

// Petani
int Petani::jumlahPetani = 0;

Petani::Petani() : Pemain() {
    Petani::jumlahPetani++;
    this->username = "Petani" + to_string(Petani::jumlahPetani);
    cout << "Petani " << this->username << " siap bermain!" << endl;

}

// Peternak
int Peternak::jumlahPeternak = 0;

Peternak::Peternak() : Pemain() {
    Peternak::jumlahPeternak++;
    this->username = "Peternak" + to_string(Peternak::jumlahPeternak);
    cout << "Peternak " << this->username << " siap bermain!" << endl;
}