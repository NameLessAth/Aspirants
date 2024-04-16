#ifndef __PEMAIN_H__
#define __PEMAIN_H__

#include <string>
#include <vector>
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
        Pemain(string, int, int, Matrix<Simpanan>);
        // void next();  
        void makan();
        virtual void tumbal(){};
        // void beli();
        // void jual();
        int getUang();
        int getBerat();
        string getName();

};

class ListPemain {
    private:
        static vector<Pemain*> listPemain;
    public:
        static vector<Pemain*> getListPemain();
        static void setListPemain(vector<Pemain*>);
        static void pushPemain(Pemain*);
};

// Walikota
class Walikota : public Pemain {
    public:
        Walikota();
        Walikota(string, int, int, Matrix<Simpanan>);
        // void pungutPajak();
        // void bangunBangunan();
        // void tambahPemain();
        virtual void tumbal(){};
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
        Petani(string, int, int, Matrix<Simpanan>, Matrix<Tanaman>);
        void tanam();
        void panen();
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
        Peternak(string, int, int, Matrix<Simpanan>, Matrix<Hewan>);
        void kasihMakan();
        void ternak();
        void panen();
};

#endif 