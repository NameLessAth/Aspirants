#ifndef __PEMAIN_H__
#define __PEMAIN_H__

#include <string>
#include "Matrix.hpp"
#include "Simpanan.hpp"
using namespace std;

// Pemain
// Abstract Base Class
class Pemain {
    protected: 
        string username;
        int uang;
        int beratBadan;
        Matrix<Simpanan> penyimpanan;
        static int jumlahPemain;
        static int barisPenyimpanan;
        static int kolomPenyimpanan;
    public:
        Pemain();
        // void next();  
        // void makan();
        void printPenyimpanan();
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
        Matrix<Tanaman> ladang;
        static int jumlahPetani;
        static int barisLadang;
        static int kolomLadang;
    public:
        Petani();
        // void tanam();
        // void panen();
};  

// Peternak 
class Peternak : public Pemain {
    private:
        Matrix<Hewan> peternakan;
        static int jumlahPeternak;
        static int barisTernak;
        static int kolomTernak;
    public:
        Peternak();
        // void kasihMakan();
        // void ternak();
        // void panen();
};  

#endif 