#ifndef __SIMPANAN_H__
#define __SIMPANAN_H__

#include <string>
#include <map>
using namespace std;

// Parent class Simpanan, sehingga semua item child dapat 
// disimpan di penyimpanan

// Simpanan
class Simpanan {
    protected:
        int id;
        string kode;
        string name;
        string tipe;
    public:
        Simpanan();
        virtual ~Simpanan();
        Simpanan(int id, string kode, string name, string tipe);
        string getKode();
        string getIsi();
        string getNama();
};

// Bangunan
class Bangunan : public Simpanan {
    protected:
        map<string, int> material;
    public: 
        Bangunan(int id, string kode, string name, string tipe, map<string, int> material);
        map<string, int> getMats();
};

// Item
class Item : public Simpanan {
    protected:
        int harga;
    public:
        Item();
        Item(int id, string kode, string name, string tipe, int harga);
        int getHarga();
};

// Hewan
class Hewan : public Item {
    private:
        int beratUntukPanen;
        int berat;
    public:
        Hewan();
        Hewan(int id, string kode, string name, string tipe, int harga, int beratUntukPanen, int berat);
        // void makan();
};

// Tanaman
class Tanaman : public Item {
    private:
        int umurUntukPanen;
        int umur;
    public:
        Tanaman();
        Tanaman(int id, string kode, string name, string tipe, int harga, int umurUntukPanen, int umur);
        void tambahUmur();
};

// Produk
class Produk : public Item {
    private:
        string origin;
        int beratTambahan;
    public:
        Produk(int id, string kode, string name, string tipe, int harga, string origin, int beratTambahan);
};

#endif 