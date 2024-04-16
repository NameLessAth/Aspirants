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
        int harga;
        string kode;
        string name;
        string tipe;
    public:
        Simpanan();
        virtual ~Simpanan();
        Simpanan(int id, string kode, string name, string tipe, int harga);
        string getKode();
        string getIsi();
        string getNama() const;
        int getHarga() const;
        bool operator<(const Simpanan& other) const {
            return name < other.name;
        }
};

// Bangunan
class Bangunan : public Simpanan {
    protected:
        map<string, int> material;
    public: 
        Bangunan();
        Bangunan(int id, string kode, string name, string tipe, int harga, map<string, int> material);
        map<string, int> getMats();
        void setTipe(string tipe);
};

// Hewan
class Hewan : public Simpanan {
    private:
        int beratUntukPanen;
        int berat;
    public:
        Hewan();
        Hewan(int id, string kode, string name, string tipe, int harga, int beratUntukPanen, int berat);
        // void makan();
        void setBerat(int berat);
        void tambahBerat(int beratTambahan);
        int getBerat();
};

// Tanaman
class Tanaman : public Simpanan {
    private:
        int umurUntukPanen;
        int umur;
    public:
        Tanaman();
        Tanaman(int id, string kode, string name, string tipe, int harga, int umurUntukPanen, int umur);
        void setUmur(int umur);
        void tambahUmur();
};

// Produk
class Produk : public Simpanan {
    private:
        string origin;
        int beratTambahan;
    public:
        Produk();
        Produk(int id, string kode, string name, string tipe, int harga, string origin, int beratTambahan);
        int getBeratTambahan();
};

#endif 