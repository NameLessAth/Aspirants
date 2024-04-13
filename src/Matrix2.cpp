#include "Matrix2.hpp"
#include "Simpanan.hpp"
using namespace std;

template<class T>
Matrix<T>::Matrix(int baris, int kolom): baris(baris), kolom(kolom) {
    this->matrix.resize(this->baris, std::vector<T>(this->kolom));
    this->banyakIsi = 0;
}

template<class T>
void Matrix<T>::setValue(int baris, int kolom, T& value) {
    if (baris >= 1 && baris <= this->baris && kolom >= 1 && kolom <= this->kolom) {
        this->matrix[baris - 1][kolom - 1] = value;
        this->banyakIsi++;
    } else {
        cerr << "Index out of bounds!" << endl; // Nanti diubah jadi throw error
    }
}

template<class T>
T& Matrix<T>::getValue(int baris, int kolom) {
    if (baris >= 1 && baris <= this->baris && kolom >= 1 && kolom <= this->kolom) {
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
            if (this->matrix[i][j].getKode() != "XXXX") {
                cout << this->matrix[i][j].getKode();
                cout << "  |";
            } else {
                cout << "     |";
            }
        }
        cout << endl;
        this->printGaris();
    }
}