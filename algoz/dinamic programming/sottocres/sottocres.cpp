#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <climits>

using namespace std;

int sottocresRec(vector<int>& seq, int i, int limit){
    if(i==0){
        if(seq[0] < limit){
            return max(0, seq[0]);
        }
        else{
            return 0;
        }
    }

    if(seq[i] > limit){
        return sottocresRec(seq, i-1, limit);
    }

    int notTaken = sottocresRec(seq, i-1, limit);
    
    int taken = seq[i] + sottocresRec(seq, i-1, seq[i]);

    return max(taken, notTaken);
}

int sottocresMonoRec(vector<int>& seq, int i, vector<int>& DP){
    int N = seq.size();

    if(DP[i] == -1){
        int mx = 0;
        for(int j=i+1; j<N; j++){
            if(seq[i] <= seq[j]){
                mx = max(mx, sottocresMonoRec(seq, j, DP));
            }
        }
        DP[i] = mx + seq[i];
    }

    return DP[i];
}

int sottocresMono(vector<int>& seq){
    int N = seq.size();
    vector<int> DP(N, -1);
    int mx = 0;
    for(int i=0; i<N; i++){
        int result = sottocresMonoRec(seq, i, DP);
        mx = max(mx, result);
    }
    return mx;
}

int sottocresDualRec(vector<int>& seq, int i, int j, int** DP){
    int N = seq.size(); 
    if(i==N){
        return 0;
    }

    if(DP[i][j] == -1){
        if(seq[i] < seq[j]){
            DP[i][j] = sottocresDualRec(seq, i+1, j, DP);
        }
        else{
            DP[i][j] = max(sottocresDualRec(seq, i+1, j, DP), sottocresDualRec(seq, i+1, i, DP) + seq[i]);
        }
    }

    return DP[i][j];
}

int sottocresDual(vector<int>& seq){
    int N = seq.size();
    int** DP = new int*[N];
    for(int i=0; i<N; i++){
        DP[i] = new int[N];
        for(int j=0; j<N; j++){
            DP[i][j] = -1;
        }
    }

    

    return sottocresDualRec(seq, 0, 0, DP);
}

int sottocres(vector<int>& seq){
    int N = seq.size();

    map<int,int> DP;
    DP[INT_MIN] = 0;
    
    //////
    for(int i=0; i<N; i++){
        int value = seq[i];

        // non prendo => ultimo (non me ne frega)
        //int notTaken = DP.rbegin()->second;
        
        // prendo => numeri minori di value, + value
        map<int,int>::iterator limite = --DP.upper_bound(value);

        int max_guad = 0;
        while(limite->first != INT_MIN){
            max_guad = max(max_guad, limite->second);
            limite--;
        }

        int taken = max_guad + value;

        //cout<<i<<" ("<<value<<"): "<<"t "<<taken<<endl;
        //cout<<"limite: "<<limite->second<<", max_guad: "<<max_guad<<endl;

        DP[value] = taken;
        
        //for (map<int,int>::iterator it=DP.begin(); it!=DP.end(); ++it)  cout << it->first << " => " << it->second << '\n';
        //cout<<"---------------------------------"<<endl;
        
    }

    int mx = 0;
    for (map<int,int>::iterator it=DP.begin(); it!=DP.end(); ++it){
        mx = max(mx, it->second);
    }

    return mx;
}

// serve upperbound diminuito

int main(){

    ifstream input("input.txt");
    int N;
    input>>N;
    vector<int> seq(N);
    for(int i=0; i<N; i++){
        input>>seq[i];
    }
    
    int result = sottocresMono(seq);
    ofstream output("output.txt");
    cout<<result<<endl;
    output<<result;
    
    return 0;
}

