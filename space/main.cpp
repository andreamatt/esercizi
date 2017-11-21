#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_set>

using namespace std;

struct nodo{
    bool visited = false;
    bool isArticulation = false;
    nodo* parent = nullptr;
    int time;
    int lowTime;
    int value;
    vector<nodo*> vic;
};

void allArticulationPoints(nodo* current, int time);
vector<int> allVicere(vector<nodo>& grafo);

int main() {

    ifstream input("input.txt");
    int N, M;
    input>>N>>M;

    vector<nodo> grafo;
    grafo.resize(N);
    for (int i = 0; i < N; ++i) {
        grafo[i].value = i;
    }
    for (int i = 0; i < M; ++i) {
        int from, to;
        input>>from>>to;
        grafo[from].vic.push_back(&grafo[to]);
        grafo[to].vic.push_back(&grafo[from]);
    }

    vector<int> vicere = allVicere(grafo);

    ofstream output("output.txt");
    output<<vicere.size()<<endl;
    for(int i : vicere){
        output<<i<<" ";
    }

    return 0;
}

void allArticulationPoints(nodo* current, int time){
    current->visited = true;
    current->time = time;
    current->lowTime = time;
    int childCount = 0;
    bool isArticulation = false;
    for(nodo* v : current->vic){
        if(!v->visited){
            v->parent = current;
            allArticulationPoints(v, time+1);
            childCount++;
            if(v->lowTime >= current->time){
                isArticulation = true;
            }
            current->lowTime = min(current->lowTime, v->lowTime);
        }
        else if(v != current->parent){
            current->lowTime = min(current->lowTime, v->time);
        }
    }

    if((current->parent != nullptr && isArticulation) || (current->parent == nullptr && childCount > 1)){
        //cout<<current->value<<endl;
        current->isArticulation = true;
    }
}

vector<int> allVicere(vector<nodo>& grafo){
    // find articulation points
    allArticulationPoints(&grafo[0], 0);

    // reset all to unvisited
    for(int i=0; i<grafo.size(); i++){
        grafo[i].visited = false;
    }

    vector<int> vicere;
    // for each node, NOT art-points, gather points until find arts
    for(int i=0; i<grafo.size(); i++){
        if(!grafo[i].isArticulation && !grafo[i].visited){
            // visit nodes, NOT APs, check if encounted more than 1 AP
            vector<nodo*> toReach;
            unordered_set<nodo*> APs;
            grafo[i].visited = true;
            toReach.push_back(&grafo[i]);
            for(int j=0; j<toReach.size(); j++){
                for(nodo* v : toReach[j]->vic){
                    if(v->isArticulation){
                        APs.insert(v);
                    }
                    else if(!v->visited){
                        v->visited = true;
                        toReach.push_back(v);
                    }
                }
            }
            if(APs.size() == 1){
                //cout<<"Vicere: "<<grafo[i].value<<endl;
                vicere.push_back(grafo[i].value);
            }
        }
    }

    return vicere;
}


