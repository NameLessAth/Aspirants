#include "Matrix.hpp"
#include "Simpanan.hpp"
#include <iostream>
#include <set>
using namespace std;

template<class T>
Matrix<T>::Matrix(int baris, int kolom) : baris(baris), kolom(kolom) {
    this->matrix = new T**[this->baris];
    for (int i = 0; i < this->baris; i++) {
        matrix[i] = new T*[this->kolom];
        for (int j = 0; j < this->kolom; j++) {
            matrix[i][j] = new T();
        }
    }
    this->banyakIsi = 0;
}

template<class T>
Matrix<T>::~Matrix() {
    for (int i = 0; i < this->baris; ++i) {
        delete[] this->matrix[i];
    }
    delete[] this->matrix;
}

template <class T>
int Matrix<T>::getBanyakIsi(){
    return this->banyakIsi;
}

template<class T>
void Matrix<T>::setValue(int row, int col, T* value) {
    if (row >= 1 && row <= this->baris && col >= 1 && col <= this->kolom) {
        if (value == nullptr) {
            matrix[row - 1][col - 1] = new T();
            this->banyakIsi--;
        }
        else {
            matrix[row - 1][col - 1] = value;
            this->banyakIsi++;
        }
    } else {
        throw IndexPenyimpananOutOfBounds(); // Nanti diubah jadi throw error
    }
}

template <class T>
const int Matrix<T>::getBaris(){
    return this->baris;
}

template <class T>
const int Matrix<T>::getKolom(){
    return this->kolom;
}

template<>
void Matrix<Simpanan>::addNearby(Simpanan *value){
    if (this->banyakIsi == this->baris*this->kolom) throw FullStorage();
    else{
        int i = 1, j = 1; bool ketemu = false;
        while(!ketemu){
            if (this->getValue(i, j)->getKode() == "XXXX") ketemu = true;
            else{
                j++; 
                if (j > this->kolom){
                    j = 1; i++;
                }
            }
        } this->setValue(i, j, value);
    }
}

template<>
void Matrix<Tanaman>::addNearby(Tanaman *value){
    if (this->banyakIsi == this->baris*this->kolom) throw FullStorage();
    else{
        int i = 1, j = 1; bool ketemu = false;
        while(!ketemu){
            if (this->getValue(i, j)->getKode() == "XXXX") ketemu = true;
            else{
                j++; if (j > this->kolom){
                    j = 1; i++;
                }
            }
        } this->setValue(i, j, value);
    }
}

template<>
void Matrix<Hewan>::addNearby(Hewan *value){
    if (this->banyakIsi == this->baris*this->kolom) throw FullStorage();
    else{
        int i = 1, j = 1; bool ketemu = false;
        while(!ketemu){
            if (this->getValue(i, j)->getKode() == "XXXX") ketemu = true;
            else{
                j++; if (j > this->kolom){
                    j = 1; i++;
                }
            }
        } this->setValue(i, j, value);
    }
}

template <class T>
T* Matrix<T>::getValue(int baris, int kolom) {
    if (baris >= 1 && baris <= this->baris && kolom >= 1 && kolom <= this->kolom) {
        return this->matrix[baris - 1][kolom - 1];
    } else {
         throw IndexPenyimpananOutOfBounds(); // Nanti diubah jadi throw error
    }
}

template<class T>
std::pair<int,int> Matrix<T>::extractSlot() {
    // this->printSimpananMatrix();
    // cout << "Slot: ";
    string slot;
    cin >> slot;
    char hurufKolom = slot[0];
    int baris = stoi(slot.substr(1));
    int kolom = toupper(hurufKolom) - 'A' + 1;
    return std::make_pair(baris, kolom);
}

// template <>
// Simpanan* Matrix<Simpanan>::extractSlot() {
//     string slot;
//     this->printSimpananMatrix();
//     cout << "Slot: ";
//     cin >> slot;
//     char hurufKolom = slot[0];
//     int baris = stoi(slot.substr(1));
//     int kolom = toupper(hurufKolom) - 'A' + 1;
//     if (getValue(baris, kolom) == nullptr) {
//         cerr << "Kamu mengambil harapan kosong dari penyimpanan.\nSilahkan masukan slot yang tidak kosong.";
//     }
//     else {
//         return getValue(baris, kolom);
//     }
// }

// template <>
// Tanaman* Matrix<Tanaman>::extractSlot() {
//     string slot;
//     this->printSimpananMatrix();
//     cout << "Petak tanah: ";
//     cin >> slot;
//     char hurufKolom = slot[0];
//     int baris = stoi(slot.substr(1));
//     int kolom = toupper(hurufKolom) - 'A' + 1;
//     return getValue(baris, kolom);
// }

template<class T>
void Matrix<T>::printGaris() {
    cout << "\t+";
    for (int i = 0; i < this->kolom; i++) {
        cout << "-------+";
    }
    cout << endl;
}

template<>
void Matrix<Simpanan>::printSimpananMatrix() {
    cout << "================[ Penyimpanan ]==================" << endl;
    cout << "\t";
    for (int i = 0; i < this->kolom; i++) {
        cout << char('A' + i) << "\t";
    }
    cout << endl;
    this->printGaris();
    for (int i = 0; i < this->baris; i++) {
        cout << i+1 << "\t|";
        for (int j = 0; j < this->kolom; j++) {
            cout << "  ";
            if (this->matrix[i][j]->getKode() != "XXXX") {
                cout << this->matrix[i][j]->getKode();
                cout << "  |";
            } else {
                cout << "     |";
            }
        }
        cout << endl;
        this->printGaris();
    }
    cout << "Total slot kosong: " << this->baris * this->kolom - this->banyakIsi << endl;
}


// Untuk perintah CETAK_LADANG (belum ada fitur warna untuk siap panen)
template<>
void Matrix<Tanaman>::printSimpananMatrix() {
    cout << "================[ Ladang ]==================" << endl;
    cout << "\t";
    for (int i = 0; i < this->kolom; i++) {
        cout << char('A' + i) << "\t";
    }
    cout << endl;
    this->printGaris();
    std::set<std::string> KodedanNamaUnik;
    std::string KodedanNama;
    for (int i = 0; i < this->baris; i++) {
        cout << i+1 << "\t|";
        for (int j = 0; j < this->kolom; j++) {
            cout << "  ";
            if (this->matrix[i][j]->getKode() != "XXXX") {
                cout << this->matrix[i][j]->getKode();
                cout << "  |";
                KodedanNama = "- " + this->matrix[i][j]->getKode() + ": " + this->matrix[i][j]->getNama();
                KodedanNamaUnik.insert(KodedanNama);
            } else {
                cout << "     |";
            }
        }
        cout << endl;
        this->printGaris();
    }
    for (const std::string& KodedanNama : KodedanNamaUnik) {
        cout << KodedanNama << "\n";
    }
}

// Untuk perintah CETAK_PETERNAKAN (belum ada fitur warna untuk siap panen)
template<>
void Matrix<Hewan>::printSimpananMatrix() {
    cout << "================[ Peternakan ]==================" << endl;
    cout << "\t";
    for (int i = 0; i < this->kolom; i++) {
        cout << char('A' + i) << "\t";
    }
    cout << endl;
    this->printGaris();
    std::set<std::string> KodedanNamaUnik;
    for (int i = 0; i < this->baris; i++) {
        cout << i+1 << "\t|";
        for (int j = 0; j < this->kolom; j++) {
            cout << "  ";
            if (this->matrix[i][j]->getKode() != "XXXX") {
                cout << this->matrix[i][j]->getKode();
                cout << "  |";
                std::string KodedanNama = "- " + this->matrix[i][j]->getKode() + ": " + this->matrix[i][j]->getNama();
                KodedanNamaUnik.insert(KodedanNama);
            } else {
                cout << "     |";
            }
        }
        cout << endl;
        this->printGaris();
    }
    for (const std::string& KodedanNama : KodedanNamaUnik) {
        cout << KodedanNama << "\n";
    }
}

template<class T>
bool Matrix<T>::isEmpty() {
    return (this->banyakIsi == 0);
}

template<class T>
bool Matrix<T>::isFull() {
    return (this->banyakIsi <= this->baris * this->kolom);
}

template<>
bool Matrix<Simpanan>::check(std::string kelas) {
    bool found = false;
    Simpanan* simpanan;
    if (kelas == "Tanaman") {
        for (int i = 1; i <= this->baris; ++i) {
            for (int j = 1; j <= this->kolom; ++j) {
                simpanan = this->getValue(i, j);
                if (dynamic_cast<Tanaman*>(simpanan)) {
                    found = true;
                    break;
                }
            }
        }
    }
    else if (kelas == "Hewan") {
        for (int i = 1; i <= this->baris; ++i) {
            for (int j = 1; j <= this->kolom; ++j) {
                simpanan = this->getValue(i, j);
                if (dynamic_cast<Hewan*>(simpanan)) {
                    found = true;
                    break;
                }
            }
        }
    }
    else if (kelas == "Makanan") {
        for (int i = 1; i <= this->baris; ++i) {
            for (int j = 1; j <= this->kolom; ++j) {
                simpanan = this->getValue(i, j);
                Produk* makanan = dynamic_cast<Produk*>(simpanan);
                if (makanan && makanan->getBeratTambahan() > 0) {
                    found = true;
                    break;
                }
            }
        }
    }
    return found;
}

template<>
int Matrix<Tanaman>::countSiapPanen(std::string kode) {
    int retval = 0;
    for (int i = 0; i < this->baris; i++) {
        for (int j = 0; j < this->kolom; j++) {
            if ((this->getValue(i, j)->getKode() == kode) && (this->getValue(i, j)->getUmur() >= this->getValue(i, j)->getUmurUntukPanen())) {
                retval++;
            }
        }
    }
    return retval;
}

// template<>
// void Matrix<Simpanan>::printMatrix() {
//     cout << "\t";
//     for (int i = 0; i < this->kolom; i++) {
//         cout << char('A' + i) << "\t";
//     }
//     cout << endl;
//     cout << "\t+-------+-------+-------+-------+-------+" << endl;
//     for (int i = 0; i < this->baris; i++) {
//         cout << i+1 << "\t|";
//         for (int j = 0; j < this->kolom; j++) {
//             cout << "  ";
//             if (this->matrix[i][j].getKode() != "XXXX") {
//                 cout << this->matrix[i][j].getKode();
//             } else {
//                 cout << "";
//             }
//             cout << "\t|";
//         }
//         cout << endl;
//         cout << "\t+-------+-------+-------+-------+-------+" << endl;
//     }
//     cout << "Total slot kosong: " << this->baris*this->kolom - this->banyakIsi << endl;
// }

// template<>
// void Matrix<Hewan>::printMatrix() {
//     cout << "\t";
//     for (int i = 0; i < this->kolom; i++) {
//         cout << char('A' + i) << "\t";
//     }
//     cout << endl;
//     cout << "\t+-------+-------+-------+-------+-------+" << endl;
//     for (int i = 0; i < this->baris; i++) {
//         cout << i+1 << "\t|";
//         for (int j = 0; j < this->kolom; j++) {
//             cout << "  ";
//             if (this->matrix[i][j].getKode() != "XXXX") {
//                 cout << this->matrix[i][j].getKode();
//             } else {
//                 cout << "";
//             }
//             cout << "\t|";
//         }
//         cout << endl;
//         cout << "\t+-------+-------+-------+-------+-------+" << endl;
//     }
//     cout << "Total slot kosong: " << this->baris*this->kolom - this->banyakIsi << endl;
// }

// template<>
// void Matrix<Tanaman>::printMatrix() {
//     cout << "\t";
//     for (int i = 0; i < this->kolom; i++) {
//         cout << char('A' + i) << "\t";
//     }
//     cout << endl;
//     cout << "\t+-------+-------+-------+-------+-------+" << endl;
//     for (int i = 0; i < this->baris; i++) {
//         cout << i+1 << "\t|";
//         for (int j = 0; j < this->kolom; j++) {
//             cout << "  ";
//             if (this->matrix[i][j].getKode() != "XXXX") {
//                 cout << this->matrix[i][j].getKode();
//             } else {
//                 cout << "";
//             }
//             cout << "\t|";
//         }
//         cout << endl;
//         cout << "\t+-------+-------+-------+-------+-------+" << endl;
//     }
//     cout << "Total slot kosong: " << this->baris*this->kolom - this->banyakIsi << endl;
// }


// template class Matrix<int>;
template class Matrix<Simpanan>;
template class Matrix<Hewan>;
template class Matrix<Tanaman>;