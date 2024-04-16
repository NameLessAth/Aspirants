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
}

string Simpanan::getKode() {
    return this->kode;
}

string Simpanan::getIsi() {
    return this->kode + " " + this->name + " " + this->tipe;
}

string Simpanan::getNama() const {
    return this->name;
}

int Simpanan::getHarga() const {
    return this->harga;
}

// Bangunan
Bangunan::Bangunan() : Simpanan() {}

Bangunan::Bangunan(int id, string kode, string name, string tipe, int harga, map<string, int> material) : Simpanan(id, kode, name, tipe, harga){
    this->material = material;
}

void Bangunan::setTipe(string tipe){
    this->tipe = tipe;
}

map<string, int> Bangunan::getMats(){
    return this->material;
}

// Hewan
Hewan::Hewan() : Simpanan() {}

Hewan::Hewan(int id, string kode, string name, string tipe, int harga, int beratUntukPanen, int berat) : Simpanan(id, kode, name, tipe, harga) {
    this->beratUntukPanen = beratUntukPanen;
    this->berat = berat;
}

void Hewan::setBerat(int berat){
    this->berat = berat;
}

void Hewan::tambahBerat(int beratTambahan) {
    this->berat += beratTambahan;
}

int Hewan::getBerat() {
    return this->berat;
}

// Tanaman
Tanaman::Tanaman() : Simpanan() {}

Tanaman::Tanaman(int id, string kode, string name, string tipe, int harga, int umurUntukPanen, int umur) : Simpanan(id, kode, name, tipe, harga) {
    this->umurUntukPanen = umurUntukPanen;
    this->umur = umur;
}

void Tanaman::setUmur(int umur){
    this->umur = umur;
}

int Tanaman::getUmur(){
    return this->umur;
}

int Tanaman::getUmurUntukPanen() {
    return this->umurUntukPanen;
}

void Tanaman::tambahUmur() {
    this->umur++;
}

// Produk
Produk::Produk() : Simpanan() {}

Produk::Produk(int id, string kode, string name, string tipe, int harga, string origin, int beratTambahan) : Simpanan(id, kode, name, tipe, harga) {
    this->origin = origin;
    this->beratTambahan = beratTambahan;
}

int Produk::getBeratTambahan() {
    return this->beratTambahan;
}
