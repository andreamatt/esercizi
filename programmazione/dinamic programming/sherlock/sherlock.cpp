#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>

using namespace std;

pair<vector<int>,vector<int>> succ(string S){
    vector<int> H(S.size());
    vector<int> J(S.size());
    int h=-1;
    int j=-1;

    for(int i=0; i<S.size(); i++){
        H[i] = h;
        J[i] = j;
        if(S[i] == 'H'){
            h = i;
        }
        else{
            j = i;
        }
    }
    return {H, J};
}

int guadagnoRec(string &S, int i, char prec, int c, int** DP, vector<int>& H, vector<int>& J){
    // casi estremi
    if(c < 0){
        return -1;
    }
    if(i < 0){
        return 0;
    }

    // se non calcolato
    //cout<<"Before: DP["<<i<<"]["<<c<<"] = "<<DP[i][c]<<endl;
    if(DP[i][c] == -1){
        // se uguale al prec:
        if(S[i] == prec){
            DP[i][c] = 1 + guadagnoRec(S, i-1, prec, c, DP, H, J);
        }

        // se diverso:
        else{
            // non lo prendo => salto
            int salto = (prec=='H') ? H[i] : J[i];
            int notTaken = guadagnoRec(S, salto, prec, c, DP, H, J);

            // lo prendo => meno capacità
            int taken = 1 + guadagnoRec(S, i-1, S[i], c-1, DP, H, J);

            DP[i][c] = max(taken, notTaken);
        }
    }
    //cout<<"After:  DP["<<i<<"]["<<c<<"] = "<<DP[i][c]<<endl;

    return DP[i][c];
}

int guadagno(string S, int C, int** DP){
    pair<vector<int>, vector<int>> HJ = succ(S);

    //char prec = (S.back() == 'J') ? 'H' : 'J';
    char last = S.back();
    return 1 + guadagnoRec(S, S.size()-2, last, C-1, DP, HJ.first, HJ.second);
}

vector<int> stringToGuad(string S, int C){
    int** DP = new int*[S.size()];
    for(int i=0; i<S.size(); i++){
        DP[i] = new int[C+1];
        for(int c=0; c<C+1; c++){
            DP[i][c] = -1;
        }
    }
    
    vector<int> result(C+1);
    // chiamo funzione guadagno
    for(int c=0; c<=C; c++){
        result[c] = guadagno(S, c, DP);
    }

    for(int i=0; i<S.size(); i++){
        delete[] DP[i];
    }
    delete[] DP;

    return result;
}

int knapsackRec(vector<vector<int>>& guadagni, int i, int C){
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
    
    string test = "JHJ";
    cout<<test<<endl;
    vector<int> guad = stringToGuad(test, 4);
    for(int c=0; c<guad.size(); c++)  cout<<guad[c]<<", "; cout<<endl<<endl;
    return 0;
    
    ifstream input("input.txt");
    int N; // serate
    int M; // lunghezza serata
    int T; // limite travestimenti
    input>>N>>M>>T;
    vector<string> serate;
    vector<vector<int>> guadagni;
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