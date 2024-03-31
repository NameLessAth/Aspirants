#ifndef __HEWAN_H__
#define __HEWAN_H__

#include <string>
using namespace std;

class Hewan {
    private:
        int id;
        string kode;
        string nama;
        string tipe;
        int beratUntukPenan;
        int harga;
        int berat;
    public:
        Hewan();
        void makan();
};

#endif