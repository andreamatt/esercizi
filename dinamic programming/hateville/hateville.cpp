#include <vector>
#include <iostream>

using  namespace std;

int hateville(vector<int> donations){
	vector<int> HV(donations.size());
	HV[0] = donations[0];
	HV[1] = max(donations[0], donations[1]);
	for(int i=2; i<HV.size(); i++){
		HV[i] = max
	}
	return 0;
}

int main(){
	vector<int> donations = {6, 3, 10, 22, 1, 5, 8};
	cout << hateville(donations);
	return 0;
}