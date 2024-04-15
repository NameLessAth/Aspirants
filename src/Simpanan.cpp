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

Simpanan::Simpanan(int id, string kode, string name, string tipe, int harga) {
    this->id = id;
    this->kode = kode;
    this->name = name;
    this->tipe = tipe;
    this->harga = harga;
    cout << "Simpanan " << this->name << " berhasil dibuat" << endl;
}

string Simpanan::getKode() {
    return this->kode;
}

string Simpanan::getIsi() {
    return this->kode + " " + this->name + " " + this->tipe;
}

string Simpanan::getNama() {
    return this->name;
}

int Simpanan::getHarga(){
    return this->harga;
}

// Bangunan
Bangunan::Bangunan() : Simpanan() {}

Bangunan::Bangunan(int id, string kode, string name, string tipe, int harga, map<string, int> material) : Simpanan(id, kode, name, tipe, harga){
    this->material = material;
    cout << "Bangunan " << this->name << " berhasil dibangun" << endl;
}

map<string, int> Bangunan::getMats(){
    return this->material;
}

// Hewan
Hewan::Hewan() : Simpanan() {}

Hewan::Hewan(int id, string kode, string name, string tipe, int harga, int beratUntukPanen, int berat) : Simpanan(id, kode, name, tipe, harga) {
    this->beratUntukPanen = beratUntukPanen;
    this->berat = berat;
    cout << "Hewan " << this->name << " berhasil dilahirkan" << endl;
}

// Tanaman
Tanaman::Tanaman() : Simpanan() {}

Tanaman::Tanaman(int id, string kode, string name, string tipe, int harga, int umurUntukPanen, int umur) : Simpanan(id, kode, name, tipe, harga) {
    this->umurUntukPanen = umurUntukPanen;
    this->umur = umur;
    cout << "Tanaman " << this->name << " berhasil ditanam" << endl;
}

void Tanaman::tambahUmur() {
    this->umur++;
}

// Produk
Produk::Produk() : Simpanan() {}

Produk::Produk(int id, string kode, string name, string tipe, int harga, string origin, int beratTambahan) : Simpanan(id, kode, name, tipe, harga) {
    this->origin = origin;
    this->beratTambahan = beratTambahan;
    cout << "Produk " << this->name << " berhasil dihasilkan" << endl;
}

int Produk::getBeratTambahan() {
    return this->beratTambahan;
}
