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

Pemain::Pemain(string username) : penyimpanan(Pemain::barisPenyimpanan, Pemain::kolomPenyimpanan) {
    Pemain::jumlahPemain++;
    this->username = username;
    this->uang = 50;
    this->beratBadan = 40;
}

void Pemain::printPenyimpanan() {
    cout << "================[ Penyimpanan ]==================" << endl;
    this->penyimpanan.printSimpananMatrix();
}

void Pemain::makan() {
    bool found = false;
    for (int i = 1; i <= this->barisPenyimpanan; ++i) {
        for (int j = 1; j <= this->kolomPenyimpanan; ++j) {
            Simpanan* simpanan = this->penyimpanan.getValue(i, j);
            Produk* produk = dynamic_cast<Produk*>(simpanan);
            if (produk) {
                found = true;
                break;
            }
        }
    }
    if (found) {
        cout << "Pilih makanan dari penyimpanan" << endl;
        this->printPenyimpanan();
        Simpanan* simpanan = this->penyimpanan.extractSlot();
        Produk* produk = dynamic_cast<Produk*>(simpanan);
        while (!produk || produk->getBeratTambahan() == 0) {
            cout << "Ini bukan makanan!" << endl;
            cout << "Silahkan masukan slot yang berisi makanan" << endl;
            simpanan = this->penyimpanan.extractSlot();
            produk = dynamic_cast<Produk*>(simpanan);   
        }
        cout << "Dengan lahapnya, kamu memakanan hidangan itu" << endl;
        this->beratBadan += produk->getBeratTambahan();
        cout << "Alhasil, berat badan kamu naik menjadi " << this->beratBadan << endl;
    } else {
        cout << "Perintah tidak dapat dijalankan" << endl;
    }
}

// Walikota
Walikota::Walikota() : Pemain() {
    this->username = "Walikota";
    cout << "Walikota " << this->username << " siap bermain!" << endl;
}

Walikota::Walikota(string username) : Pemain(){
    this->username = username;
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

Petani::Petani(string username) : Pemain(), ladang(Petani::barisLadang, Petani::kolomLadang) {
    Petani::jumlahPetani++;
    this->username = username;
    cout << "Petani " << this->username << " siap bermain!" << endl;
}

void Petani::tanam() {
    bool found = false;
    for (int i = 1; i <= this->barisPenyimpanan; ++i) {
        for (int j = 1; j <= this->kolomPenyimpanan; ++j) {
            Simpanan* simpanan = this->penyimpanan.getValue(i, j);
            Tanaman* tanaman = dynamic_cast<Tanaman*>(tanaman);
            if (tanaman) {
                found = true;
                break;
            }
        }
    }
    if (found) {
        cout << "Pilih tanaman dari penyimpanan" << endl;
        this->printPenyimpanan();
        Simpanan* simpanan = this->penyimpanan.extractSlot();
        Tanaman* tanaman = dynamic_cast<Tanaman*>(simpanan);
        while (!tanaman) {
            cout << "Ini bukan tanaman!" << endl;
            cout << "Silahkan masukan slot yang berisi tanaman" << endl;
            simpanan = this->penyimpanan.extractSlot();
            tanaman = dynamic_cast<Tanaman*>(simpanan);   
        }
        cout << "Kamu memilih " << tanaman->getNama() << "." << endl;
        cout << "Pilih petak tanah yang akan ditanami" << endl;
        this->ladang.printSimpananMatrix();
        Tanaman* petak = this->ladang.extractSlot();
        while (petak != nullptr) {
            cout << "Petak tanah ini sudah terisi" << endl;
            cout << "Silahkan pilih petak tanah yang kosong" << endl;
            petak = this->ladang.extractSlot();
        }
        
    }
    else {
        cout << "Perintah tidak dapat dijalankan" << endl;
    }
    cout << "Pilih tanaman dari penyimpanan" << endl;
    Simpanan *simpanan = this->penyimpanan.extractSlot();
    Tanaman* tanaman = dynamic_cast<Tanaman*>(simpanan);
    while (!tanaman) {
        
    }
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

Peternak::Peternak(string username) : Pemain(), peternakan(Peternak::barisTernak, Peternak::kolomTernak) {
    Peternak::jumlahPeternak++;
    this->username = username;
    cout << "Peternak " << this->username << " siap bermain!" << endl;
}