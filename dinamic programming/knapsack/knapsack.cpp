#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int knapsackMemoMatRec(vector<int>& w, vector<int>& p, int i, int c, int** DP){
	if(c < 0){
		return -1;
	}
	if(i==0 || c==0){
		return 0;
	}

	if(DP[i][c] == -1){
		int notTaken = knapsackMemoMatRec(w, p, i-1, c, DP);
		int taken = -1;
		if(w[i] <= c){
			taken = p[i] + knapsackMemoMatRec(w, p, i-1, c-w[i], DP);
		}
		DP[i][c] = max(taken, notTaken);
	}

	return DP[i][c];
}

int knapsackMemoMat(vector<int>& w, vector<int>& p, int n, int C){
	int** DP = new int*[n+1];
	for(int i=0; i<=n; i++){
		DP[i] = new int[C+1];
		for(int c=0; c<=C; c++){
			DP[i][c] = -1;
		}
	}

	int result = knapsackMemoMatRec(w, p, n, C, DP);

	return result;
}

int knapsackIterVec(vector<int>& w, vector<int>& p, int n, int C){
	vector<int> prec(C+1, 0);
	vector<int> curr(C+1, 0);

	for(int i=1; i<=n; i++){
		for(int c=1; c<=C; c++){
			int notTaken = prec[c];
			int taken = -1;
			if(w[i] <= c){
				taken = prec[c - w[i]] + p[i];
			}
			curr[c] = max(taken, notTaken);
		}
		//swap the 2 vecs
		for(int c=0; c<=C; c++){
			//cout<<curr[c]<<", ";
			prec[c] = curr[c];
			curr[c] = 0;
		}
		//cout<<endl;
	}

	return prec.back();
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
			int result = DP[i][c];
			if(c != 0){
				cout<<", ";
				if(result < 10 && result >= 0){
					cout<<" ";
				}
			}
			cout<<result;
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

	int result = knapsackIterVec(weight, profit, n, C);
	ofstream output("output.txt");
	output<<result;
	cout<<result<<endl;

	return 0;
}

/*
Prendi >= 18 => puoi rifare stessa sessione
Prendi < 18 => salti a sessione dopo
Rifai => se consegni, sovrascrivi
Rifai => se NON consegni, conta quello prima (very noice)
*/