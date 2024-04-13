#ifndef __MATRIX2_H__
#define __MATRIX2_H__

#include <iostream>
#include <vector>

template<class T>
class Matrix {
    private:
        const int baris;
        const int kolom;
        int banyakIsi;
        std::vector<std::vector<T>> matrix;
    public :
        Matrix(int baris, int kolom);
        ~Matrix();
        void setValue(int baris, int kolom, T& value);
        T& getValue(int baris, int kolom);
        void printGaris();
        void printSimpananMatrix();
};

#endif