#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

struct nodo{
    vector<nodo*> vic;
    bool visited;
    int value;
};

void funzione(unordered_set<pair<nodo*,nodo*>>& result, nodo* a, nodo* b);

int main() {



    return 0;
}

void funzione(unordered_set<pair<nodo*,nodo*>>& result, nodo* a, nodo* b){
    result.insert(make_pair(a, b));
    pair<nodo*,nodo*> temp = make_pair(a, b);
    result.insert(temp);
    cout<<result.size();
}