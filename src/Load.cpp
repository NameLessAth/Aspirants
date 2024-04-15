#include "Load.hpp"
#define PB push_back

string Load::ADVWORD(FILE *file)
{
    char var; 
    int success = ADV(file, var); 
    string toberet = "";
    if (success != 1) return "habis";
    else{
        while (var != ' ' and var != '\n' and success == 1){
            toberet += var; 
            success = ADV(file, var);
        } return toberet;
    }
}

vector<Hewan> Load::loadAnimal(){
    FILE *file = fopen("../Config/config1/animal.txt", "r");
    
    if (file == NULL) throw FileNotFound();

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
    
    if (file == NULL) throw FileNotFound();

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

vector<int> Load::loadMisc(){
    FILE *file = fopen("../Config/config1/misc.txt", "r");

    if (file == NULL) throw FileNotFound();

    string tempvar = Load::ADVWORD(file); vector<int> temp;
    
    while(tempvar != "habis"){
        temp.PB(stoi(tempvar)); tempvar = Load::ADVWORD(file);
    } return temp;
}

vector<Produk> Load::loadProduct(){
    FILE *file = fopen("../Config/config1/product.txt", "r");
    
    if (file == NULL) throw FileNotFound();

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
    
    if (file == NULL) throw FileNotFound();

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
                Bangunan newBangunan(id, kode, nama, "PLACEHOLDER", harga, mats);
                newVec.PB(newBangunan);
                mats.clear();
                itr = 0;
            } tempvar = "";
        } else tempvar += var;
    } matqua = stoi(tempvar);
    mats[mat] = matqua;
    Bangunan newBangunan(id, kode, nama, "PLACEHOLDER", harga, mats);
    newVec.PB(newBangunan);
    return newVec;
}

vector<Pemain*> Load::loadState(string path){
    vector<Hewan> animalVec = Load::loadAnimal();
    vector<Tanaman> plantVec = Load::loadPlant();
    vector<Produk> prodVec = Load::loadProduct();
    vector<Bangunan> buildVec = Load::loadRecipe();
    FILE *file = fopen(path.c_str(), "r");

    if (file == NULL) throw FileNotFound();

    // word pertama jumlahPemain
    int jumlahPemain = stoi(Load::ADVWORD(file));

    // declare var
    string username, role, kode; int beratbadan, uang;
    vector<Pemain*> tempVec;


    FOR(i, jumlahPemain){
        // word pertama per pemain adalah username
        username = Load::ADVWORD(file);

        // word selanjutnya rolenya
        role = Load::ADVWORD(file);

        // bb dan uang
        beratbadan = stoi(Load::ADVWORD(file)); uang = stoi(Load::ADVWORD(file));

        


    }

}
