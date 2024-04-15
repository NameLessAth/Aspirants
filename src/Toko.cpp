#include "Toko.hpp"

Toko::Toko() {}

void Toko::insertItem(Simpanan* item, int quantity) {
    items[item->getNama()] = make_pair(item->getHarga(), quantity);
}

void Toko::printToko() {
    int i = 1;
    for (auto const& [kode, info] : items) {
        cout << i++ << ". " << kode << " - " << info.first << " (" << info.second << ")" << endl;
    }
}        