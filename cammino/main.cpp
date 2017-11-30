#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct node{
    vector<node*> vic;
    int value;
    bool visited;
    int maxDistanceFromHere = 0;
};

int maxFromHere(node* start);

int main() {

    ifstream input("input.txt");
    int N, M;
    input>>N>>M;
    vector<node> graph;
    graph.resize(N);
    for(int i=0; i<graph.size(); i++){
        graph[i].value = i;
    }
    for(int i=0; i<M; i++){
        int from, to;
        input>>from>>to;
        graph[from].vic.push_back(&graph[to]);
    }

    int mx = 0;
    for(int i=0; i<graph.size(); i++){
        mx = max(mx, maxFromHere(&graph[i]));
    }

    ofstream output("output.txt");
    output<<mx;

    return 0;
}

int maxFromHere(node* start){
    if(start->visited){
        return start->maxDistanceFromHere;
    }

    start->visited = true;
    int mx = 0;
    for(node* v : start->vic){
        mx = max(mx, maxFromHere(v)+1);
    }

    start->maxDistanceFromHere = mx;
    return mx;
}