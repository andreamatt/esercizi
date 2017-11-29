#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct nodo{
    vector<nodo*> vic;
    int value;
    bool visited = false;
};

int maxFromHere(nodo*, bool);

int main() {

    int N, M;
    vector<nodo> grafo;
    ifstream input("input.txt");
    input>>N>>M;
    grafo.resize(N);
    for(int i=0; i<N; i++){
        grafo[i].value = i;
    }
    for(int i=0; i<M; i++){
        int from, to;
        input>>from>>to;
        grafo[from].vic.push_back(&grafo[to]);
        grafo[to].vic.push_back(&grafo[from]);
    }

    int maxD = 0;
    bool valueW = true;
    // BFS starting from every node, the last i reach is the farthest
    // instead of resetting "visited" to false, i just switch between true and false the expected value
    for(nodo n : grafo){
        maxD = max(maxD, maxFromHere(&n, valueW));
        valueW = !valueW;
    }

    ofstream output("output.txt");
    output<<maxD;

    return 0;
}

int maxFromHere(nodo* from, bool valueWant){

    vector<pair<nodo*,int>> toReach;
    from->visited = true;
    pair<nodo*,int> p = make_pair(from, 0);
    toReach.push_back(p);
    //cout<<"Distance from "<<from->value<<endl;
    for(int i=0; i<toReach.size(); i++){
        for(nodo* j : toReach[i].first->vic){
            if(j->visited != valueWant){
                pair<nodo*,int> t = make_pair(j, toReach[i].second+1);
                toReach.push_back(t);
                j->visited = valueWant;
                //cout<<"Added "<<t.first->value<<" "<<t.second<<endl;
            }
        }
    }
    //cout<<endl;
    return toReach[toReach.size()-1].second;
}

