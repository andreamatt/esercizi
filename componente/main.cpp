#include <iostream>
#include <vector>
#include <fstream>
#include <stack>

using namespace std;

struct nodo{
    vector<nodo*> vic;
    bool visited = false;
    int value;
    nodo* parent = nullptr;
};

void DFS(nodo* start, stack<int>& stack1);
void DFSTranspose(nodo* start, vector<int> &SCC);

int main() {

    // using Kosaraju's algorithm for SCCs (Strongly Connected Components)

    ifstream input("input.txt");
    int N, M;
    input>>N>>M;
    // graph: default one
    // transposeGraph: reversed edges
    vector<nodo> graph;
    vector<nodo> transposeGraph;
    graph.resize(N);
    transposeGraph.resize(N);
    for(int i=0; i<N; i++){
        graph[i].value = i;
        transposeGraph[i].value = i;
    }

    for(int i=0; i<M; i++){
        int from, to;
        input>>from>>to;
        graph[from].vic.push_back(&graph[to]);
        transposeGraph[to].vic.push_back(&transposeGraph[from]);
    }

    // DFS visit adding to stack
    stack<int> stack1;
    for(int i=0; i<graph.size(); i++){
        if(!graph[i].visited){
            DFS(&graph[i], stack1);
        }
    }

    // visit transpose using stack
    vector<vector<int>> SCCs;
    while(!stack1.empty()){
        if(transposeGraph[stack1.top()].visited){
            stack1.pop();
        }
        else{
            vector<int> tempV;
            DFSTranspose(&transposeGraph[stack1.top()], tempV);
            SCCs.push_back(tempV);
        }
    }

    int mx = 0;
    for(int i=0; i<SCCs.size(); i++){
        int len = SCCs[i].size();
        mx = max(mx, len);
    }

    ofstream output("output.txt");
    output<<mx;

    return 0;
}

void DFSTranspose(nodo* start, vector<int> &SCC){
    start->visited = true;
    SCC.push_back(start->value);
    for(nodo* v : start->vic){
        if(!v->visited) {
            DFSTranspose(v, SCC);
        }
    }
}

void DFS(nodo* start, stack<int>& stack1){
    start->visited = true;

    for(nodo* v : start->vic){
        if(!v->visited){
            DFS(v, stack1);
        }
    }

    stack1.push(start->value);
}