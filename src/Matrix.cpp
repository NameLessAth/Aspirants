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
    for (int i = 1; i <= kolom; ++i) {
        cout << char('A' + i - 1) << "\t";
    }
    cout << endl;
    cout << "\t+-------+-------+-------+-------+-------+" << endl;
    for (int i = 1; i <= baris; ++i) {
        if (i < 10) cout << " ";
        cout << i << "\t|";
        for (int j = 1; j <= kolom; ++j) {
            cout << "   ";
            if (matrix[i - 1][j - 1] != T()) {
                cout << matrix[i - 1][j - 1];
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