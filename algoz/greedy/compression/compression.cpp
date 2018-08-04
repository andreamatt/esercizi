#include <iostream>
#include <fstream>
#include <unordered_map>
#include <map>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

typedef uint8_t byte;

struct Tree{
	int freq;
	char c;
	vector<bool> toBits;
	bool empty;
	Tree* left;
	Tree* right;
	Tree(int freq, char c, bool empty=false, Tree* left=nullptr, Tree* right = nullptr){
		this->freq = freq;
		this->c = c;
		this-> empty = empty;
		this->left = left;
		this-> right = right;
	}
	string toString(){
		string l = (left==nullptr) ? " " : string("(") + left->toString() + ")";
		string r = (right==nullptr) ? " " : string("(") + right->toString() + ")"; 
		return l + "[" + c + ", " + to_string(freq) + "]" + r;
	}
	void setBits(string bits="_"){
		if(bits=="_"){
			if(left!=nullptr) left->setBits("0");
			if(right!=nullptr) right->setBits("1");
		}
		else{
			for(char c : bits) this->toBits.push_back(c=='1');
			if(left!=nullptr) left->setBits(bits + "0");
			if(right!=nullptr) right->setBits(bits + "1");
		}
	}
	void addToMap(unordered_map<char,vector<bool>> &map){
		if(!empty) map.insert({c, toBits});
		if(left!=nullptr) left->addToMap(map);
		if(right!=nullptr) right->addToMap(map);
	}
};

Tree* buildTree(multimap<int,Tree*> &ordered){
	if(ordered.size() == 1){
		//IDK
		return (*(ordered.begin())).second;
	}
	// tolgo i primi due
	pair<int,Tree*> a = *(ordered.begin());
	ordered.erase(ordered.begin());
	pair<int,Tree*> b = *(ordered.begin());
	ordered.erase(ordered.begin());

	// inserisco un nuovo con freq = fa + fb
	ordered.insert({a.first + b.first, new Tree(a.first + b.first, '_', true, a.second, b.second)});
	return buildTree(ordered);
}

unordered_map<char,vector<bool>> treeToMap(Tree* tree){
	tree->setBits();
	unordered_map<char,vector<bool>> map;
	tree->addToMap(map);
	return map;
}

vector<byte> fileToBytes(string path){
	ifstream input(path);
	// reading
	unordered_map<char, int> count;
	multimap<int, Tree*> ordered_count;
	int tot=0;
	char t='#';
	while(input >> noskipws >> t){
		if(count.find(t)!=count.end()){
			count[t]++;
		}
		else{
			count[t]=1;
		}
		tot++;
	}

	// ordering
	for(pair<char,int> p : count){
		Tree* tree = new Tree(p.second, p.first);
		ordered_count.insert({p.second, tree});
	}
	
	// to tree
	Tree* tree = buildTree(ordered_count);
	cout<<tree->toString()<<endl;

	// get map from char to bits
	unordered_map<char,vector<bool>> charToBits = treeToMap(tree);

	// create vector of words
	vector<vector<bool>> codifiedText;
	input.clear();
	input.seekg(0, input.beg);
	while(input >> noskipws >> t){
		codifiedText.push_back(charToBits[t]);
	}

	// create vector of bytes
	vector<byte> cod_bytes;
	int pos=7;
	byte result=0;
	for(vector<bool> t : codifiedText){
		for(bool b : t){
			result += (b) ? pow(2, pos) : 0;
			pos--;
			if(pos==0){
				cod_bytes.push_back(result);
				pos=7;
				result=0;
			}
		}
	}

	return cod_bytes;
}

int main(){

	vector<byte> codified = fileToBytes("file.txt");
	ofstream output("codified");
	for(byte b : codified){
		output<<b;
	}

	return 0;
}