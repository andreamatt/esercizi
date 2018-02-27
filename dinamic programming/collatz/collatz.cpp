#include <iostream>
#include <vector>

using namespace std;

typedef unsigned long long int uint;

struct myVector{
	vector<uint> vec;
	uint get(uint i){
		if(i < 0 || i >= vec.size()){
			cerr<<"Out of range ("<<i<<", "<<vec.size()<<")"<<endl;
			return -1;
		}
		else{
			return vec[i];
		}
	}
	void set(uint i, uint value){
		if(i < 0 || i >= vec.size()){
			cerr<<"Out of range ("<<i<<", "<<vec.size()<<")"<<endl;
		}
		else{
			vec[i] = value;
		}
	}
	uint size(){
		return vec.size();
	}
	void resize(uint dim, uint value=-1){
		if(dim > size()){
			vec.resize(dim, value);
		}
	}
};

uint collatz(uint n, myVector& coll){
	if(coll.size() < n+1){
		coll.resize(n+1, -1);
	}
	if(coll.get(n) == -1){
		uint next = (n%2==0) ? n/2 : (n*3)+1;
		coll.set(n, collatz(next, coll)+1);
	}
	return coll.get(n);
}

// find sum of collatz(i), i from 0 to n
uint collatz_sum(uint n){
	myVector coll;
	coll.resize(n+1);
	coll.set(0, -1);
	coll.set(1, 0);
	uint sum=0;
	for(uint i=1; i<=n; i++){
		sum += collatz(i, coll);
	}
	cout<<"Size: "<<coll.size()<<endl;
	return sum;
}

// find longest same successive collatz
void collatz_serie(uint n){
	myVector coll;
	coll.resize(n+1);
	coll.set(0, -1);
	coll.set(1, 0);

	uint longest=0;
	uint current_len=0;
	uint current_start=0;
	uint prec=-1;
	uint starting=0;
	for(uint i=1; i<=n; i++){
		uint c = collatz(i, coll);
		if(c==prec){
			current_len++;
		}
		else{
			prec=c;
			current_start=i;
			current_len=0;
		}
		if(current_len > longest){
			longest = current_len;
			starting = current_start;
		}
	}

	cout<<longest<<": from "<<starting<<" to "<<starting+longest<<", value: "<<coll.get(starting);
}

int main(){

	int n;
	cout<<"Enter n: ";
	cin>>n;
 
	collatz_serie(n);
	return 0;
}
