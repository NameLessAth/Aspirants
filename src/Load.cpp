#include "Load.hpp"
#define PB push_back

vector<Hewan> Load::loadAnimal(){
    FILE *file = fopen("../Config/config1/animal.txt", "r");
    
    if (file == NULL) cerr << "read error\n";

    string tempvar = ""; char var; int itr = 0;
    int id, beratpanen, harga; string kode, nama, tipe;
    vector<Hewan> newVec;
    while(fscanf(file, "%c", &var) == 1){
        if ((var == ' ') || (var == '\n')){
            switch (itr%6){
                case 0:
                    id = stoi(tempvar); break;
                case 1:
                    kode = tempvar; break;
                case 2:
                    nama = tempvar; break;
                case 3:
                    tipe = tempvar; break;
                case 4:
                    beratpanen = stoi(tempvar); break;
                case 5:
                    harga = stoi(tempvar);
                    Hewan newAnimal(id, kode, nama, tipe, harga, beratpanen, 69);
                    newVec.PB(newAnimal);
                    break;
            } tempvar = "";
            itr++;
        } else tempvar += var;
    } harga = stoi(tempvar);
    Hewan newAnimal(id, kode, nama, tipe, harga, beratpanen, 0);
    newVec.PB(newAnimal);    
    return newVec;
}

vector<Tanaman> Load::loadPlant(){
    FILE *file = fopen("../Config/config1/plant.txt", "r");
    
    if (file == NULL) cerr << "read error\n";

    string tempvar = ""; char var; int itr = 0;
    int id, umurpanen, harga; string kode, nama, tipe;
    vector<Tanaman> newVec;
    while(fscanf(file, "%c", &var) == 1){
        if ((var == ' ') || (var == '\n')){
            switch (itr%6){
                case 0:
                    id = stoi(tempvar); break;
                case 1:
                    kode = tempvar; break;
                case 2:
                    nama = tempvar; break;
                case 3:
                    tipe = tempvar; break;
                case 4:
                    umurpanen = stoi(tempvar); break;
                case 5:
                    harga = stoi(tempvar);
                    Tanaman newPlant(id, kode, nama, tipe, harga, umurpanen, 69);
                    newVec.PB(newPlant);
                    break;
            } tempvar = "";
            itr++;
        } else tempvar += var;
    } harga = stoi(tempvar);
    Tanaman newPlant(id, kode, nama, tipe, harga, umurpanen, 0);
    newVec.PB(newPlant);    
    return newVec;
}

vector<Produk> Load::loadProduct(){
    FILE *file = fopen("../Config/config1/product.txt", "r");
    
    if (file == NULL) cerr << "read error\n";

    string tempvar = ""; char var; int itr = 0;
    int id, beratTambahan, harga; string kode, nama, tipe, origin;
    vector<Produk> newVec;
    while(fscanf(file, "%c", &var) == 1){
        if ((var == ' ') || (var == '\n')){
            switch (itr%7){
                case 0:
                    id = stoi(tempvar); break;
                case 1:
                    kode = tempvar; break;
                case 2:
                    nama = tempvar; break;
                case 3:
                    tipe = tempvar; break;
                case 4:
                    origin = tempvar; break;
                case 5:
                    beratTambahan = stoi(tempvar); break;
                case 6:
                    harga = stoi(tempvar);
                    Produk newProduk(id, kode, nama, tipe, harga, origin, beratTambahan);
                    newVec.PB(newProduk);
                    break;
            } tempvar = "";
            itr++;
        } else tempvar += var;
    } harga = stoi(tempvar);
    Produk newProduk(id, kode, nama, tipe, harga, origin, beratTambahan);
    newVec.PB(newProduk);
    return newVec;
}

vector<Bangunan> Load::loadRecipe(){
    FILE *file = fopen("../Config/config1/recipe.txt", "r");
    
    if (file == NULL) cerr << "read error\n";

    string tempvar = ""; char var; int itr = 0;
    int id, matqua, harga; string kode, nama, tipe, mat;
    vector<Bangunan> newVec; map<string, int> mats;
    while(fscanf(file, "%c", &var) == 1){
        if ((var == ' ') || (var == '\n')){
            switch (itr){
                case 0:
                    id = stoi(tempvar); break;
                case 1:
                    kode = tempvar; break;
                case 2:
                    nama = tempvar; break;
                case 3:
                    harga = stoi(tempvar); break;
                default:
                    if (itr%2 == 0) mat = tempvar;
                    else{
                        matqua = stoi(tempvar);
                        mats[mat] = matqua;
                    } break;
            } if (var == ' ') itr++;
            else {
                Bangunan newBangunan(id, kode, nama, "tipe", mats);
                newVec.PB(newBangunan);
                mats.clear();
                itr = 0;
            } tempvar = "";
        } else tempvar += var;
    } matqua = stoi(tempvar);
    mats[mat] = matqua;
    Bangunan newBangunan(id, kode, nama, "tipe", mats);
    newVec.PB(newBangunan);
    return newVec;
}
