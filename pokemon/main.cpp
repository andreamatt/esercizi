#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_set>
#include <stack>

using namespace std;

struct nodo {
    bool visited = false;
    bool removed = false;
    bool starter = false;
    int disc = -1;
    int low = -1;
    nodo *parent = nullptr;
    bool isArticulation;
    int value;
    unordered_set<nodo *> vic;
};

void removeSingles(vector<nodo> &);
int GCD(int a, int b);
void findBCCs(nodo *u, stack<pair<nodo *, nodo *>> &edges, vector<unordered_set<nodo *>> &BCCs, int time);
vector<unordered_set<nodo *>> biconnected_components(vector<nodo> &grafo);
int GCDFromHere(nodo *start, unordered_set<nodo *> &comp);
int lenFrom(nodo* start, unordered_set<nodo*>& comp);

//ofstream //dbgout("//dbgout.txt");
//ofstream //dbgBCC("//dbgBCC.txt");

int main() {

    for(int quale = 0; quale<=20; quale++) {
        string inName = "input" + to_string(quale) + ".txt";
        string outName = "output" + to_string(quale) + ".txt";
        ifstream input(inName);
        ifstream actualOutput(outName);
        int actualGCD;
        actualOutput >> actualGCD;

        int N, M;
        input >> N >> M;

        vector<nodo> grafo;
        grafo.resize(N);
        for (int i = 0; i < N; ++i) {
            grafo[i].value = i;
        }
        for (int i = 0; i < M; ++i) {
            int from, to;
            input >> from >> to;
            grafo[from].vic.insert(&grafo[to]);
            grafo[to].vic.insert(&grafo[from]);
        }

        // step 1
        //removeSingles(grafo);

        // step 2
        vector<unordered_set<nodo *>> BCCs = biconnected_components(grafo);
        cout<<"BCCs: "<<BCCs.size()<<endl;
        for(int i=0; i<grafo.size(); i++){
            grafo[i].visited = false;
        }

        // step 3
        int currentGCD = -1;
        bool first = true;
        if (BCCs.size() == 0) {
            currentGCD = 1;
        } else {
            for (int i = 0; i < BCCs.size(); i++) {
                for (nodo *n : BCCs[i]) {
                    if (!n->visited) {
                        int result = GCDFromHere(n, BCCs[i]);
                        if (result != -1) {
                            if (first) {
                                currentGCD = result;
                                first = false;
                            } else {
                                currentGCD = GCD(currentGCD, result);
                            }
                        }
                    }
                }

                // reset all visited
                for (nodo *n : BCCs[i]) {
                    n->visited = false;
                }
            }
        }


        cout << quale << " Mine: " << currentGCD << ",   Actual: " << actualGCD << endl;

        //ofstream output("output.txt");
        //output<<currentGCD<<endl;
    }

    return 0;
}

int lenFrom(nodo* start, unordered_set<nodo*>& comp){
    //dbgout<<"lenFrom: "<<start->value<<" ||  ";
    // assuming i either have a direction
    // or i should stop
    vector<nodo*> possibleVic;
    for(nodo* v : start->vic){
        if(comp.find(v) != comp.end()){
            possibleVic.push_back(v);
        }
    }

    nodo* next;
    if(possibleVic.size() == 2){
        start->visited = true;
        // choose the not visited
        if(!possibleVic[0]->visited){
            next = possibleVic[0];
        }
        else if(!possibleVic[1]->visited){
            next = possibleVic[1];
        }
        else{
            // both visited => return
            //dbgout<<endl;
            return 0;
        }

        return 1 + lenFrom(next, comp);
    }
    else{
        //dbgout<<endl;
        return 0;
    }
}

int GCDFromHere(nodo *start, unordered_set<nodo *> &comp) {
    //dbgout<<"GCDFrom: "<<start->value<<endl;
    vector<nodo *> vicInThis;
    for (nodo* v : start->vic) {
        if (comp.find(v) != comp.end()) {
            vicInThis.push_back(v);
        }
    }

    if(vicInThis.size() == 2){
        start->visited = true;
        int len = 2;
        if(!vicInThis[0]->visited){
            len += lenFrom(vicInThis[0], comp);
        }
        if(!vicInThis[1]->visited){
            len += lenFrom(vicInThis[1], comp);
        }
        //dbgout<<" 2V "<<len<<endl;
        return len;
    }

    else{
        start->visited = true;
        bool first = true;
        int currentGCD;
        for(nodo* v : vicInThis){
            if(!v->visited){
                int len = lenFrom(v, comp) +1;
                if(first){
                    currentGCD = len;
                    first = false;
                }
                else{
                    currentGCD = GCD(currentGCD, len);
                }
            }
        }

        if(first){
            currentGCD = -1;
        }

        //dbgout<<currentGCD<<endl;
        start->visited = false;
        return currentGCD;
    }
}


void findBCCs(nodo *u, stack<pair<nodo *, nodo *>> &edges, vector<unordered_set<nodo *>> &BCCs, int time) {
    //dbgBCC<<"In: "<<u->value<<endl;
    u->disc = u->low = time + 1;
    time++;
    u->visited = true;
    int children = 0;
    for (nodo *v : u->vic) {
        if (v->visited == false) {
            //dbgBCC<<"Edge: "<<u->value<<" - "<<v->value<<endl;
            children++;
            // push edge(u, v) to stack
            edges.push(make_pair(u, v));
            v->parent = u;
            findBCCs(v, edges, BCCs, time);
            u->low = min(u->low, v->low);
            if ((u->parent == nullptr && children > 1) || (u->parent != nullptr && v->low >= u->disc)) {
                unordered_set<nodo *> bccTemp;
                while (!(edges.top().first == u && edges.top().second == v)) {
                    // print last element
                    //dbgBCC<<edges.top().first->value<<" - "<<edges.top().second->value<<endl;
                    bccTemp.insert(edges.top().first);
                    bccTemp.insert(edges.top().second);
                    edges.pop();
                }
                //dbgBCC<<edges.top().first->value<<" - "<<edges.top().second->value<<"  (last)"<<endl;
                bccTemp.insert(edges.top().first);
                bccTemp.insert(edges.top().second);
                edges.pop();
                //dbgBCC<<"Found a bic"<<endl;
                if (bccTemp.size() > 2) {
                    BCCs.push_back(bccTemp);
                }
            }

        } else if (u->parent != v && v->disc < u->low) {
            u->low = min(u->low, v->disc);
            edges.push(make_pair(u, v));
        }
    }
    //dbgBCC<<"Out: "<<u->value<<endl;
}

vector<unordered_set<nodo *>> biconnected_components(vector<nodo> &grafo) {

    vector<unordered_set<nodo *>> BCCs;

    for (int i = 0; i < grafo.size(); i++) {
        if (grafo[i].visited == false) {
            stack<pair<nodo *, nodo *>> stack1;
            findBCCs(&grafo[i], stack1, BCCs, 0);

            unordered_set<nodo *> bccTemp;
            while (!stack1.empty()) {
                //dbgBCC<<stack1.top().first->value<<" - "<<stack1.top().second->value<<"  (BC)"<<endl;
                bccTemp.insert(stack1.top().first);
                bccTemp.insert(stack1.top().second);
                stack1.pop();
            }
            //dbgBCC<<endl;
            if (bccTemp.size() > 2) {
                BCCs.push_back(bccTemp);
            }
        }
    }

    return BCCs;
}

void removeSingles(vector<nodo> &grafo) {
    vector<nodo *> toReach;
    for (int i = 0; i < grafo.size(); i++) {
        if (grafo[i].vic.size() <= 1) {
            toReach.push_back(&grafo[i]);
            //cout<<"Removing: "<<grafo[i].value<<endl;
        }
    }

    for (int i = 0; i < toReach.size(); i++) {
        toReach[i]->visited = true;
        toReach[i]->removed = true;
        nodo *toRemove = nullptr;
        for (nodo *v : toReach[i]->vic) {
            toRemove = v;
        }
        toRemove->vic.erase(toReach[i]);
        toReach[i]->vic.erase(toRemove);
        if (toRemove->vic.size() <= 1) {
            toReach.push_back(toRemove);
        }
    }

}

int GCD(int a, int b) {
    while (a != b) {
        if (a > b)
            a -= b;
        else
            b -= a;
    }

    return a;
}