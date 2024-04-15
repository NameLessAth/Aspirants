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

Pemain::Pemain(string username, int uang, int berat, Matrix<Simpanan> inventory) : penyimpanan(inventory.getBaris(), inventory.getKolom()) {
    Pemain::jumlahPemain++;
    this->username = username;
    this->uang = uang;
    this->beratBadan = berat;
    for (int i = 1; i <= this->penyimpanan.getBaris(); i++){
        for (int j = 1; j <= this->penyimpanan.getKolom(); j++){
            this->penyimpanan.setValue(i, j, inventory.getValue(i, j));
        }
    }
}

void Pemain::printPenyimpanan() {
    cout << "================[ Penyimpanan ]==================" << endl;
    this->penyimpanan.printSimpananMatrix();
}

void Pemain::makan() {
    if (this->penyimpanan.check("Makanan")) {
        cout << "Pilih makanan dari penyimpanan" << endl;
        this->printPenyimpanan();
        std::pair<int, int> barisdankolomsimpanan = this->penyimpanan.extractSlot();
        Simpanan* simpanan = this->penyimpanan.getValue(barisdankolomsimpanan.first, barisdankolomsimpanan.second);
        Produk* produk = dynamic_cast<Produk*>(simpanan);
        while (!produk || produk->getBeratTambahan() == 0) {
            cout << "Ini bukan makanan!" << endl;
            cout << "Silahkan masukan slot yang berisi makanan" << endl;
            barisdankolomsimpanan = this->penyimpanan.extractSlot();
            simpanan = this->penyimpanan.getValue(barisdankolomsimpanan.first, barisdankolomsimpanan.second);
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

Walikota::Walikota(string username, int uang, int berat, Matrix<Simpanan> inventory) : Pemain(username, uang, berat, inventory){
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

Petani::Petani(string username, int uang, int berat, Matrix<Simpanan> inventory, Matrix<Tanaman> kebun) : Pemain(username, uang, berat, inventory), ladang(kebun.getBaris(), kebun.getKolom()) {
    for (int i = 1; i <= this->ladang.getBaris(); i++){
        for (int j = 1; j <= this->ladang.getKolom(); j++){
            this->ladang.setValue(i, j, kebun.getValue(i, j));
        }
    } cout << "Petani " << this->username << " siap bermain!" << endl;
    Petani::jumlahPetani++;
}

void Petani::tanam() {
    if (this->penyimpanan.check("Tanaman")) {
        cout << "Pilih tanaman dari penyimpanan" << endl;
        this->printPenyimpanan();
        std::pair<int, int> barisdankolomsimpanan = this->penyimpanan.extractSlot();
        Simpanan* simpanan = this->penyimpanan.getValue(barisdankolomsimpanan.first, barisdankolomsimpanan.second);
        Tanaman* tanaman = dynamic_cast<Tanaman*>(simpanan);
        while (!tanaman) {
            cout << "Ini bukan tanaman!" << endl;
            cout << "Silahkan masukan slot yang berisi tanaman" << endl;
            barisdankolomsimpanan = this->penyimpanan.extractSlot();
            simpanan = this->penyimpanan.getValue(barisdankolomsimpanan.first, barisdankolomsimpanan.second);
            tanaman = dynamic_cast<Tanaman*>(simpanan);   
        }
        cout << "Kamu memilih " << tanaman->getNama() << "." << endl;
        cout << "Pilih petak tanah yang akan ditanami" << endl;
        this->ladang.printSimpananMatrix();
        std::pair<int, int> barisdankolomladang = this->ladang.extractSlot();
        Tanaman* petak = this->ladang.getValue(barisdankolomladang.first, barisdankolomladang.second);
        while (petak != nullptr) {
            cout << "Petak tanah ini sudah terisi" << endl;
            cout << "Silahkan pilih petak tanah yang kosong" << endl;
            barisdankolomladang = this->ladang.extractSlot();
            petak = this->ladang.getValue(barisdankolomladang.first, barisdankolomladang.second);
        }
        this->ladang.setValue(barisdankolomladang.first, barisdankolomladang.second, tanaman);  
        this->penyimpanan.setValue(barisdankolomsimpanan.first, barisdankolomsimpanan.second, nullptr);      
    }
    else {
        cout << "Perintah tidak dapat dijalankan" << endl;
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

Peternak::Peternak(string username, int uang, int berat, Matrix<Simpanan> inventory, Matrix<Hewan> ternak) : Pemain(username, uang, berat, inventory), peternakan(ternak.getBaris(), ternak.getKolom()) {
    for (int i = 1; i <= this->peternakan.getBaris(); i++){
        for (int j = 1; j <= this->peternakan.getKolom(); j++){
            this->peternakan.setValue(i, j, ternak.getValue(i, j));
        }
    }
    Peternak::jumlahPeternak++;
    cout << "Peternak " << this->username << " siap bermain!" << endl;
}