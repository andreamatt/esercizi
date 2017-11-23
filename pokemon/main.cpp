#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_set>

using namespace std;

struct nodo{
    bool visited = false;
    bool removed = false;
    bool starter = false;
    int value;
    unordered_set<nodo*> vic;
};

void removeSingles(vector<nodo>&);
int GCD(int a, int b);
int GCDFromHere(nodo* start);

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
        grafo[from].vic.insert(&grafo[to]);
        grafo[to].vic.insert(&grafo[from]);
    }

    removeSingles(grafo);

    int starters = 0;
    for(int i=0; i<grafo.size(); i++){
        if(!grafo[i].removed && grafo[i].vic.size() > 2){
            grafo[i].starter = true;
            starters++;
        }
    }
    if(starters == 0){
        for(int i=0; i<grafo.size() && starters == 0; i++){
            if(!grafo[i].removed && grafo[i].vic.size() == 2){
                grafo[i].starter = true;
                starters++;
            }
        }
    }

    bool first = true;
    int currentGCD = -1;
    for(int i=0; i<grafo.size(); i++){
        if(grafo[i].starter && !grafo[i].visited){
            if(first){
                currentGCD = GCDFromHere(&grafo[i]);
                first = false;
            }
            else{
                currentGCD = GCD(currentGCD, GCDFromHere(&grafo[i]));
            }
        }
    }



    ofstream output("output.txt");
    output<<currentGCD;

    return 0;
}

int GCDFromHere(nodo* start){
    bool first = true;
    int len = 1;
    int currentGCD;
    start->visited = true;
    for(nodo* v : start->vic){
        if(!v->visited && v->vic.size() == 2){
            nodo* next = v;
            while(!next->visited && next->vic.size() == 2){
                next->visited = true;
                len++;
                nodo* _temp;
                for(nodo* nv : next->vic){
                    if(!nv->visited){
                        _temp = nv;
                    }
                }
                next = _temp;
            }
            if(first){
                first = false;
                currentGCD = len;
            }
            else{
                currentGCD = GCD(currentGCD, len);
            }
            //cout<<"Started at: "<<v->value<<", len: "<<len<<endl;
            len=1;
        }
    }

    //cout<<"GCD: "<<currentGCD<<endl<<endl;

    return currentGCD;
}

void removeSingles(vector<nodo>& grafo){
    vector<nodo*> toReach;
    for(int i=0; i<grafo.size(); i++){
        if(grafo[i].vic.size() == 1){
            toReach.push_back(&grafo[i]);
            cout<<"Removing: "<<grafo[i].value<<endl;
        }
    }

    for(int i=0; i<toReach.size(); i++){
        toReach[i]->removed = true;
        nodo* toRemove = nullptr;
        for(nodo* v : toReach[i]->vic){
            toRemove = v;
        }
        toRemove->vic.erase(toReach[i]);
        toReach[i]->vic.erase(toRemove);
        if(toRemove->vic.size() == 1){
            toReach.push_back(toRemove);
        }
    }

    for(nodo* i : toReach){
        if(!i->removed){
            cout<<i->value;
        }
    }

}

int GCD(int a, int b){
    while(a != b)
    {
        if(a > b)
            a -= b;
        else
            b -= a;
    }

    return a;
}