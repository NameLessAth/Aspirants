#ifndef __ITEM_H__
#define __ITEM_H__

#include <string>
using namespace std;

class Item {
    protected:
        int id;
        string kode;
        string name;
        string tipe;
        int harga;
};

class Hewan : public Item {
    private:
        int beratUntukPanen;
        int berat;
    public:
        Hewan();
        void makan();
};

class Tanaman : public Item {
    private:
        int umurUntukPanen;
        int harga;
        int umur;
    public:
        Tanaman();
        void tambahUmur();
};

class Produk : public Item {
    private:
        string origin;
        int beratTambahan;
    public:
        Produk();
};

#endif 