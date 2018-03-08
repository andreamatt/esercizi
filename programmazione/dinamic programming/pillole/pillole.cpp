#include <vector>
#include <iostream>
#include <fstream>

using namespace std;



int main(){

    ifstream input("input.txt");
    int N;
    input>>N;

    pillole(N);

    return 0;
}