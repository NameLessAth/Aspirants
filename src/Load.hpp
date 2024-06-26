#ifndef __LOAD_H__
#define __LOAD_H__

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "Pemain.hpp"
#include "Simpanan.hpp"
#include <filesystem>
using namespace std;
#define PB push_back
#define ADV(arg1, arg2) fscanf(arg1, "%c", &arg2)
#define FOR(i, a) for (int i = 0; i < a; i++)

class Load{
    public:
        static string ADVWORD(FILE*);
        static vector<Hewan> loadAnimal();
        static vector<Tanaman> loadPlant();
        static vector<int> loadMisc();
        static vector<Produk> loadProduct();
        static vector<Bangunan> loadRecipe();
        static void loadState(string path);
};

class Save{
    public:
        static void saveState(string path, vector<Pemain*> playerVec);
};

#endif