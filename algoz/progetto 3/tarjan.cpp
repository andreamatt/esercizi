#include <fstream>
#include <iostream>
#include <unordered_set>
#include <vector>
#define AP_GID 0

using namespace std;

struct Node {
    int id = 0;
    int level = 0;

    int time = 0;
    int lowTime = 0;
    Node *parent = nullptr;
    int groupID = AP_GID;

    vector<Node *> vic;
    int n_vic = 0;

    bool visited = false;
    bool removed = false;
    bool articulation = false;
};

void remove_leaves(Node *n);
void find_APs(Node *n, int time);
void set_gid(Node *n, int gid);

/*int n_vic(Node* n){
    int r=0;
    for(Node* v : n->vic) r+= !v->removed;
    return r;
}*/

void remove(Node *n){
    n->removed = true;
    for(Node *v : n->vic){
        v->n_vic--;
    }
}

void reset_APs_and_groups(vector<Node> &graph) {
    for (int i = 0; i < graph.size(); i++) {
        graph[i].articulation = false;
        graph[i].groupID = AP_GID;
    }
}

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
    for (int i = 0; i < N; i++) {
        graph[i].id = i;
        graph[i].n_vic = graph[i].vic.size();
    }

    unordered_set<int> solution;
    bool finished = false;
    while(!finished) {
        // REMOVE LEAVES
        for (int i = 0; i < N; i++) {
            if (!graph[i].removed) {
                remove_leaves(&graph[i]);
            }
        }
        reset_visited(graph);

        // FIND APs
        for (int i = 0; i < N; i++) {
            if (!graph[i].visited && !graph[i].removed) {
                find_APs(&graph[i], 0);
            }
        }
        reset_visited(graph);

        // SET GROUP IDs
        int gid = 1;
        for (int i = 0; i < N; i++) {
            if (!graph[i].visited && !graph[i].removed && !graph[i].articulation) {
                set_gid(&graph[i], gid);
                gid++;
            }
        }
        reset_visited(graph);

        // FIND TO_REM
        int max_level = -1;
        int to_rem = -1;
        for (int i = 0; i < N; i++) {
            if (!graph[i].removed) {
                vector<int> vic_gids(gid+1, 0);
                int vic_APs=0;
                for(Node *v : graph[i].vic){
                    if(!v->removed){
                        if(graph[i].articulation){
                            vic_gids[v->groupID]++; // se v è AP incremento di 0
                        } else {
                            if(v->articulation){
                                vic_APs++;
                            } else {
                                vic_gids[v->groupID]++;
                            }
                        }
                    }
                }

                int level = 0;
                for(int l : vic_gids){
                    level = max(level, l);
                }
                level += vic_APs;

                if(level > max_level){
                    max_level = level;
                    to_rem = i;
                } else if (level == max_level){
                    if(graph[i].articulation){
                        to_rem = i;
                    }
                }
            }
        }
        reset_APs_and_groups(graph);

        // REMOVE TO_REM
        if(max_level <= 0 || to_rem == -1){
            finished = true;
        } else {
            solution.insert(to_rem);
            remove(&graph[to_rem]);
        }
    }

    cout << "Solution: "<<solution.size()<<endl;
    out << solution.size() << " ";
    for(int i : solution){
        cout << i <<", ";
        out << i << " ";
    }
    cout <<endl;
    out << "#";

    reset_visited(graph);
    if (has_cycle(graph)) {
        cout << "\nStill has cycle WTF\n";
    }

    return 0;
}

void find_APs(Node *current, int time) {
    // algorithm from wikipedia
    current->visited = true;
    current->time = time;
    current->lowTime = time;
    int childCount = 0;
    bool isArticulation = false;
    for (Node *v : current->vic) {
        if (!v->visited) {
            v->parent = current;
            find_APs(v, time + 1);
            childCount++;
            if (v->lowTime >= current->time) {
                isArticulation = true;
            }
            current->lowTime = min(current->lowTime, v->lowTime);
        } else if (v != current->parent) {
            current->lowTime = min(current->lowTime, v->time);
        }
    }

    if ((current->parent != nullptr && isArticulation) || (current->parent == nullptr && childCount > 1)) {
        //cout<<current->value<<endl;
        current->articulation = true;
    }
}

void remove_leaves(Node *n) {
    if(n->n_vic <= 1){
        remove(n);
        for(Node *v : n->vic){
            if(!v->removed){
                remove_leaves(v);
            }
        }
    }
}

void set_gid(Node *n, int gid) {
    n->visited = true;
    n->groupID = gid;
    for (Node *v : n->vic) {
        if (!v->removed && !v->visited && !v->articulation) {
            set_gid(v, gid);
        }
    }
}
