#ifndef __MATRIX_H__
#define __MATRIX_H__

template <class T>
class Matrix {
    private: 
        const int baris;
        const int kolom;
        T ** matrix;
    public :
        Matrix(int baris, int kolom);
        ~Matrix();
        void setValue(int baris, int kolom, T value);
        void printMatrix();
};

#endif 