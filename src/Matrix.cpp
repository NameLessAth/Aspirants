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

template<class T>
void Matrix<T>::setValue(int row, int col, T* value) {
    if (row >= 1 && row <= this->baris && col >= 1 && col <= this->kolom) {
        matrix[row - 1][col - 1] = value;
        this->banyakIsi++;
    } else {
        cerr << "Index out of bounds!" << endl; // Nanti diubah jadi throw error
    }
}

template <class T>
T* Matrix<T>::getValue(int baris, int kolom) {
    if (baris >= 1 && baris < this->baris && kolom >= 1 && kolom < this->kolom) {
        return this->matrix[baris - 1][kolom - 1];
    } else {
        cerr << "Index out of bounds!" << endl; // Nanti diubah jadi throw error
    }
}

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

// Untuk perintah CETAK_PETERNAKAN (belum ada fitur warna untuk siap panen)
template<>
void Matrix<Hewan>::printSimpananMatrix() {
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