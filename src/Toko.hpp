#include "Simpanan.hpp"
#include <iostream>
#include <map>
#include <utility>

class Toko {
    private:
        map<string, pair<int, int>> items;

    public:
        Toko();
        void insertItem(Simpanan* item, int quantity);
        void printToko();        
};