#include <fstream>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

struct Node {
    int id = 0;
    int level = 0;

    vector<Node *> vic;
    int n_vic = 0;

    bool visited = false;
    bool removed = false;
};

void resetGraph(vector<Node> &graph);
void dfs(Node *n, int parent);

int main(int argc, char* argv[]) {
    //string in_f = string("input/input") + argv[1] + ".txt";
    string in_f = "input.txt";
    ifstream in(in_f);
    ofstream out("output.txt");
    vector<Node> graph;

    unsigned int N, M;
    in >> N >> M;
    graph.resize(N);

    /* push nodes */
    int from, to;
    for (int i = 0; i < M; i++) {
        in >> from >> to;
        graph[from].vic.push_back(&graph[to]);
        graph[to].vic.push_back(&graph[from]);
    }

    /* insert ids */
    for (int k = 0; k < N; k++) {
        graph[k].id = k;
        graph[k].n_vic = graph[k].vic.size();
    }

    unordered_set<int> solution;
    Node *tmpNode;
    int maxLevel=0;

    /* repeat dfs() until no nodes with level>1 are found */
    do {
        for (int k = 0; k < N; k++) {
            if ((!graph[k].visited) && (!graph[k].removed)) {
                dfs(&graph[k], -1);
            }
        }
        /* get biggest level node in set and delete it */
        int to_rem = -1;
        int max_lvl = -1;
        for (Node n : graph) {
            if (!n.removed) {
                if (n.level > max_lvl) {
                    max_lvl = n.level;
                    to_rem = n.id;
                } else if(n.level == max_lvl && n.n_vic > graph[to_rem].n_vic){
                    to_rem = n.id;
                }
            }
        }

        //cout << "Max_lvl " << max_lvl << endl;

        if (max_lvl == -1) {
            // no cycles
            break;
        }

        /* remove it from graph */
        graph[to_rem].removed = true;
        solution.insert(to_rem);
        for (Node *v : graph[to_rem].vic) {
            v->n_vic--;
        }

        /* reset visited, deactivated and level */
        resetGraph(graph);
    } while (true);

    cout<<"Solution: "<<solution.size()<<endl;

    return 0;
}

void dfs(Node *n, int parent) {
    n->visited = true;
    //cout << n.id << endl;

    for (Node *v : n->vic) {
        if (!v->removed) {
            if (!v->visited) {
                dfs(v, n->id);
            } else {
                if (v->id != parent) {
                    v->level++;
                }
            }
        }
    }
}

void resetGraph(vector<Node> &graph) {
    for (auto &node : graph) {
        node.visited = false;
        node.level = 0;
    }
}


