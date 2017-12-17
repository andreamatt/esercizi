#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <set>
#include <climits>
#include <ctime>
#include <stack>

using namespace std;

struct edge{
    int to;
    int l;
    int i, j, k;
};

struct node {
    vector<edge> vic;
    int value;
    int parent = -1;
};

int timeToCross(int time, int l, int i, int j, int k);
void dijkstraWithTime(vector<node> &graph);

int main() {

    ifstream input("input.txt");
    int N, M;
    input >> N >> M;
    vector<node> graph(N);
    for (int i = 0; i < N; i++) {
            graph[i].value = i;
        }
        for (int a = 0; a < M; a++) {
            int from, to, l, i, j, k;
            input >> from >> to >> l >> i >> j >> k;
            if (l <= j) {
                edge from_to;
                edge to_from;
                from_to.to = to;
                to_from.to = from;
                from_to.i = to_from.i = i;
                from_to.j = to_from.j = j;
                from_to.k = to_from.k = k;
                from_to.l = to_from.l = l;
                graph[from].vic.push_back(from_to);
                graph[to].vic.push_back(to_from);
            }
        }

    dijkstraWithTime(graph);

    return 0;
}

void dijkstraWithTime(vector<node> &graph) {
    int N = graph.size();
    vector<int> times(N, INT_MAX);
    set<pair<int, int>> nodes;
    times[0] = 0;
    nodes.insert(make_pair(0, 0));

    while (!nodes.empty()) {
        pair<int, int> p = *nodes.begin();
        nodes.erase(p);
        node *n = &graph[p.second];
        for (int a = 0; a < n->vic.size(); a++) {
            node *v = &graph[n->vic[a].to];
            int oldTime = times[v->value];
            int n_time = times[n->value], l = n->vic[a].l, i = n->vic[a].i, j = n->vic[a].j, k = n->vic[a].k;
            int newTime = n_time + timeToCross(n_time, l, i, j, k);
            if (newTime < oldTime) {
                if(oldTime != INT_MAX){
                    nodes.erase(make_pair(oldTime, v->value));
                }
                times[v->value] = newTime;
                nodes.insert(make_pair(newTime, v->value));
                v->parent = n->value;
            }
        }

    }

    ofstream output("output.txt");
    if(times[N-1] == INT_MAX){
        output<<-1<<endl;
    }
    else{
        output<<times[N-1]<<endl;
        stack<int> path;
        int current = N-1;
        while(current != -1){
            path.push(current);
            current = graph[current].parent;
        }

        while(!path.empty()){
            output<<path.top()<<endl;
            path.pop();
        }
    }
}

int timeToCross(int time, int l, int i, int j, int k) {
    if (time < i) {
        return i - time + l;
    } else {
        int relativeTime = (time - i) % (j + k);
        if (relativeTime + l <= j) {
            return l;
        } else {
            return (j + k) - relativeTime + l;
        }
    }
}
