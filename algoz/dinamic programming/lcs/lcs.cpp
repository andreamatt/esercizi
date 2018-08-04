#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int lcsRec(string &a, string &b, int i, int j, int **DP){
    if(i==-1 || j==-1){
        return 0;
    }

    if(DP[i][j] == -1){
        if(a[i] == b[j]){
            DP[i][j] = 1 + lcsRec(a, b, i-1, j-1, DP);
        }
        else{
            DP[i][j] = max(lcsRec(a, b, i, j-1, DP), lcsRec(a, b, i-1, j, DP));
        }
    }

    return DP[i][j];
}

int lcs(string a, string b){
    int **DP = new int*[a.length()];
    for(int i=0; i<a.length(); i++){
        DP[i] = new int[b.length()];
        for(int j=0; j<b.length(); j++){
            DP[i][j] = -1;
        }
    }

    return lcsRec(a, b, a.length()-1, b.length()-1, DP);
}

int main(){

    ifstream input("input.txt");
    string a, b;
    input>>a>>b;
    cout<<a<<endl<<b<<endl;
    int len = lcs(a, b);
    cout<<len<<endl;

    ofstream output("output.txt");
    output<<len;

    return 0;
}