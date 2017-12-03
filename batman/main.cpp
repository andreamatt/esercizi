#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
#include <unordered_set>

using  namespace std;

struct node{
    vector<node*> vic;
    int value;
    bool visited = false;
    int SCC = -1;
    void removeVic(node* toRem){
        for(int i=0; i<vic.size(); i++){
            if(vic[i] == toRem){
                vic.erase(vic.begin() + i);
                return;
            }
        }
    }
    int ways = 0;
};

void DFS(node* start, stack<int>& stack1);
void DFSTranspose(node* start, vector<int>& SCC);
vector<unordered_set<node*>> findSCCs(vector<node>& graph, vector<node>& transpose);
vector<node> getNewGraph(vector<unordered_set<node*>>& SCCs, int& start, int& end, vector<node>& oldGraph);
int possibleWaysFromHere(node* start, node* end);

int main() {

    ifstream input("input.txt");
    int N, M, S, E;
    input>>N>>M>>S>>E;
    vector<node> graph;
    vector<node> transpose;
    graph.resize(N);
    transpose.resize(N);
    for(int i=0; i<N; i++){
        graph[i].value = i;
        transpose[i].value = i;
    }
    for(int i=0; i<M; i++){
        int from, to;
        input>>from>>to;
        graph[from].vic.push_back(&graph[to]);
        transpose[to].vic.push_back(&transpose[from]);
    }

    vector<unordered_set<node*>> SCCs = findSCCs(graph, transpose);
    cout<<"SCCs: "<<SCCs.size()<<endl;
    for(int i=0; i<SCCs.size(); i++){
        //cout<<"SCC "<<i<<":"<<endl;
        for(node* n : SCCs[i]){
            //cout<<n->value<<" ";
        }
        //cout<<endl;
    }

    // new Graph
    vector<node> newGraph = getNewGraph(SCCs, S, E, graph);
    cout<<endl<<"NEW GRAPH:"<<endl;
    for(int i=0; i<newGraph.size(); i++){
        cout<<"Node "<<i<<": ";
        for(node* v : newGraph[i].vic){
            cout<<v->value<<" ";
        }
        cout<<endl;
    }
    cout<<"Start: "<<S<<", end: "<<E<<endl;

    // WAYS
    ofstream output("output.txt");
    output<<possibleWaysFromHere(&newGraph[S], &newGraph[E]);

    return 0;
}

int possibleWaysFromHere(node* start, node* end){
    if(start == end){
        return 1;
    }
    if(start->visited){
        return start->ways;
    }
    // generic case
    start->visited = true;
    int result = 0;
    for(node* v : start->vic){
        result += possibleWaysFromHere(v, end);
    }
    start->ways = result;
    return result;
}

vector<node> getNewGraph(vector<unordered_set<node*>>& SCCs, int& start, int& end, vector<node>& oldGraph){
    vector<node> newG;
    newG.resize(SCCs.size());
    for(int i=0; i<newG.size(); i++){
        newG[i].value = i;
    }
    bool startFound = false, endFound = false;
    for(int scc=0; scc<SCCs.size(); scc++){
        // replace start and end
        if(!startFound && SCCs[scc].find(&oldGraph[start]) != SCCs[scc].end()){
            start = scc;
            startFound = true;
        }
        if(!endFound && SCCs[scc].find(&oldGraph[end]) != SCCs[scc].end()){
            end = scc;
            endFound = true;
        }

        // create all new edges
        for(node* n : SCCs[scc]){
            for(node* v : n->vic){
                // if not in this SCC, add new edge
                if(SCCs[scc].find(v) == SCCs[scc].end()){
                    newG[scc].vic.push_back(&newG[v->SCC]);
                }
            }
        }
    }

    return newG;
}

vector<unordered_set<node*>> findSCCs(vector<node>& graph, vector<node>& transpose){
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
        if(transpose[stack1.top()].visited){
            stack1.pop();
        }
        else{
            vector<int> tempV;
            DFSTranspose(&transpose[stack1.top()], tempV);
            SCCs.push_back(tempV);
        }
    }

    vector<unordered_set<node*>> SCCs_set;
    for(int i=0; i<SCCs.size(); i++) {
        unordered_set<node*> temp;
        for(int n : SCCs[i]) {
            temp.insert(&graph[n]);
            graph[n].SCC = i;
        }
        SCCs_set.push_back(temp);
    }

    return SCCs_set;
}

void DFSTranspose(node* start, vector<int> &SCC){
    start->visited = true;
    SCC.push_back(start->value);
    for(node* v : start->vic){
        if(!v->visited) {
            DFSTranspose(v, SCC);
        }
    }
}

void DFS(node* start, stack<int>& stack1){
    start->visited = true;

    for(node* v : start->vic){
        if(!v->visited){
            DFS(v, stack1);
        }
    }

    stack1.push(start->value);
}