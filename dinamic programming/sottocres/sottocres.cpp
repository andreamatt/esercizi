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

void test(){
    map<int, int> t;
    t.insert({{4, 2}, {5, 4}, {10, 9}});
    for (map<int,int>::iterator it=t.begin(); it!=t.end(); ++it){
        cout << it->first << " => " << it->second << '\n';
    }

    cout<<"Begin: "<<t.begin()->first<<", end: "<<(t.end())->first<<", rbegin: "<<t.rbegin()->first<<endl;
    cout<<"Upper: "<<t.upper_bound(2)->first<<", lower: "<<t.lower_bound(2)->first<<endl;
    cout<<"Upper_dec: "<<(--t.upper_bound(2))->first<<endl;
    cout<<(--t.begin()==t.end())<<endl;
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

    //test();

    int result = sottocres(seq);
    //cout<<result<<endl;
    ofstream output("output.txt");
    output<<result;
    //cout<<"Ric: "<<sottocresRec(seq, N-1, INT_MAX)<<endl;

    return 0;
}

