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

Pemain::Pemain(string nama) : penyimpanan(Pemain::barisPenyimpanan, Pemain::kolomPenyimpanan) {
    Pemain::jumlahPemain++;
    this->username = nama;
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
        Produk* makanan = dynamic_cast<Produk*>(simpanan);
        while (!makanan || makanan->getBeratTambahan() == 0) {
            if (simpanan->getKode() == "XXXX") {
                cout << "Kamu mengambil harapan kosong dari penyimpanan." << endl;
            }
            else {
                cout << "Ini bukan makanan!" << endl;
            }
            cout << "Silahkan masukan slot yang berisi makanan" << endl;
            cout << "Slot: ";
            barisdankolomsimpanan = this->penyimpanan.extractSlot();
            simpanan = this->penyimpanan.getValue(barisdankolomsimpanan.first, barisdankolomsimpanan.second);
            makanan = dynamic_cast<Produk*>(simpanan);   
        }
        cout << "Dengan lahapnya, kamu memakanan hidangan itu" << endl;
        this->beratBadan += makanan->getBeratTambahan();
        cout << "Alhasil, berat badan kamu naik menjadi " << this->beratBadan << endl;
    } else {
        cout << "Perintah tidak dapat dijalankan" << endl;
    }
}


bool isNumber(string input){
    for(int i=0;i<input.length();i++){
        if(!isdigit(input[i])){
            return false;
        }
   }
   return true;
}

vector<string> separator(string input){
    vector<string> temp;
    temp.push_back(input.substr(0,3));
    input.erase(0,3);
    while(input.length()){
        input.erase(0,2);
        temp.push_back(input.substr(0,3));
        input.erase(0,3);
    }
    return temp;
}

void Pemain::beli(){
    if(this->penyimpanan.isFull()){
        throw FullStorage();
    }

    Toko::printToko();
    cout << "Uang anda : " << this->uang << "\nSlot penyimpanan tersedia : " << (this->barisPenyimpanan * this->kolomPenyimpanan) - this->penyimpanan.getBanyakIsi();

    string input;
    cout << "Barang yang ingin dibeli : ";
    cin >> input;

    if(!isNumber(input) || stoi(input) > Toko::manyItem() || stoi(input) == 0){
        throw InvalidInput();
    }

    int index = stoi(input);

    cout << "Kuantitas : ";
    cin >> input;

    if(!isNumber(input) || stoi(input) > Toko::manyItem() || stoi(input) == 0){
        throw InvalidInput();
    }

    int qty = stoi(input);

    if(dynamic_cast<Bangunan*>(Toko::getCatalogue()[index-1].first)){
        if(qty > Toko::getCatalogue()[index-1].second){
            throw InsufficientItems();
        }
        if(this->uang < qty * Toko::getCatalogue()[index-1].first->getHarga()){
            throw InsufficientMoney();
        } else {
            this->uang -= qty * Toko::getCatalogue()[index-1].first->getHarga();
            Toko::getCatalogue()[index-1].second -= qty;
        }
    } else {
        if(this->uang < qty * Toko::getCatalogue()[index-1].first->getHarga()){
            throw InsufficientMoney();
        } else {
            this->uang -= qty * Toko::getCatalogue()[index-1].first->getHarga();
        }
    }
    
    cout << "Selamat Anda berhasil membeli " << qty << " " << Toko::getCatalogue()[index-1].first->getNama() << ". Uang Anda tersisa " << this->uang << " gulden.\n\nPilih slot untuk menyimpan barang yang Anda beli!\n";

    this->penyimpanan.printSimpananMatrix();

    bool valid = true;
    cout << "Petak slot : ";
    cin >> input;
    vector<string> temp = separator(input);

    for(int i=0;i<temp.size();i++){
        char hurufKolom = temp[i][0];
        int baris = stoi(temp[i].substr(1));
        int kolom = toupper(hurufKolom) - 'A' + 1;
        if(this->penyimpanan.getValue(baris,kolom)->getKode() != "XXXX"){
            valid = false;
        }
    }

    while(!valid){
        cout << "Petak tidak valid!\nMasukkan petak slot : ";
        cin >> input;

        vector<string> temp = separator(input);

        for(int i=0;i<temp.size();i++){
            char hurufKolom = temp[i][0];
            int baris = stoi(temp[i].substr(1));
            int kolom = toupper(hurufKolom) - 'A' + 1;
            if(this->penyimpanan.getValue(baris,kolom)->getKode() != "XXXX"){
                continue;
            }
        }
        valid = true;
    }

    for(int i=0;i<temp.size();i++){
        char hurufKolom = temp[i][0];
        int baris = stoi(temp[i].substr(1));
        int kolom = toupper(hurufKolom) - 'A' + 1;
        this->penyimpanan.setValue(baris,kolom,Toko::getCatalogue()[index-1].first);
    }
}

void Pemain::jual(){
    cout << "Berikut merupakan penyimpanan Anda\n";
    this->penyimpanan.printSimpananMatrix();
    cout << "Silahkan pilih petak yang ingin Anda jual!\n";

    bool valid = true;
    string input;
    cout << "Petak slot : ";
    cin >> input;
    vector<string> temp = separator(input);

    for(int i=0;i<temp.size();i++){
        char hurufKolom = temp[i][0];
        int baris = stoi(temp[i].substr(1));
        int kolom = toupper(hurufKolom) - 'A' + 1;
        if(this->penyimpanan.getValue(baris,kolom)->getKode() == "XXXX"){
            valid = false;
        }
    }

    while(!valid){
        cout << "Petak tidak valid!\nMasukkan petak slot : ";
        cin >> input;

        vector<string> temp = separator(input);

        for(int i=0;i<temp.size();i++){
            char hurufKolom = temp[i][0];
            int baris = stoi(temp[i].substr(1));
            int kolom = toupper(hurufKolom) - 'A' + 1;
            if(this->penyimpanan.getValue(baris,kolom)->getKode() == "XXXX"){
                continue;
            }
        }
        valid = true;
    }

    int net=0;

    for(int i=0;i<temp.size();i++){
        char hurufKolom = temp[i][0];
        int baris = stoi(temp[i].substr(1));
        int kolom = toupper(hurufKolom) - 'A' + 1;
        Toko::insertItem(this->penyimpanan.getValue(baris,kolom),1);
        net += this->penyimpanan.getValue(baris,kolom)->getHarga();
        this->penyimpanan.setValue(baris,kolom,nullptr);
    }

    cout << "Barang Anda berhasil dijual! Uang Anda bertambah " << net << " gulden!\n";
    this->uang += net;
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


void Pemain::setUang(int newUang){
	this->uang = newUang;
}

Matrix<Simpanan> Pemain::getPenyimpanan(){
	return this->penyimpanan;
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

void ListPemain::next(){
    for(int i=0;i<ListPemain::listPemain.size();i++){
        if(Petani* p2 = dynamic_cast<Petani*>(ListPemain::listPemain[i])){
            for (int i=1; i<=p2->getLadang().getBaris(); i++){
                for (int j=1; j<=p2->getLadang().getKolom(); j++){
                    if (p2->getLadang().getValue(i,j) != nullptr){
                        p2->getLadang().getValue(i,j)->setUmur(p2->getLadang().getValue(i,j)->getUmur()+1);
                    }
                }
            }
        }
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
        }
    }

    this->setUang(
        this->getUang() + hasilPajak
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

void Walikota::bangunBangunan(){
    cout << "Resep bangunan yang ada adalah sebagai berikut.\n";
    vector<pair<Simpanan*, int>> temp = Toko::getCatalogue();
    vector<Bangunan> senarayBangunan;
    int iterator = 1;
    for(int i=0;i<temp.size();i++){
        if(dynamic_cast<Bangunan*>(temp[i].first)){
            cout << iterator << ". " << temp[i].first->getNama() << " (";
            Bangunan* b = dynamic_cast<Bangunan*>(temp[i].first);
            senarayBangunan.push_back(*b);
            map<string, int> tempmats = b->getMats();
            bool first = true;
            for(auto it = tempmats.cbegin(); it != tempmats.cend(); ++it){
                if(first){
                    cout << it->first << " " << it->second;
                    first = false;
                } else {
                    cout << ", " << it->first << " " << it->second;
                }
            }
            cout << ")\n";
        }
    }

    string input;
    cout << "Bangunan yang ingin dibangun: ";
    cin >> input;
    bool found = false;
    int index;

    for(int i=0;i<senarayBangunan.size();i++){
        if(input == senarayBangunan[i].getNama()){
            index = i;
            found = true;
            break;
        }
    }

    map<string,int> target = senarayBangunan[index].getMats();
    vector<int> x,y;

    Walikota *p = dynamic_cast<Walikota*>(this);
    for(int i=1; i<=p->getPenyimpanan().getBaris(); i++){
        for(int j=1; j<=p->getPenyimpanan().getKolom(); j++){
            if(target[p->getPenyimpanan().getValue(i,j)->getNama()] > 1){
                target[p->getPenyimpanan().getValue(i,j)->getNama()]--;
                x.push_back(i);
                y.push_back(j);
            } else if(target[p->getPenyimpanan().getValue(i,j)->getNama()] == 1){
                target.erase(p->getPenyimpanan().getValue(i,j)->getNama());
                x.push_back(i);
                y.push_back(j);
            }
        }
    }

    if(target.empty()){
        this->penyimpanan.addNearby(&senarayBangunan[index]);
        cout << senarayBangunan[index].getNama() << " berhasil dibangun dan telah menjadi hak milik walikota!\n";
        for(int i=0;i<x.size();i++){
            this->penyimpanan.setValue(x[i],y[i],nullptr);
        }
    } else {
        cout << "Kamu tidak punya sumber daya yang cukup! Masih memerlukan ";
        bool first = true;
        for(auto it = target.cbegin(); it != target.cend(); ++it){
            if(first){
                cout << it->second << " " << it->first;
                first = false;
            } else {
                cout << ", " << it->second << " " << it->first;
            }
        }
        cout << "!\n";
    }
}

void Walikota::tambahPemain(){
    string role;
    string name;

    if (this->getUang() < 50) throw InsufficientMoney();
    
    cout << "Masukkan jenis pemain (petani/peternak): ";
    cin >> role;
    if ((role != "peternak") && (role != "petani")) throw InvalidInput();

    cout << endl << "Masukkan nama pemain: ";
    cin >> name;

    for (int i=0; i<ListPemain::getListPemain().size(); i++){
        if (ListPemain::getListPemain()[i]->getName() == name){
            throw NameNotUnique();
        }
    }

    if (role == "petani"){
        Petani p(name);
        ListPemain::pushPemain(&p);
    }
    else{
        Peternak p(name);
        ListPemain::pushPemain(&p);
    }

    cout << "Pemain baru ditambahkan!" << endl;
    cout << "Selamat datang “" << name << "” di kota ini!" << endl;
    
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

Petani::Petani(string nama) : Pemain(nama), ladang(Petani::barisLadang, Petani::kolomLadang){
    Petani::jumlahPetani++;
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


Matrix<Tanaman> Petani::getLadang(){
	return this->ladang;
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

Peternak::Peternak(string nama) : Pemain(nama), peternakan(Peternak::barisTernak, Peternak::kolomTernak){
    Peternak::jumlahPeternak++;
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

Matrix<Hewan> Peternak::getPeternakan(){
	return this->peternakan;
}
