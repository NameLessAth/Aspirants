#ifndef __MATRIX_H__
#define __MATRIX_H__
#include "Exception.hpp"
#include <string>
#include <utility>

template <class T>
class Matrix {  
    private: 
        const int baris;
        const int kolom;
        int banyakIsi;
        T* ** matrix;
    public :
        Matrix(int baris, int kolom);
        ~Matrix();
        void setValue(int baris, int kolom, T* value);
        int getBaris(){return this->baris}
        int getKolom(){return this->kolom}
        T* getValue(int baris, int kolom);
        std::pair<int,int> extractSlot();
        void printGaris();
        void printSimpananMatrix();
        bool isEmpty();
        bool check(std::string kelas);
};

#endif