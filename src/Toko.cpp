#include "Toko.hpp"

vector<pair<Simpanan, int>> Toko::catalogue;

void Toko::insertItem(Simpanan item, int quantity){
    bool found = false;
    for(int i=0;i<Toko::catalogue.size();i++){
        if(Toko::catalogue[i].first.getKode() == item.getKode()){
            found = true;
            if(dynamic_cast<Bangunan*>(&Toko::catalogue[i].first)){
                Toko::catalogue[i].second += quantity;
            }
            break;
        }
    }
    if(!found){
        Toko::catalogue.push_back(make_pair(item,quantity));
    }
}

void Toko::printToko(){
    cout << "Selamat datang di toko!!\nBerikut merupakan hal yang dapat Anda Beli\n";
    for(int i=0;i<Toko::catalogue.size();i++){
        cout << i+1 << ". " << Toko::catalogue[i].first.getNama() << " - " << Toko::catalogue[i].first.getHarga();
        Simpanan* temp = &(Toko::catalogue[i].first);
        if(dynamic_cast<Bangunan*>(temp)){
            cout << " (" << Toko::catalogue[i].second << ")";
        }
        cout << endl;
    }
}