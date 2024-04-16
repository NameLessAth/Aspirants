#include "Toko.hpp"

map<Simpanan, int> Toko::catalogue;

void Toko::insertItem(Simpanan item, int quantity){
    Toko::catalogue[item] += quantity;
}

void Toko::printToko(){
    cout << "Selamat datang di toko!!\nBerikut merupakan hal yang dapat Anda Beli\n";
    int i=1;
    map<Simpanan, int>::iterator it = Toko::catalogue.begin();
 
    // Print map catalogue
    while (it != Toko::catalogue.end()) {
        Simpanan temp = it->first;
        cout << i << ". " << temp.getNama() << " - " << temp.getHarga();
        if(dynamic_cast<Bangunan*>(&temp)){
            cout << " (" << it->second << ")";
        }
        cout << endl;
        it++;
        i++;
    }
}
