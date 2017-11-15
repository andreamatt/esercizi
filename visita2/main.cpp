#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct nodo{
    vector<nodo*> vicini;
    bool visited = false;
};

int DFS(vector<nodo> &, nodo &);

int main() {

    ifstream input("input.txt");
    int N, M, S;
    input>>N>>M>>S;
    vector<nodo> grafo;
    grafo.resize(N);
    for(int i=0; i<M; i++) {
        int from, to;
        input >> from >> to;
        grafo[from].vicini.push_back(&grafo[to]);
    }

    // BFS
    grafo[S].visited = true;
    vector<nodo*> toReach;
    toReach.push_back(&grafo[S]);
    for (int i = 0; i < toReach.size(); i++) {
        for (nodo* j : toReach[i]->vicini) {
            if (!j->visited) {
                j->visited = true;
                toReach.push_back(j);
                //cout<<"added "<<grafo[toReach[i]].vicini[j]<<endl;
            }
        }
    }
    ofstream output("output.txt");
    output<<toReach.size();


    // DFS
    //ofstream output("output.txt");
    //output<<DFS(grafo, grafo[S]);


    return 0;
}

int DFS(vector<nodo> &grafo, nodo &S){

    if(S.visited){
        return 0;
    }

    S.visited = true;
    int result = 1;
    for(nodo* i : S.vicini){
        result += DFS(grafo, *i);
    }
    return result;
}