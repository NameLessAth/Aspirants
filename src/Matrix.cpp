#include "Matrix.hpp"
#include "Simpanan.hpp"
#include <iostream>
using namespace std;

template<class T>
Matrix<T>::Matrix(int baris, int kolom) : baris(baris), kolom(kolom) {
    matrix = new T*[baris];
    for (int i = 0; i < baris; ++i) {
        matrix[i] = new T[kolom];
        for (int j = 0; j < kolom; ++j) {
            matrix[i][j] = T();
        }
    }
}

template<class T>
Matrix<T>::~Matrix() {
    for (int i = 0; i < baris; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

template<class T>
void Matrix<T>::setValue(int row, int col, T value) {
    if (row >= 1 && row <= baris && col >= 1 && col <= kolom) {
        matrix[row - 1][col - 1] = value;
    } else {
        cerr << "Index out of bounds!" << endl;
    }
}

template<class T>
void Matrix<T>::printMatrix() {
    cout << "\t";
    for (int i = 0; i < kolom; i++) {
        cout << char('A' + i) << "\t";
    }
    cout << endl;
    cout << "\t+-------+-------+-------+-------+-------+" << endl;
    for (int i = 0; i < baris; i++) {
        cout << i+1 << "\t|";
        for (int j = 0; j < kolom; j++) {
            cout << "  ";
            if (matrix[i][j] != T()) {
                cout << matrix[i][j];
            } else {
                cout << "";
            }
            cout << "\t|";
        }
        cout << endl;
        cout << "\t+-------+-------+-------+-------+-------+" << endl;
    }
}

template<>
void Matrix<Simpanan>::printMatrix() {
    cout << "\t";
    for (int i = 0; i < kolom; i++) {
        cout << char('A' + i) << "\t";
    }
    cout << endl;
    cout << "\t+-------+-------+-------+-------+-------+" << endl;
    for (int i = 0; i < baris; i++) {
        cout << i+1 << "\t|";
        for (int j = 0; j < kolom; j++) {
            cout << "  ";
            if (matrix[i][j].getKode() != "XXXX") {
                cout << matrix[i][j].getKode();
            } else {
                cout << "";
            }
            cout << "\t|";
        }
        cout << endl;
        cout << "\t+-------+-------+-------+-------+-------+" << endl;
    }
}

template class Matrix<int>;
template class Matrix<Simpanan>;