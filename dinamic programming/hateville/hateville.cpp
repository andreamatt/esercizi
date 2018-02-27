#include <vector>
#include <iostream>
#include <algorithm>

using  namespace std;

vector<int> hateville(vector<int> donations){
	vector<int> HV(donations.size());
	HV[0] = donations[0];
	HV[1] = max(donations[0], donations[1]);
	for(int i=2; i<HV.size(); i++){
		HV[i] = max(HV[i-1], donations[i] + HV[i-2]);
	}

	vector<int>donators;
	int i = HV.size()-1;
	while(i>=1){
		if(HV[i] == HV[i-1]){
			// non ho preso i
			i = i-1;
		}
		else{
			// ho preso i
			donators.push_back(i);
			i = i-2;
		}
	}
	
	if(i==0){
		donators.push_back(i);
	}

	reverse(donators.begin(), donators.end());

	return donators;;
}

int main(){
	vector<int> donations = {3, 6, 10, 22, 1, 5, 8};
	vector<int> donators = hateville(donations);
	for(auto var : donators){
		cout<<var<<" ("<<donations[var]<<"), ";
	}
	return 0;
}