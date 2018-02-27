#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

int knapsackRec(vector<int> &weight, vector<int> &profit, int i, int c, int **DP) {
	if (i == 0 || c == 0) {
		return 0;
	}

	if (DP[i][c] < 0) {
		int notTaken = knapsackRec(weight, profit, i - 1, c, DP);
		int taken;
		if(weight[i-1] <= c){
			taken = knapsackRec(weight, profit, i - 1, c - weight[i-1], DP) + profit[i];
		}
		else{
			taken = INT_MIN;
		}
		DP[i][c] = max(taken, notTaken);
	}

	return DP[i][c];
}

int knapsack(vector<int> &weight, vector<int> &profit, int C) {
	int items = weight.size();
	int **DP = new int *[items + 1];
	for (int i = 0; i < items + 1; i++) {
		DP[i] = new int[C + 1];
		for (int j = 0; j < C + 1; j++) {
			DP[i][j] = -1;
		}
	}
	
	return knapsackRec(weight, profit, items, C, DP);
}

int main() {
	vector<int> weight = {5, 24, 5, 23, 14, 35};
	vector<int> profit = {21, 32, 1, 21, 12, 14};
	int C = 50;

	cout << knapsack(weight, profit, C);

	return 0;
}

/*
Prendi >= 18 => puoi rifare stessa sessione
Prendi < 18 => salti a sessione dopo
Rifai => se consegni, sovrascrivi
Rifai => se NON consegni, conta quello prima (very noice)
*/