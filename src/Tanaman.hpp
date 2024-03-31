#ifndef __TANAMAN_H__
#define __TANAMAN_H__

#include <string>
using namespace std;

class Tanaman {
    private:
        int id;
        string kode;
        string nama;
        string tipe;
        int umurUntukPanen;
        int harga;
        int umur;
    public:
        Tanaman();
        void tambahUmur();
};


#endif