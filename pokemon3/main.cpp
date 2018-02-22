#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <unordered_set>
#include "graph_utils.h"

using namespace std;

int main() {

    for (int quale = 15; quale <= 20; quale++) {
        string inName = "in-out/input" + to_string(quale) + ".txt";
        //string inName = "input.txt";
        ifstream input(inName);
        unsigned int N, M;
        input >> N >> M;
        Graph graph(N);
        for (int i = 0; i < N; i++) {
            graph[i].value = i;
        }

        for (int i = 0; i < M; i++) {
            int from, to;
            input >> from >> to;
            graph[from].vic.push_back(Edge(&graph[to]));
            graph[to].vic.push_back(Edge(&graph[from]));

        }

        int pokemon_num = pokemon_number(graph);

        string outName = "in-out/output" + to_string(quale) + ".txt";
        ifstream actualOutput(outName);
        int actualGCD;
        actualOutput >> actualGCD;
        cout << quale << " Mine: " << pokemon_num << ",   Actual: " << actualGCD << endl;
    }
    return 0;
}

