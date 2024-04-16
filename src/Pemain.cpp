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

int Walikota::getNetoKekayaan(Pemain* p) {
    //Neto kekayaan terdiri dari uang, harga setiap penyimpanan, dan harga setiap lahan/peternakan (bangunan termasuk penyimpanan).
    int netoKekayaan = 0;

    //Uang (gulden)
    netoKekayaan += p->getUang();

    //Penyimpanan
    for (int i=1; i<=p->getPenyimpanan().getBaris(); i++){
        for (int j=1; j<=p->getPenyimpanan().getKolom(); j++){
            if (p->getPenyimpanan().getValue(i,j) != nullptr){
                netoKekayaan += p->getPenyimpanan().getValue(i, j)->getHarga();
            }
        }
    }

    //Lahan/Peternakan
    if(Petani* p2 = dynamic_cast<Petani*>(p)){
    for (int i=1; i<=p2->getLadang().getBaris(); i++){
        for (int j=1; j<=p2->getLadang().getKolom(); j++){
            if (p2->getLadang().getValue(i,j) != nullptr){
                netoKekayaan += p2->getLadang().getValue(i, j)->getHarga();
            }
        }
    }
    }
    else if (Peternak* p2 = dynamic_cast<Peternak*>(p)){
    for (int i=1; i<=p2->getPeternakan().getBaris(); i++){
        for (int j=1; j<=p2->getPeternakan().getKolom(); j++){
            if (p2->getPeternakan().getValue(i,j) != nullptr){
                netoKekayaan += p2->getPeternakan().getValue(i, j)->getHarga();
            }
        }
    }
    }

	return 0;
}

float Walikota::getTarifBesaranPajak(int KKP) {
    if (KKP <= 0) return 0;
    else if (KKP <= 6) return 0.05;
    else if (KKP <= 25) return 0.15;
    else if (KKP <= 50) return 0.25;
    else if (KKP <= 500) return 0.3;
    else return 0.35;
}

void Walikota::pungutPajak(){
    int indexWalikota;
    int KTKP;
    int uangPemain;
    int hasilPajak = 0;
    int currentPajak;
    vector<Pemain*> sortedPemain;

    for (int i=0; i<ListPemain::getListPemain().size(); i++){
        if (!dynamic_cast<Walikota*>(ListPemain::getListPemain()[i])){
            currentPajak = 0;
            uangPemain = ListPemain::getListPemain()[i]->getUang();
            if (dynamic_cast<Peternak*>(ListPemain::getListPemain()[i])){
                KTKP = 11;
            }
            else { //Petani
                KTKP = 13;
            }
            
            currentPajak = (uangPemain - KTKP) * getTarifBesaranPajak(uangPemain);
            ListPemain::getListPemain()[i]->setUang(uangPemain - currentPajak); //Untested
            hasilPajak += currentPajak;

            if (sortedPemain.size() == 0){
                sortedPemain.push_back(ListPemain::getListPemain()[i]);
            }
            else{
                int j = 0;
                bool found = false;
                while (j < sortedPemain.size() && !found){
                    if (sortedPemain[j]->getUang() < uangPemain){
                        sortedPemain.insert(sortedPemain.begin() + j, ListPemain::getListPemain()[i]);
                    }
                    j++;
                }
                if (!found) sortedPemain.push_back(ListPemain::getListPemain()[i]);
            }
            
        }
        else{
            indexWalikota = i;
        }
    }

    ListPemain::getListPemain()[indexWalikota]->setUang(
        ListPemain::getListPemain()[indexWalikota]->getUang() + hasilPajak
    );

    cout << "Cring cring cring..." << endl;
    cout << "Pajak sudah dipungut!" << endl << endl;
    cout << "Berikut adalah detil dari pemungutan pajak:" << endl;
    for (int i=0; i<sortedPemain.size(); i++){
        cout << "  " << i+1 << ". " << sortedPemain[i]->getName() << " - ";
        if (dynamic_cast<Peternak*>(ListPemain::getListPemain()[i])){
            cout << "Peternak: ";
        }
        else { //Petani
            cout << "Petani: ";
        }
        cout << sortedPemain[i]->getUang() << " gulden" << endl;
    }

    cout << "Negara mendapatkan pemasukan sebesar "<< hasilPajak << " gulden." << endl;
    cout << "Gunakan dengan baik dan jangan dikorupsi ya!" << endl;

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

void Pemain::setUang(int newUang){
	this->uang = newUang;
}

Matrix<Simpanan> Pemain::getPenyimpanan(){
	return this->penyimpanan;
}

Matrix<Tanaman> Petani::getLadang(){
	return this->ladang;
}

Matrix<Hewan> Peternak::getPeternakan(){
	return this->peternakan;
}
