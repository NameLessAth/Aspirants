#ifndef __ITEM_H__
#define __ITEM_H__

#include <string>
using namespace std;

// Parent class Simpanan, sehingga semua item child dapat 
// disimpan di penyimpanan
class Simpanan {
    protected:
        int id;
        string name;
        string tipe;
};

class Bangunan : public Simpanan {
    public: 
        Bangunan();
};

class Item : public Simpanan {
    protected:
        string kode;
        string name;
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