#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

double potenza(int V, int F, int M){

    double*** DP = new double**[V+1];
    int C = 2*V + F, c, m;
    double pot;

    for(int v=0; v<=V; v++){
        DP[v] = new double*[F+1];
        for(int f=0; f<=F; f++){
            DP[v][f] = new double[V-v+1];
            for(int vc=0; vc+v<=V; vc++){
                
                c = 2*v + vc + f;
                m = M - (C-c);
                if(m>0){
                    pot = 0;
                    if(v>0 && vc<V)  pot += DP[v-1][f][vc+1] * v/(v+vc+f);
                    if(vc>0) pot += DP[v][f][vc-1] * vc/(v+vc+f);
                    if(f>0)  pot += DP[v][f-1][vc] * f/(v+vc+f);
                    DP[v][f][vc] = pot;
                }
                else{
                    DP[v][f][vc] = (v+vc)*f;
                }
                
            }
            if(v>0 && f>0){
                delete[] DP[v-1][f-1];
            }
        }
        if(v > 0){
            delete[] DP[v-1];
        }
    }
    
    return DP[V][F][0];
}

int main(){

    ifstream input("input.txt");
    int V, F, M;
    input>>V>>F>>M;

    ofstream output("output.txt");
    double result = potenza(V, F, M);
    cout<<"Giusto: "<<result<<endl;
    output<<scientific<<setprecision(10)<<result<<endl;



    return 0;
}


