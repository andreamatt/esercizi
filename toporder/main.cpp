#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
#include <unordered_set>

using namespace std;

struct node{
    vector<node*> vic;
    unordered_set<node*> incoming;
    int value;
    bool visited = false;
};

vector<int> Kahn_topoSort(vector<node>& graph);
void visit(node& n, stack<int>& sorted);
vector<int> DFS_topoSort(vector<node>& graph);

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
        graph[to].incoming.insert(&graph[from]);
    }

    //vector<int> sorted = Kahn_topoSort(graph);
    vector<int> sorted = DFS_topoSort(graph);

    ofstream output("output.txt");
    for(int i : sorted){
        output<<i<<" ";
    }

    return 0;
}

vector<int> DFS_topoSort(vector<node>& graph){
    stack<int> sortedStack;
    for(node& n : graph){
        if(!n.visited){
            visit(n, sortedStack);
        }
    }

    vector<int> sorted;
    while(!sortedStack.empty()){
        int n = sortedStack.top();
        sorted.push_back(n);
        sortedStack.pop();
    }

    return sorted;
}

void visit(node& n, stack<int>& sorted){
    if(n.visited){
        return;
    }
    for(node* m : n.vic){
        visit(*m, sorted);
    }
    n.visited = true;
    sorted.push(n.value);
}

vector<int> Kahn_topoSort(vector<node>& graph){
    vector<int> sorted;
    stack<node*> no_incoming;
    for(node& n : graph){
        if(n.incoming.size() == 0){
            no_incoming.push(&n);
        }
    }

    while(!no_incoming.empty()){
        node* n = no_incoming.top();
        no_incoming.pop();
        sorted.push_back(n->value);
        for(node* m : n->vic){
            m->incoming.erase(n);
            if(m->incoming.size() == 0){
                no_incoming.push(m);
            }
        }
        n->vic.clear();
    }

    return sorted;
}