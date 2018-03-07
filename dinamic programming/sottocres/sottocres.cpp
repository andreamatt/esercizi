#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
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

int sottocres(vector<int>& seq){
    int N = seq.size();

    map<int,int> DP;
    if(seq[0] >= 0){
        DP.insert({seq[0], seq[0]});
    }
    else{
        DP.insert({INT_MIN, 0});
    }

    cout<<0<<" ("<<seq[0]<<"): "<<DP.begin()->second<<endl;
    
    for (map<int,int>::iterator it=DP.begin(); it!=DP.end(); ++it){
        cout << it->first << " => " << it->second << '\n';
    }
    cout<<"---------------------------------"<<endl;
    
    //////
    for(int i=1; i<N; i++){
        int value = seq[i];

        // non prendo => ultimo
        int notTaken = DP.rbegin()->second;
        
        // prendo => numeri minori di value, + value
        int taken = value + (--DP.lower_bound(value))->second;

        cout<<i<<" ("<<value<<"): "<<"t "<<taken<<", nT "<<notTaken<<endl;
        cout<<"upper: "<<(--DP.upper_bound(value))->second<<endl;
        cout<<"lower: "<<(--DP.lower_bound(value))->second<<endl;

        DP.insert({value, taken});
        
        for (map<int,int>::iterator it=DP.begin(); it!=DP.end(); ++it){
           cout << it->first << " => " << it->second << '\n';
        }
        cout<<"---------------------------------"<<endl;
        
    }

    int mx = 0;
    for (map<int,int>::iterator it=DP.begin(); it!=DP.end(); ++it){
        mx = max(mx, it->second);
    }

    return mx;
}


int main(){

    ifstream input("input.txt");
    int N;
    input>>N;
    vector<int> seq(N);
    for(int i=0; i<N; i++){
        input>>seq[i];
    }

    int result = sottocresRec(seq, N-1, INT_MAX);
    cout<<result<<endl;
    ofstream output("output.txt");
    output<<result;

    return 0;
}

