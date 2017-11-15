#include <iostream>
#include <vector>
#include <fstream>
#include <climits>

using namespace std;

struct nodo{
    vector<nodo*> vic;
    int value;
    bool visited = false;
};

pair<int,int> numCamminiMinBFS(nodo*, nodo*);

int main() {
    int N, M, S, E;
    vector<nodo> grafo;
    ifstream input("input.txt");
    input>>N>>M>>S>>E;
    grafo.resize(N);
    for(int i=0; i<N; i++){
        grafo[i].value = i;
    }
    for(int i=0; i<M; i++){
        int from, to;
        input>>from>>to;
        grafo[from].vic.push_back(&grafo[to]);
    }

    ofstream output("output.txt");
    pair<int,int> result = numCamminiMinBFS(&grafo[S], &grafo[E]);
    output<<result.first<<" "<<result.second;

    return 0;
}

pair<int,int> numCamminiMinBFS(nodo* from, nodo* to){

    vector<pair<nodo*,int>> toReach;
    pair<nodo*,int> p = make_pair(from, 0);
    toReach.push_back(p);

    int minDist = INT_MAX;
    int ways = 0;

    for(int i=0; i<toReach.size(); i++){
        if(toReach[i].second >= minDist){
            // tutti i suoi vicini sono piu distanti => li salto
        }
        else {
            for (nodo *n : toReach[i].first->vic) {
                if(n == to){
                    minDist = toReach[i].second +1;
                    ways++;
                }
                else if (!n->visited) {
                    pair<nodo*,int> t = make_pair(n, toReach[i].second +1);
                    toReach.push_back(t);
                }

            }
        }
    }

    return pair<int,int>(minDist, ways);
}