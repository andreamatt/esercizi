#include <iostream>
#include <vector>

using namespace std;

int ugly(int n) {
	vector<unsigned int> numbers = {1};
	int x, y, z;
	x=y=z=0; // ugly index
	int a,b,c;
	while(numbers.size() < n) {
		a = numbers[x]*2;
		b = numbers[y]*3;
		c = numbers[z]*5;
		int mn = min(min(a, b), c);
		numbers.push_back(mn);
		if(a < 0 || b < 0 || c < 0){
			cout<<x<<", "<<y<<", "<<z<<endl;
			return -1;
		}
		if(mn == a){
			x++;
		}
		if(mn == b){
			y++;
		}
		if(mn == c){
			z++;
		}
	}
	//for(auto& a : numbers){cout<<a<<", ";}	cout<<endl;
	return numbers.back();
}

int main() {
	int n;
	cin >> n;
	cout << ugly(n);
	return 0;
}