#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct nodo{
    vector<int> vicini;
    bool visited = false;
};

int DFS(vector<nodo> &, int);

int main() {

    ifstream input("input.txt");
    int N, M, S;
    input>>N>>M>>S;
    vector<nodo> grafo;
    grafo.resize(N);
    for(int i=0; i<M; i++) {
        int from, to;
        input >> from >> to;
        grafo[from].vicini.push_back(to);
    }

    // BFS
    /*
    grafo[S].visited = true;
    vector<int> toReach;
    toReach.push_back(S);
    for (int i = 0; i < toReach.size(); i++) {
        for (int j = 0; j < grafo[toReach[i]].vicini.size(); j++) {
            if (!grafo[grafo[toReach[i]].vicini[j]].visited) {
                grafo[grafo[toReach[i]].vicini[j]].visited = true;
                toReach.push_back(grafo[toReach[i]].vicini[j]);
                //cout<<"added "<<grafo[toReach[i]].vicini[j]<<endl;
            }
        }
    }
    ofstream output("output.txt");
    output<<toReach.size();
    */

    // DFS
    ofstream output("output.txt");
    output<<DFS(grafo, S);


    return 0;
}

int DFS(vector<nodo> &grafo, int S){

    if(grafo[S].visited){
        return 0;
    }

    grafo[S].visited = true;
    int result = 1;
    for(int i : grafo[S].vicini){
        result += DFS(grafo, i);
    }
    return result;
}