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
    private:
        void printGaris();
    public :
        Matrix(int baris, int kolom);
        ~Matrix();
        int getBanyakIsi();
        void setValue(int baris, int kolom, T* value);
        void addNearby(T* value);
        const int getBaris();
        const int getKolom();
        T* getValue(int baris, int kolom);
        std::pair<int,int> extractSlot();
        void printSimpananMatrix();
        bool isEmpty();
        bool isFull();
        bool check(std::string kelas);
};

#endif