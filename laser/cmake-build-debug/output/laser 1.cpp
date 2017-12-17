#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ofstream outputTotal("outputTotal.txt");
    for(int i=0; i<=19; i++){
        string name = "output" + to_string(i) + ".txt";
        ifstream output(name);
        int n;
        output>>n;
        outputTotal<<i<<", "<<n<<endl;
    }
}
