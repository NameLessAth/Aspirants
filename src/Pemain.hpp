#ifndef __PEMAIN_H__
#define __PEMAIN_H__

#include <string>
// #include "Matrix.hpp"
// #include "Tanaman.hpp"
// #include "Hewan.hpp"
using namespace std;

// Pemain
// Abstract Base Class
class Pemain {
    protected: 
        string username;
        int uang;
        int beratBadan;
        static int jumlahPemain;
    public:
        Pemain();
        // void next();  
        // void makan();
        // void cetakPenyimpanan();
        // void beli();
        // void jual();
};

// Walikota
class Walikota : public Pemain {
    public:
        Walikota();
        // void pungutPajak();
        // void bangunBangunan();
        // void tambahPemain();
};

// Petani
class Petani : public Pemain {
    private:
        // Matrix<Tanaman> ladang;
        static int jumlahPetani;
    public:
        Petani();
        // void tanam();
        // void panen();
};  

// Peternak 
class Peternak : public Pemain {
    private:
        // Matrix<Hewan> peternakan;
        static int jumlahPeternak;
    public:
        Peternak();
        // void kasihMakan();
        // void ternak();
        // void panen();
};  

#endif 