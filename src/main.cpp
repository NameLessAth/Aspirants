#include "Game.hpp"
#include "Pemain.hpp"
#include "Matrix.hpp"
#include "Simpanan.hpp"
#include <iostream>
using namespace std;

// int main() {

//     // Game game;
//     // int i = 0;
//     // while (i < 10) {
//     //     game.next();
//     //     cout << game.getCurrentPemain() << endl;
//     //     i++;
//     // }

// }

// Testing Simpanan
int main() {

    Petani petani1;

    // Simpanan s(1, "S01", "Simpanan 1", "Simpanan");
    // Bangunan b(1, "B01", "Bangunan 1", "Bangunan");
    // Item i(1, "I01", "Item 1", "Item", 10000);
    // Hewan h(1, "H01", "Hewan 1", "Hewan", 10000, 50, 20);
    Tanaman t1(1, "T01", "Tanaman 1", "Tanaman", 10000, 10, 2);
    Tanaman t2(1, "T01", "Tanaman 1", "Tanaman", 10000, 10, 2);
    // Tanaman t3(1, "T02", "Tanaman 2", "Tanaman", 10000, 10, 2);
    // Tanaman t4(1, "T02", "Tanaman 2", "Tanaman", 10000, 10, 2);
    Produk p(1, "P01", "Produk 1", "Produk", 10000, "Indonesia", 10);


    petani1.penyimpanan.setValue(2,1,&p);
    petani1.penyimpanan.setValue(2,2,&t1);
    // petani1.printPenyimpanan();
    petani1.makan();
    petani1.tanam();
    // Matrix<Simpanan> m(2,2);
    // m.setValue(1,1,&t1);
    // m.setValue(1,2,&p);
    // m.setValue(2,1,&t3);
    // m.setValue(2,2,&t4);
    // m.setValue(2,1,b);
    // m.setValue(3,2,&i);
    // m.setValue(4,1,&h);
    // m.setValue(2,5,&t);
    // m.setValue(5,3,&p);
    // m.printSimpananMatrix();
    // Simpanan *a = m.getValue(1,1);
    // Item* b = dynamic_cast<Item*>(m.getValue(3,2));
    // cout << b->getHarga();
    // simpanan = a, item = b
    // cout << c.getIsi() << c.getHarga() << endl;
    // m.getValue(3,2);
    // m.getValue(4,1);
    // m.getValue(2,5);
    // m.getValue(5,3);
};