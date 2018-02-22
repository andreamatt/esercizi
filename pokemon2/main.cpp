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
    vector<nodo *> vic;
    vector<int> pokemon;

    int vicInThisBBC(unordered_set<nodo*>& BCC){
        int result = 0;
        for(nodo* v : this->vic){
            if(BCC.find(v) != BCC.end()){
                result++;
            }
        }
        return result;
    }
};

int GCD(int a, int b);
int GCDFromHere(nodo *start, unordered_set<nodo *> &comp);
int lenFrom(nodo* start, unordered_set<nodo*>& comp);
void findBCCs(nodo *u, stack<pair<nodo *, nodo *>> &edges, vector<unordered_set<nodo *>> &BCCs, int time);
vector<unordered_set<nodo *>> biconnected_components(vector<nodo> &grafo);

//ofstream //dbgout("//dbgout.txt");
//ofstream //dbgBCC("//dbgBCC.txt");

int main() {

    for(int quale = 0; quale<=0; quale++) {
        //string inName = "input" + to_string(quale) + ".txt";
        string inName = "input.txt";
        ifstream input(inName);
        //string outName = "output" + to_string(quale) + ".txt";   ifstream actualOutput(outName);   int actualGCD;  actualOutput >> actualGCD;

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
            grafo[from].vic.push_back(&grafo[to]);
            grafo[from].pokemon.push_back(-1);
            grafo[to].vic.push_back(&grafo[from]);
            grafo[to].pokemon.push_back(-1);
        }

        // step 1
        //removeSingles(grafo);

        // step 2
        vector<unordered_set<nodo *>> BCCs = biconnected_components(grafo);
        //cout<<"BCCs: "<<BCCs.size()<<endl;
        for(int i=0; i<grafo.size(); i++){
            grafo[i].visited = false;
        }

        // step 3
        int currentGCD = -1;
        if (BCCs.size() == 0) {
            currentGCD = 1;
        } else {
            bool firstBCC = true;
            for (int i = 0; i < BCCs.size(); i++) {
                int GCDinBCC;
                bool first = true;
                //cout<<endl<<"BCC "<<i<<" :"<<endl;
                for (nodo *n : BCCs[i]) {
                    //cout<<n->value<<" ";
                    int temp;
                    if(n->vicInThisBBC(BCCs[i]) > 2){
                        temp = GCDFromHere(n, BCCs[i]);
                        if(temp != -1){
                            //cout<<"Got: "<<temp<<endl;
                            if(first){
                                first = false;
                                GCDinBCC = temp;
                            }
                            else{
                                GCDinBCC = GCD(GCDinBCC, temp);
                            }
                        }
                    }
                }
                if(first){
                    GCDinBCC = BCCs[i].size();
                }

                // reset all visited
                for (nodo *n : BCCs[i]) {
                    n->visited = false;
                }

                if(firstBCC){
                    firstBCC = false;
                    currentGCD = GCDinBCC;
                }
                else{
                    currentGCD = GCD(currentGCD, GCDinBCC);
                }
            }
        }


        //cout << quale << " Mine: " << currentGCD << ",   Actual: " << actualGCD << endl;
        ofstream output("output.txt");    output<<currentGCD<<endl;
    }

    return 0;
}