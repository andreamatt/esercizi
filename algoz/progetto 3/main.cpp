#include <fstream>
#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

struct Node {
    int id;
    vector<Node *> vic;
    bool visited = false;
    bool removed = false;
};

void dfs(unordered_set<int> &result, Node *n, int prec);

int main() {

    ifstream input("input.txt");
    int N, M;
    input >> N >> M;
    vector<Node> graph(N);
    for (int i = 0; i < N; i++)
        graph[i].id = i;

    for (int i = 0; i < M; i++) {
        int from, to;
        input >> from >> to;
        graph[from].vic.push_back(&graph[to]);
        graph[to].vic.push_back(&graph[from]);
    }

    unordered_set<int> result;
    for (int i = 0; i < N; i++)
        if (graph[i].visited == false)
            dfs(result, &graph[i], -1);

    ofstream output("output.txt");
    output << result.size() << " ";
    cout<<"Solution: "<<result.size()<<endl;
    for (int n : result) {
        //cout << n << ", ";
        output << n << " ";
    }
    output << "#";
    //cout << endl;

    return 0;
}

void dfs(unordered_set<int> &result, Node *n, int prec) {
    n->visited = true;

    for (Node *v : n->vic) {
        if (!n->removed) {
            if (v->visited) {
                if (v->id != prec){
                    result.insert(v->id);
                    v->removed = true;
                }
            } else {
                dfs(result, v, n->id);
            }
        }
    }
}
