#include "Simpanan.hpp"
#include <iostream>
#include <vector>
#include <utility>

class Toko {
    private:
        static vector<pair<Simpanan*, int>> catalogue;
    public:
        static void insertItem(Simpanan* item, int quantity);
        static int manyItem();
        static vector<pair<Simpanan*, int>> getCatalogue();
        static void printToko();
};