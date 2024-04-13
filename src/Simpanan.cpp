#include "Simpanan.hpp"
#include <iostream>
using namespace std;

// Apakah ID mau automatisasi berdasarkan jumlah 
// barang atau tidak?

// Versi tidak automatis

// Simpanan
Simpanan::Simpanan() {
    this->kode = "XXXX";
}

Simpanan::~Simpanan(){}

Simpanan::Simpanan(int id, string kode, string name, string tipe) {
    this->id = id;
    this->kode = kode;
    this->name = name;
    this->tipe = tipe;
    cout << "Simpanan " << this->name << " berhasil dibuat" << endl;
}

string Simpanan::getKode() {
    return this->kode;
}

string Simpanan::getIsi() {
    return this->kode + " " + this->name + " " + this->tipe;
}


// Bangunan
Bangunan::Bangunan(int id, string kode, string name, string tipe, map<string, int> material) : Simpanan(id, kode, name, tipe){
    this->material = material;
    cout << "Bangunan " << this->name << " berhasil dibangun" << endl;
}

map<string, int> Bangunan::getMats(){
    return this->material;
}

// Item
Item::Item() : Simpanan() {}

Item::Item(int id, string kode, string name, string tipe, int harga) : Simpanan(id, kode, name, tipe) {
    this->harga = harga;
    cout << "Item " << this->name << " berhasil dibuat" << endl;
}

int Item::getHarga(){
    return this->harga;
}

// Hewan
Hewan::Hewan() : Item() {}

Hewan::Hewan(int id, string kode, string name, string tipe, int harga, int beratUntukPanen, int berat) : Item(id, kode, name, tipe, harga) {
    this->beratUntukPanen = beratUntukPanen;
    this->berat = berat;
    cout << "Hewan " << this->name << " berhasil dilahirkan" << endl;
}

// Tanaman
Tanaman::Tanaman() : Item() {}

Tanaman::Tanaman(int id, string kode, string name, string tipe, int harga, int umurUntukPanen, int umur) : Item(id, kode, name, tipe, harga) {
    this->umurUntukPanen = umurUntukPanen;
    this->umur = umur;
    cout << "Tanaman " << this->name << " berhasil ditanam" << endl;
}

void Tanaman::tambahUmur() {
    this->umur++;
}

// Produk
Produk::Produk(int id, string kode, string name, string tipe, int harga, string origin, int beratTambahan) : Item(id, kode, name, tipe, harga) {
    this->origin = origin;
    this->beratTambahan = beratTambahan;
    cout << "Produk " << this->name << " berhasil dihasilkan" << endl;
}


