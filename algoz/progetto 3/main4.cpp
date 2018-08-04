#include <fstream>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

struct Node {
    int id = 0;
    int level = 0;

    vector<Node *> vic;
    int n_vic = 0;

    bool visited = false;
    bool removed = false;
    bool deactivated = false;
};

void bfs(vector<Node> &graph, int start);
void reset_visited(vector<Node> &graph) {
    for (int i = 0; i < graph.size(); i++)
        graph[i].visited = false;
}
void reset_lvl(vector<Node> &graph) {
    for (int i = 0; i < graph.size(); i++)
        graph[i].level = 0;
}

bool has_cycle_rec(Node *n, int parent) {
    n->visited = true;
    for (Node *v : n->vic) {
        if (!v->removed) {
            if (!v->visited) {
                if (has_cycle_rec(v, n->id))
                    return true;
            } else if (v->id != parent) {
                return true;
            }
        }
    }
    return false;
}

bool has_cycle(vector<Node> &graph) {
    for (int n = 0; n < graph.size(); n++) {
        if (!graph[n].visited && !graph[n].removed) {
            if (has_cycle_rec(&graph[n], -1)) {
                return true;
            }
        }
    }
    return false;
}

int main(int argc, char *argv[]) {
    //string in_f = string("input/input") + argv[1] + ".txt";
    string in_f = "input.txt";
    ifstream in(in_f);
    ofstream out("output.txt");

    int N, M;
    in >> N >> M;
    vector<Node> graph(N);

    /* push nodes */
    int from, to;
    for (int i = 0; i < M; i++) {
        in >> from >> to;
        graph[from].vic.push_back(&graph[to]);
        graph[to].vic.push_back(&graph[from]);
    }

    /* insert ids */
    for (unsigned int k = 0; k < N; k++) {
        graph[k].id = k;
        graph[k].n_vic = graph[k].vic.size();
    }

    set<int> solution;
    int maxLevel;

    do {
        for (int i = 0; i < N; i++) {
            if (!graph[i].removed) {
                bfs(graph, i);
                //cout << "Done bfs " << i << endl;
                // reset visited
                reset_visited(graph);
            }
        }
        /* get biggest level node in set and delete it */
        int to_rem = -1;
        int max_lvl = 0;
        for (Node n : graph) {
            if (!n.removed) {
                if (n.level > max_lvl) {
                    max_lvl = n.level;
                    to_rem = n.id;
                }
            }
        }

        int quanti = 0;
        for (Node n : graph)
            quanti += max_lvl == n.level;

        reset_lvl(graph);

        //cout << "Max_lvl " << max_lvl << endl;

        if (max_lvl == 0) {
            // no cycles
            break;
        } else {
            //cout << quanti << " reached max_lvl\n";
        }

        /* remove it from graph */
        graph[to_rem].removed = true;
        solution.insert(to_rem);
        for (Node *v : graph[to_rem].vic) {
            v->n_vic--;
        }

        //cout << "Removed " << to_rem << "\n\n";

    } while (true);

    cout << "Solution: " << solution.size() << endl;
    out << solution.size() << " ";
    for (int n : solution) {
        //cout << n << ", ";
        out << n << " ";
    }
    cout << endl;
    out << "#";

    if (has_cycle(graph)) {
        cout << "\nStill has cycle WTF\n";
    }

    return 0;
}

void bfs(vector<Node> &graph, int start) {
    vector<pair<int, int>> nodes;
    nodes.push_back({start, -1});
    graph[start].visited = true;
    for (int i = 0; i < nodes.size(); i++) {
        int n = nodes[i].first;
        int who_added_n = nodes[i].second;
        for (Node *v : graph[n].vic) {
            if (!v->removed) {
                if (v->visited) {
                    if (v->id != who_added_n) {
                        //v->level++;
                        graph[n].level++;
                    }
                } else {
                    nodes.push_back({v->id, n});
                    v->visited = true;
                }
            }
        }
    }
}