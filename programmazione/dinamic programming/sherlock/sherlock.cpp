#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>

using namespace std;

typedef vector<vector<int>> Mat;

void printMat(Mat& MAT){
    for(int i=0; i<MAT.size(); i++){
        for(int j=0; j<MAT[i].size(); j++){
            cout<<MAT[i][j]<<", ";
        }
        cout<<endl;
    }
    cout<<endl;
}

int guadagnoRec(string S, int i, int k, char c){
    if(k < 0){
        return -9999999;
    }
    if(i==S.size()){
        return 0;
    }

    if(S[i]==c){
        return 1 + guadagnoRec(S, i+1, k, S[i]);
    }
    else{
        return max(guadagnoRec(S, i+1, k, c), 1+guadagnoRec(S, i+1, k-1, S[i]));
    }
}

vector<int> stringToGuad(string S, int K){
    vector<int> guad(K+1, 0);
    char diff = (S[0]=='H') ? 'J' : 'H';
    for(int k=1; k<=K; k++){
        guad[k] = guadagnoRec(S, 0, k, '#');
    }
    return guad;
}

int knapsackRec(Mat& guadagni, int i, int C){
    if(i==guadagni.size()){
        return 0;
    }

	int best = 0;
    for(int c=0; c<=C; c++){
        int questo = guadagni[i][c];
        int resto = knapsackRec(guadagni, i+1, C-c);
        best = max(best, questo+resto);
        if(i==0){
            //cout<<"Questo: "<<questo<<", resto: "<<resto<<", best: "<<best<<endl;
        }
    }

    //cout<<"I: "<<i<<", C: "<<C<<", best: "<<best<<endl;
    return best;
}

int main(){
    cout<<"Scrivi seq: ";
    string test;
    test = "JH";
    //cin>>test;
    cout<<test<<endl;
    vector<int> guad = stringToGuad(test, 4);
    for(int c=0; c<guad.size(); c++)  cout<<guad[c]<<", "; cout<<endl<<endl;

    //Mat HJ = {succ(test).first, succ(test).second};   printMat(HJ);
    return 0;
    
    ifstream input("input.txt");
    int N; // serate
    int M; // lunghezza serata
    int T; // limite travestimenti
    input>>N>>M>>T;
    vector<string> serate;
    Mat guadagni;
    for(int i=0; i<N; i++){
        string a = ",";
        input>>a;
        serate.push_back(a);
        //cout<<a<<endl;
        vector<int> guad = stringToGuad(a, T);
        //for(int c=0; c<guad.size(); c++)  cout<<guad[c]<<", "; cout<<endl<<endl;
        guadagni.push_back(guad);
    }
    
    cout<<endl<<"Result: "<<knapsackRec(guadagni, 0, T)<<endl;

    return 0;
}