#ifndef __MATRIX_H__
#define __MATRIX_H__

template <class T>
class Matrix {
    private: 
        int baris;
        int kolom;
        T **matrix;
    public :
        Matrix();
        ~Matrix();
};

#endif 