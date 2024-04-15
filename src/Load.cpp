#include "Load.hpp"
#define PB push_back

string Load::ADVWORD(FILE *file)
{
    char var; 
    int success = ADV(file, var); 
    string toberet = "";
    if (success != 1) return "habis";
    else{
        while (var != ' ' && var != '\n' && success == 1){
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
    vector<Pemain*> playerVec; 

    FOR(i, jumlahPemain){
        // word pertama per pemain adalah username
        username = Load::ADVWORD(file);

        // word selanjutnya rolenya
        role = Load::ADVWORD(file);

        // bb dan uang
        beratbadan = stoi(Load::ADVWORD(file)); uang = stoi(Load::ADVWORD(file));

        // jumlah item
        int itemCount = stoi(Load::ADVWORD(file));  Matrix<Simpanan> invVec(69, 69);
        // scan item2
        FOR(j, itemCount){
            string item = Load::ADVWORD(file);
            bool ketemu = false;
            int itr = 0;
            while (!ketemu && itr <= animalVec.size()+plantVec.size()+prodVec.size()+buildVec.size()){
                if (itr >= 0 && itr <= animalVec.size()-1){
                    if (item == animalVec[itr].getNama()){
                        ketemu = true;
                        Hewan* tempvar = new Hewan(animalVec[itr]);
                        invVec.addNearby(tempvar);
                    } else itr++;
                } else if (itr >= animalVec.size() && itr <= animalVec.size()+plantVec.size()-1){
                    if (item == plantVec[itr-animalVec.size()].getNama()){
                        ketemu = true;
                        Tanaman* tempvar = new Tanaman(plantVec[itr-animalVec.size()]);
                        invVec.addNearby(tempvar);
                    } else itr++;
                } else if (itr >= animalVec.size()+plantVec.size() && itr <= animalVec.size()+plantVec.size()+prodVec.size()-1){
                    if (item == prodVec[itr-animalVec.size()-plantVec.size()].getNama()){
                        ketemu = true;
                        Produk* tempvar = new Produk(prodVec[itr-animalVec.size()-plantVec.size()]);
                        invVec.addNearby(tempvar);
                    } else itr++;
                } else {
                    if (item == buildVec[itr-animalVec.size()-plantVec.size()-prodVec.size()].getNama()){
                        ketemu = true;
                        Bangunan* tempvar = new Bangunan(buildVec[itr-animalVec.size()-plantVec.size()-prodVec.size()]);
                        invVec.addNearby(tempvar);
                    } else itr++;
                }
            }
        } 

        //  scan untuk petani dan peternak
        if (role == "Petani"){
            itemCount = stoi(Load::ADVWORD(file));

            // var
            Matrix<Tanaman> plantMatx(69, 69);
            string lokasi, x = "", y = "", item; int xval = 0, yval, itr, age;
            bool ketemu;


            FOR(j, itemCount){

                // scan lokasi
                lokasi = Load::ADVWORD(file);
                for(char& c : lokasi){
                    if (!isdigit(c)) x += c;
                    else y += c;
                } for(char& c : x){
                    xval += int(c);
                } xval -= (int('A')-1);
                yval = stoi(y);
                
                // scan nama tanaman
                item = Load::ADVWORD(file);

                // cari nama di database
                ketemu = false; itr = 0;
                while(!ketemu){
                    if (plantVec[itr].getNama() == item){
                        ketemu = true;
                        age = stoi(Load::ADVWORD(file));
                        Tanaman* temp = new Tanaman(plantVec[itr]);
                        temp->setUmur(age);
                        plantMatx.setValue(xval, yval, temp);
                    } else itr++;
                }
            } Petani* tempvar = new Petani(username, uang, beratbadan, invVec, plantMatx);
            playerVec.push_back(tempvar);
        } else if (role == "Peternak"){
            itemCount = stoi(Load::ADVWORD(file));

            // var
            Matrix<Hewan> animalMatx(69, 69);
            string lokasi, x = "", y = "", item; int xval = 0, yval, itr, bobot;
            bool ketemu;

            FOR(j, itemCount){

                // scan lokasi
                lokasi = Load::ADVWORD(file);
                for(char& c : lokasi){
                    if (!isdigit(c)) x += c;
                    else y += c;
                } for(char& c : x){
                    xval += int(c);
                } xval -= (int('A')-1);
                yval = stoi(y);
                
                // scan nama hewan
                item = Load::ADVWORD(file);

                // cari nama di database
                ketemu = false; itr = 0;
                while(!ketemu){
                    if (animalVec[itr].getNama() == item){
                        ketemu = true;
                        bobot = stoi(Load::ADVWORD(file));
                        Hewan* temp = new Hewan(animalVec[itr]);
                        temp->setBerat(bobot);
                        animalMatx.setValue(xval, yval, temp);
                    } else itr++;
                }
            } Peternak* tempvar = new Peternak(username, uang, beratbadan, invVec, animalMatx);
            playerVec.push_back(tempvar);
        } else{
            Walikota* tempvar = new Walikota(username, uang, beratbadan, invVec);
            playerVec.push_back(tempvar);
        }
    } return playerVec;
}
