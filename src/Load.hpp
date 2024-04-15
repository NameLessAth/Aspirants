#ifndef __LOAD_H__
#define __LOAD_H__

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "Simpanan.hpp"
#include "Exception.hpp"
using namespace std;

class Load{
    public:
        static vector<Hewan> loadAnimal();
        static vector<Tanaman> loadPlant();
        static vector<Item> loadMisc();
        static vector<Produk> loadProduct();
        static vector<Bangunan> loadRecipe();
};

#endif