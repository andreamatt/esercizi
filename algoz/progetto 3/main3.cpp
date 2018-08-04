#include <fstream>
#include <iostream>
#include <limits.h>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

struct Node {
    int id = 0;
    int level = 0;
    int n_vic = 0;

    vector<Node *> vic;

    bool visited = false;
    bool removed = false;
};

void solve(vector<Node> &graph, unordered_set<int> &removed);
void dfs(Node *n, Node *last);
void print_removed(unordered_set<int> &removed) {
    cout << "Removed: " << removed.size() << endl;
    for (int i : removed) {
        cout << i << " ";
    }
    cout << endl;
}

ifstream in("input.txt");
ofstream out("output.txt");

int main() {
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

    /* insert values */
    for (int k = 0; k < N; k++) {
        graph[k].id = k;
        graph[k].n_vic = graph[k].vic.size();
    }

    //cout << "Starting" << endl;
    ofstream output("output.txt");
    unordered_set<int> removed;
    solve(graph, removed);
    cout << "\nSolution: "<< removed.size() <<"\n";
    output << removed.size() << " ";
    for (int i : removed) {
        //cout << i << " ";
        output << i << " ";
    }
    output << "#";
    //cout << endl;

    return 0;
}

void solve(vector<Node> &graph, unordered_set<int> &removed) {
    //cout << "___________________________"<<endl;
    for (int i = 0; i < graph.size(); i++) {
        if (!graph[i].visited && !graph[i].removed)
            dfs(&graph[i], nullptr);
    }

    int max_lvl = 0;
    int max_vic = 0;
    for (Node n : graph) {
        if (n.level > max_lvl) {
            max_lvl = n.level;
            max_vic = n.n_vic;
        } else if (n.level == max_lvl) {
            max_vic = max(max_vic, n.n_vic);
        }
    }

    if (max_lvl == 0) {
        // CASO BASE
        for (int i = 0; i < graph.size(); i++) {
            graph[i].visited = false;
            graph[i].level = 0;
            // QUALCOSA SUI N_VIC ?!?!?!?! NON PENSO: NON HO MODIFICATO N_VIC
        }
        //cout << "..........................."<<endl;
        return;
    }

    unordered_set<int> removable;
    for (Node n : graph) {
        if (n.level == max_lvl && n.n_vic == max_vic) {
            removable.insert(n.id);
        }
    }

    for (int i = 0; i < graph.size(); i++) {
        graph[i].visited = false;
        graph[i].level = 0;
    }

    int best_node;
    int min_removed = INT_MAX;
    for (int n : removable) {
        graph[n].removed = true;
        for (Node *v : graph[n].vic) {
            v->n_vic--;
        }
        unordered_set<int> rem_tmp;
        rem_tmp.insert(n);
        solve(graph, rem_tmp);
        if (rem_tmp.size() < min_removed) {
            min_removed = rem_tmp.size();
            best_node = n;
        }
        graph[n].removed = false;
        for (Node *v : graph[n].vic) {
            v->n_vic++;
        }
    }

    // SO QUAL E' IL MIGLIORA
    //unordered_set<int> removed;
    graph[best_node].removed = true;
    for (Node *v : graph[best_node].vic) {
        v->n_vic--;
    }
    removed.insert(best_node);
    solve(graph, removed);
    graph[best_node].removed = false;
    for (Node *v : graph[best_node].vic) {
        v->n_vic--;
    }
    removed.insert(best_node);

    //cout << "..........................."<<endl;
}

void dfs(Node *n, Node *last) {
    n->visited = true;
    //cout << n.value << endl;

    for (Node *v : n->vic) {
        if (!v->removed) {
            if (v->visited) {
                if (v != last) {
                    v->level++;
                }
            } else {
                dfs(v, n);
            }
        }
    }
}
