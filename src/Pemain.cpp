#include "Pemain.hpp"
#include "Simpanan.hpp"
#include <iostream>
#include <string>
using namespace std;

// Pemain
int Pemain::jumlahPemain = 0;
int Pemain::barisPenyimpanan = 10; // Berdasarkan berkas
int Pemain::kolomPenyimpanan = 10; // Berdasarkan berkas
vector<Pemain*> ListPemain::listPemain;

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

void Pemain::makan() {
    if (this->penyimpanan.check("Makanan")) {
        cout << "Pilih makanan dari penyimpanan" << endl;
        this->penyimpanan.printSimpananMatrix();
        cout << "Slot: ";
        std::pair<int, int> barisdankolomsimpanan = this->penyimpanan.extractSlot();
        Simpanan* simpanan = this->penyimpanan.getValue(barisdankolomsimpanan.first, barisdankolomsimpanan.second);
        Produk* produk = dynamic_cast<Produk*>(simpanan);
        while (!produk || produk->getBeratTambahan() == 0) {
            if (simpanan == nullptr) {
                cout << "Kamu mengambil harapan kosong dari penyimpanan." << endl;
            }
            else {
                cout << "Ini bukan makanan!" << endl;
            }
            cout << "Silahkan masukan slot yang berisi makanan" << endl;
            cout << "Slot: ";
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

int Pemain::getUang(){
    return this->uang;
}

int Pemain::getBerat(){
    return this->beratBadan;
}

string Pemain::getName(){
    return this->username;
}

vector<Pemain*> ListPemain::getListPemain(){
    return ListPemain::listPemain;
}

void ListPemain::setListPemain(vector<Pemain *> inputListPemain){
    ListPemain::listPemain.clear();
    for(int i=0;i<inputListPemain.size();i++){
        ListPemain::listPemain.push_back(inputListPemain[i]);
    }
}

void ListPemain::pushPemain(Pemain * p){
    ListPemain::listPemain.push_back(p);
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
    if (this->penyimpanan.check("Tanaman") && !this->ladang.isFull()) {
        cout << "Pilih tanaman dari penyimpanan" << endl;
        this->penyimpanan.printSimpananMatrix();
        cout << "Slot: ";
        std::pair<int, int> barisdankolomsimpanan = this->penyimpanan.extractSlot();
        Simpanan* simpanan = this->penyimpanan.getValue(barisdankolomsimpanan.first, barisdankolomsimpanan.second);
        Tanaman* tanaman = dynamic_cast<Tanaman*>(simpanan);
        while (!tanaman) {
            cout << "Ini bukan tanaman!" << endl;
            cout << "Silahkan masukan slot yang berisi tanaman" << endl;
            cout << "Slot: ";
            barisdankolomsimpanan = this->penyimpanan.extractSlot();
            simpanan = this->penyimpanan.getValue(barisdankolomsimpanan.first, barisdankolomsimpanan.second);
            tanaman = dynamic_cast<Tanaman*>(simpanan);   
        }
        cout << "Kamu memilih " << tanaman->getNama() << "." << endl;
        cout << "Pilih petak tanah yang akan ditanami" << endl;
        this->ladang.printSimpananMatrix();
        cout << "Petak tanah: ";
        std::pair<int, int> barisdankolomladang = this->ladang.extractSlot();
        Tanaman* petak = this->ladang.getValue(barisdankolomladang.first, barisdankolomladang.second);
        while (petak != nullptr) {
            cout << "Petak tanah ini sudah terisi" << endl;
            cout << "Silahkan pilih petak tanah yang kosong" << endl;
            cout << "Petak tanah: ";
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

void Peternak::kasihMakan() {
    if (this->penyimpanan.check("Makanan") && !this->peternakan.isEmpty()) {
        cout << "Pilih petak kandang yang akan ditinggali" << endl;
        this->peternakan.printSimpananMatrix();
        cout << "Petak kandang: ";
        std::pair<int, int> barisdankolompeternakan = this->peternakan.extractSlot();
        Simpanan* simpanan = this->penyimpanan.getValue(barisdankolompeternakan.first, barisdankolompeternakan.second);
        Hewan* hewan = dynamic_cast<Hewan*>(simpanan);
        while (hewan == nullptr) {
            cout << "Kamu mengambil harapan kosong dari peternakan" << endl;
            cout << "Silahkan masukan petak kandang yang ditinggali hewan" << endl;
            cout << "Slot: ";
            barisdankolompeternakan = this->peternakan.extractSlot();
            simpanan = this->penyimpanan.getValue(barisdankolompeternakan.first, barisdankolompeternakan.second);
            hewan = dynamic_cast<Hewan*>(simpanan);   
        }
        cout << "Kamu memilih " << hewan->getNama() << " untuk diberi makan." << endl;
        cout << "Pilih pangan yang akan diberikan:" << endl;
        this->penyimpanan.printSimpananMatrix();
        cout << "Slot: ";
        std::pair<int, int> barisdankolomsimpanan = this->peternakan.extractSlot();
        simpanan = this->penyimpanan.getValue(barisdankolompeternakan.first, barisdankolompeternakan.second);
        Produk* produk = dynamic_cast<Produk*>(simpanan);
        while (!produk || produk->getBeratTambahan() == 0) {
            if (simpanan == nullptr) {
                cout << "Kamu mengambil harapan kosong dari penyimpanan." << endl;
            }
            else {
                cout << "Ini bukan makanan!" << endl;
            }
            cout << "Silahkan masukan slot yang berisi makanan" << endl;
            cout << "Slot: ";
            barisdankolomsimpanan = this->penyimpanan.extractSlot();
            simpanan = this->penyimpanan.getValue(barisdankolomsimpanan.first, barisdankolomsimpanan.second);
            produk = dynamic_cast<Produk*>(simpanan);
        }
        hewan->tambahBerat(produk->getBeratTambahan());
        this->penyimpanan.setValue(barisdankolomsimpanan.first, barisdankolomsimpanan.second, nullptr);
        cout << hewan->getNama() << " sudah diberi makan dan beratnya menjadi " << hewan->getBerat() << endl;
    }
}

void Peternak::ternak() {
    if (this->penyimpanan.check("Hewan") && !this->peternakan.isFull()) {
        cout << "Pilih hewan dari penyimpanan" << endl;
        this->penyimpanan.printSimpananMatrix();
        cout << "Slot: ";
        std::pair<int, int> barisdankolomsimpanan = this->penyimpanan.extractSlot();
        Simpanan* simpanan = this->penyimpanan.getValue(barisdankolomsimpanan.first, barisdankolomsimpanan.second);
        Hewan* hewan = dynamic_cast<Hewan*>(simpanan);
        while (!hewan) {
            cout << "Ini bukan hewan!" << endl;
            cout << "Silahkan masukan slot yang berisi hewan" << endl;
            cout << "Slot: ";
            barisdankolomsimpanan = this->penyimpanan.extractSlot();
            simpanan = this->penyimpanan.getValue(barisdankolomsimpanan.first, barisdankolomsimpanan.second);
            hewan = dynamic_cast<Hewan*>(simpanan);   
        }
        cout << "Kamu memilih " << hewan->getNama() << "." << endl;
        cout << "Pilih petak tanah yang akan ditinggali" << endl;
        this->peternakan.printSimpananMatrix();
        cout << "Petak tanah: ";
        std::pair<int, int> barisdankolompeternakan = this->peternakan.extractSlot();
        Hewan* petak = this->peternakan.getValue(barisdankolompeternakan.first, barisdankolompeternakan.second);
        while (petak != nullptr) {
            cout << "Petak tanah ini sudah terisi" << endl;
            cout << "Silahkan pilih petak tanah yang kosong" << endl;
            cout << "Petak tanah: ";
            barisdankolompeternakan = this->peternakan.extractSlot();
            petak = this->peternakan.getValue(barisdankolompeternakan.first, barisdankolompeternakan.second);
        }
        this->peternakan.setValue(barisdankolompeternakan.first, barisdankolompeternakan.second, hewan);  
        this->penyimpanan.setValue(barisdankolomsimpanan.first, barisdankolomsimpanan.second, nullptr);      
    }
    else {
        cout << "Perintah tidak dapat dijalankan" << endl;
    }
}


