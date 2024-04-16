#include "Simpanan.hpp"
#include <iostream>
#include <map>
#include <utility>

class Toko {
    private:
        static map<Simpanan*, int> catalogue;
    public:
        void insertItem(Simpanan item, int quantity);
        void printToko();
};