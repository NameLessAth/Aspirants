#include "Pemain.hpp"
#include "Simpanan.hpp"
#include <iostream>
#include <string>
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
    cout << "================[ Penyimpanan ]==================" << endl;
    this->penyimpanan.printSimpananMatrix();
}

void Pemain::makan() {
    cout << "Pilih makanan dari penyimpanan" << endl;
    this->printPenyimpanan();
    Simpanan* simpanan = this->penyimpanan.extractSlot();
    Produk* produk = dynamic_cast<Produk*>(simpanan);
    while (!produk || produk->getBeratTambahan() == 0) {
        cout << "Ini bukan makanan!" << endl;
        cout << "Silahkan masukan slot yang berisi makanan" << endl;
        Simpanan* simpanan = this->penyimpanan.extractSlot();
        Produk* produk = dynamic_cast<Produk*>(simpanan);   
    }
    cout << "Dengan lahapnya, kamu memakanan hidangan itu" << endl;
    this->beratBadan += produk->getBeratTambahan();
    cout << "Alhasil, berat badan kamu naik menjadi " << this->beratBadan << endl;
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

void Petani::tanam() {
    cout << "Pilih tanaman dari penyimpanan" << endl;
    this->penyimpanan.printSimpananMatrix();
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