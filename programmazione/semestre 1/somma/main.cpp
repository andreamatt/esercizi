#include <iostream>
#include <fstream>

using namespace std;

void somma();

int main() {

    somma();

    return 0;
}

void somma(){
    int a, b;
    ifstream inputs("input.txt");
    inputs>>a;
    inputs>>b;
    ofstream output("output.txt");
    output<<(a+b);
}