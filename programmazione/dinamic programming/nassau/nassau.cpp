#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

clock_t t1;

int gcd(int a, int b){
    return (b==0) ? a : gcd(b, a%b);
}

double*   createDP1(int N){
    double* DP1 = new double[N+1];
    for(int n=0; n<=N; n++) DP1[n] = -1;
    return DP1;
}

double**  createDP2(int N, int M){
    double** DP2 = new double*[N+1];
    for(int n=0; n<=N; n++) DP2[n] = createDP1(M);
    return DP2;
}

double*** createDP3(int N, int M, int O){
    double*** DP = new double**[N+1];
    for(int n=0; n<=N; n++) DP[n] = createDP2(M, O);
    return DP;
}

double potenza2(int V, int F, int M, double** DP){
    if(V==0 || F==0) return 0;
    if(M==0) return V*F;
    if(DP[V][F] == -1){
        double result = 0;
        result += potenza2(V-1, F, M-1, DP) * V/(V + F);
        result += potenza2(V, F-1, M-1, DP) * F/(V + F);
        DP[V][F] = result;
    }
    return DP[V][F];
}

double potenza2GCD(int V, int F, int M, double** DP){
    if(V==0 || F==0) return 0;
    if(M==0) return V*F;
    if(DP[V][F] == -1){
        double result = 0;
        clock_t t1_b = t1;
        int GCD = gcd(V, F);
        t1 = t1_b;
        if(GCD==1){
            result += potenza2GCD(V-1, F, M-1, DP) * V/(V + F);
            result += potenza2GCD(V, F-1, M-1, DP) * F/(V + F);
        }
        else{
            int V_r = V/GCD, F_r = F/GCD;
            result += GCD*GCD * potenza2GCD(V_r, F_r, M/GCD, DP);
        }
        DP[V][F] = result;
    }
    return DP[V][F];
}


int main(){

    ifstream input("input.txt");
    int V, F, M;
    input>>V>>F>>M;

    
    t1 = clock();
    ofstream output("output.txt");
    double result = potenza2(V, F, M, createDP2(V, F));
    cout<<result<<endl;
    output<<scientific<<setprecision(10)<<result<<endl;
    //cout<<clock()-t1<<endl;

    t1 = clock();
    double result2 = potenza2GCD(V, F, M, createDP2(V, F));
    cout<<result2<<endl;
    output<<scientific<<setprecision(10)<<result2<<endl;
    //cout<<clock()-t1<<endl;




    return 0;
}