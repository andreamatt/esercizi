#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

double potenza(int V, int Vc, int F, int M, double**** DP){
    if(M==0){
        return (V+Vc)*F;
    }

    if(DP[V][Vc][F][M] == -1){
        double potenz = 0;
        if(V>0)  potenz += potenza(V-1, Vc+1, F, M-1, DP) * V/(V+Vc+F);
        if(Vc>0) potenz += potenza(V, Vc-1, F, M-1, DP) * Vc/(V+Vc+F);
        if(F>0)  potenz += potenza(V, Vc, F-1, M-1, DP) * F/(V+Vc+F);
        DP[V][Vc][F][M] = potenz;
    }

    return DP[V][Vc][F][M];
}


int main(){

    ifstream input("input.txt");
    int V, F, M;
    input>>V>>F>>M;

    double**** DP = new double***[V+1];
    for(int v=0; v<=V; v++){
        DP[v] = new double**[V+1];
        for(int vc=0; vc<=V; vc++){
            DP[v][vc] = new double*[F+1];
            for(int f=0; f<=F; f++){
                DP[v][vc][f] = new double[M+1];
                for(int m=0; m<=M; m++){
                    DP[v][vc][f][m] = -1;
                }
            }
        }
    }


    ofstream output("output.txt");
    double result = potenza(V, 0, F, M, DP);
    cout<<result<<endl;
    output<<scientific<<setprecision(10)<<result<<endl;




    return 0;
}