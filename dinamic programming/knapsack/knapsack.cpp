#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>

using namespace std;

struct pair_hash {
    inline std::size_t operator()(const std::pair<int,int> & v) const {
        return v.first*31+v.second;
    }
};

int knapsackMemoHash(vector<int> w, vector<int> p, int n, int C){
	unordered_map<pair<int,int>, int, pair_hash> DP;
	DP.insert({make_pair(5, 2), 10});
	cout<<DP.at(make_pair(5, 2));
	return -1; 
}

int knapsackIter(vector<int> w, vector<int> p, int n, int C){
	int** DP = new int*[n+1];
	for(int i=0; i<=n; i++){
		DP[i] = new int[C+1]{};
	}
	
	for(int i=1; i<=n; i++){
		for(int c=1; c<=C; c++){
			int notTaken = DP[i-1][c];
			int taken = (w[i] <= c) ? DP[i-1][c - w[i]] + p[i] : -1;
			DP[i][c] = max(taken, notTaken);
		}
	}
	
	for(int i=0; i<=n; i++){
		for(int c=0; c<=C; c++){
			cout<<DP[i][c]<<", ";
		}
		cout<<endl;
	}
	
	return DP[n][C];
}

int main() {

	int C;
	int n;
	ifstream input("input.txt");
	input>>C>>n;
	vector<int> weight(n+1);
	vector<int> profit(n+1);
	weight.push_back(-1);
	profit.push_back(-1);

	for(int i=1; i<=n; i++){
		input>>weight[i];
		input>>profit[i];
	}

	int result = knapsackMemoHash(weight, profit, n, C);
	ofstream output("output.txt");
	output<<result;

	return 0;
}

/*
Prendi >= 18 => puoi rifare stessa sessione
Prendi < 18 => salti a sessione dopo
Rifai => se consegni, sovrascrivi
Rifai => se NON consegni, conta quello prima (very noice)
*/