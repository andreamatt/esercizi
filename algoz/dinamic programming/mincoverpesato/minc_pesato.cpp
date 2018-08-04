#include <iostream>
#include <fstream>
#include <vector>
#include <limits.h>

using namespace std;

struct Node{
    vector<int> vic;
    bool visited = false;
    int weight;
};

struct Tree{
    vector<Tree> children;
    int value;
    int weight;
    Tree(){};
    Tree(int n, int w){
        value = n;
        weight = w;
    }
};

Tree graphToTree(vector<Node>& graph, int n){
    Tree t(n, graph[n].weight);
    graph[n].visited = true;
    for(int v : graph[n].vic){
        if(graph[v].visited == false){
            t.children.push_back(graphToTree(graph, v));
        }
    }
    return t;
}

void DFS(Tree t){
    cout<<t.value<<", "<<t.weight<<endl;
    for(Tree c : t.children){
        DFS(c);
    }
}

int minC_rec(Tree& t, bool needToTake, vector<int>& taking, vector<int>& notTaking){
    //cout<<"At: "<<t.value<<", "<<(needToTake ? "true" : "false")<<endl;
    if(needToTake){
        if(taking[t.value] == -1){
            int taken = t.weight;
            for(Tree& c : t.children){
                taken += min( minC_rec(c, true, taking, notTaking), minC_rec(c, false, taking, notTaking) );
            }
            taking[t.value] = taken;
        }
        return taking[t.value];
    }
    else{
        if(notTaking[t.value] == -1){
            int taken = minC_rec(t, true, taking, notTaking);
            int notTaken = 0;
            for(Tree& c : t.children){
                notTaken += minC_rec(c, true, taking, notTaking);
            }
            notTaking[t.value] = min(taken, notTaken);
        }
        return notTaking[t.value];
    }
}

int minC(Tree& t, int N){
    vector<int> taking(N, -1);
    vector<int> notTaking(N, -1);

    return minC_rec(t, false, taking, notTaking);
}

int main(){

    ifstream input("input.txt");
    int N;
    input>>N;
    vector<Node> graph(N);
    for(int i=0; i<N; i++){
        int w;
        input>>w;
        graph[i].weight = w;
    }

    for(int i=0; i<N-1; i++){
        int from, to;
        input>>from>>to;
        graph[from].vic.push_back(to);
        graph[to].vic.push_back(from);
    }

    Tree tree = graphToTree(graph, 0);
    vector<Node>().swap(graph);
    //DFS(tree);    cout<<endl<<endl;

    int result = minC(tree, N);

    ofstream output("output.txt");
    output<<result;
    cout<<result<<endl;

    return 0;
}