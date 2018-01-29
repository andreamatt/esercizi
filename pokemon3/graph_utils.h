//
// Created by andrea on 29/01/2018.
//

#ifndef POKEMON3_GRAPH_UTILS_H
#define POKEMON3_GRAPH_UTILS_H

#include <unordered_set>
#include <vector>
#include <iostream>

using namespace std;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

struct Edge;
struct Node {
    int value;
    vector<Edge> vic;
    bool visited = false;
};

struct Edge {
    //int pokemon;
    Node *to;

    //Node* from;
    //bool visited = false;
    Edge(Node *to) {
        this->to = to;
    }
};

typedef vector<Node> Graph;

struct BCC {
    bool circle = false;
    unordered_set<Node *> nodes;
    Node *first = nullptr;
    unordered_set<Node *> stop_nodes;

    void add(Node *node) {
        if (first == nullptr) {
            first = node;
        }
        nodes.insert(node);
    }

    bool contains(Node *node) {
        return nodes.find(node) != nodes.end();
    }
};

/**
 * Finds the start-stop nodes of BCC
 */
void findStartStopNodes(BCC &bcc) {
    for (Node *node : bcc.nodes) {
        int amount = 0;
        for (Edge e : node->vic) {
            if (bcc.contains(e.to)) {
                amount++;
            }
        }
        if (amount > 2) {
            bcc.stop_nodes.insert(node);
        }
    }
    bcc.circle = bcc.stop_nodes.size() == 0;
}

Node* nextNode(Node *current, BCC &bcc){
    for(Edge e : current->vic){
        Node *v = e.to;
        if(bcc.contains(v) && v->visited == false){
            return v;
        }
    }
    cerr<<"Failed to find next node. Current: "<<current->value<<endl;
}

int countFromHere(Node *node, BCC &bcc){
    if(bcc.stop_nodes.find(node) != bcc.stop_nodes.end()){
        return 0;
    }
    node->visited = true;
    Node *next = nextNode(node, bcc);
    return 1 + countFromHere(next, bcc);
}

int gcd(BCC &bcc) {
    if(bcc.circle){
        return bcc.nodes.size();
    }
    int current_gcd = 0;

    // for each start-stop point, count gcd to another one
    for(Node *node : bcc.stop_nodes){
        // start from non-visited neighb

        node->visited = true;

    }
}




#endif //POKEMON3_GRAPH_UTILS_H
