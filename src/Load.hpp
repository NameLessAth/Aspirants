#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Simpanan.hpp"
#include <vector>
using namespace std;

class Load{
    public:
        static vector<Hewan> loadAnimal();
        static vector<Tanaman> loadPlant();
        static vector<Item> loadMisc();
        static vector<Produk> loadProduct();
        static vector<Bangunan> loadRecipe();
};