#include <iostream>
#include "Tree.h"
#include <random>
using namespace std;

int main() {
    int seed = 20;
    srand(seed);
    Tree* tree = new Tree(10);

    tree->insertBRT(6);
    tree->insertBRT(15);
    tree->insertBRT(4);
    tree->insertBRT(8);
    tree->insertBRT(12);
    tree->insertBRT(18);




    return 0;
}