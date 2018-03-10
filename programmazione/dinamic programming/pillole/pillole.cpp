#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

typedef long long int lint;

lint pilloleRec(int i, int m, lint** DP){
    if(i == 0){
        return 1;
    }

    if(DP[i][m] == -1){
        DP[i][m] = 0;
        if(i > 0){
            DP[i][m] += pilloleRec(i-1, m+1, DP);
        }
        if(m > 0){
            DP[i][m] += pilloleRec(i, m-1, DP);
        }
    }

    return DP[i][m];
}

lint pillole(int P){
    lint** DP = new lint*[P+1];
    for(int i=0; i<=P; i++){
        DP[i] = new lint[ P*2 +1 ];
        for(int m=0; m<=P*2; m++){
            DP[i][m] = -1;
        }
    }

    return pilloleRec(P, 0, DP);
}

lint pilloleIter(int P){
    vector<lint> prec(P*2 +1, 1);
    vector<lint> curr(P*2 +1, 0);

    for(int i=1; i<=P; i++){
        curr[0] = prec[1];
        for(int m=1; m < P*2; m++){
            curr[m] = curr[m-1] + prec[m+1];
        }
        curr[P*2] = 1;

        for(int m=0; m<= P*2; m++){
            prec[m] = curr[m];
            //cout<<curr[m]<<", ";
            curr[m] = 0;
        }
        //cout<<endl;
    }

    return prec[0];
}


int main(){

    ifstream input("input.txt");
    int N;
    input>>N;

    lint result = pilloleIter(N);

    ofstream output("output.txt");
    output<<result<<endl;
    cout<<result<<endl<<endl;

    return 0;
}

//  P(i, m) = P(i, m-1) + P(i-1, m+1)

