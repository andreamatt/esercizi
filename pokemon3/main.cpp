#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <unordered_set>
#include "graph_utils.h"

using namespace std;

int main() {

    ifstream input("input.txt");
    int N, M;
    input>>N>>M;
    Graph graph(N);
    for(int i=0; i<N; i++){
        graph[i].value = i;
    }

    for(int i=0; i<M; i++){
        int from, to;
        input>>from>>to;
        graph[from].vic.push_back(Edge(&graph[to]));
        graph[to].vic.push_back(Edge(&graph[from]));

    }

    cout<<gcd(0, 7);


    return 0;
}

