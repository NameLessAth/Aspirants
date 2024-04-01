#include "Game.hpp"
#include "Matrix.hpp"
#include <iostream>
using namespace std;

int main() {
    Matrix<int> m(5,5);
    m.setValue(1,1,3);
    m.setValue(2,2,3);
    m.printMatrix();
};