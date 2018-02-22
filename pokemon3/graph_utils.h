//
// Created by andrea on 29/01/2018.
//

#ifndef POKEMON3_GRAPH_UTILS_H
#define POKEMON3_GRAPH_UTILS_H

#include <unordered_set>
#include <vector>
#include <iostream>
#include <stack>
#include <climits>

using namespace std;

int GCD(int a, int b) {
    return b == 0 ? a : GCD(b, a % b);
}

struct Edge;
struct Node {
    int value;
    vector<Edge> vic;
    bool visited = false;

    // BCC stuff
    int L=INT_MAX, D;
    Node* parent;

    void setLD(int &time){
        // do stuff
    }
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
struct BCC;

typedef vector<Node> Graph;
void resetVisited(Graph &graph){
    for(auto& n : graph){
        n.visited = false;
    }
}
struct BCC {
    bool circle = false;
    unordered_set<Node *> nodes;
    Node *first = nullptr;
    unordered_set<Node *> stop_nodes;

    string toString(){
        string result = "";
        for(Node* n : nodes){
            result = result + to_string(n->value) + ", ";
        }
        return result;
    }

    string toStringSS(){
        string result = "";
        for(Node* n : stop_nodes){
            result = result + to_string(n->value) + ", ";
        }
        return result;
    }

    void add(Node *node) {
        if (first == nullptr) {
            first = node;
        }
        nodes.insert(node);
    }

    bool contains(Node *node) {
        return nodes.find(node) != nodes.end();
    }

    void resetVisited(){
        for(Node *node : nodes){
            node->visited = false;
        }
    }

    void findStartStopNodes() {
        for (Node *node : nodes) {
            int amount = 0;
            for (Edge e : node->vic) {
                if (contains(e.to)) {
                    amount++;
                }
            }
            if (amount > 2) {
                //cout<<"Found ss-node: "<<node->value<<endl;
                stop_nodes.insert(node);
            }
        }
        circle = stop_nodes.empty();
        //cout<<stop_nodes.size()<<endl;
    }

    Node* nextNode(Node *current){
        for(Edge e : current->vic){
            Node *v = e.to;
            if(contains(v) && !v->visited){
                return v;
            }
        }
        cerr<<"Failed to find next node. Current: "<<current->value<<endl;
        return nullptr;
    }

    int countFromHere(Node *node){
        if(stop_nodes.find(node) != stop_nodes.end()){
            return 0;
        }
        node->visited = true;
        Node *next = nextNode(node);
        return 1 + countFromHere(next);
    }

    int gcd(){
        // prepare start-stop nodes
        findStartStopNodes();

        // circle is easy
        if(circle){
            //cout<<"Circle lel"<<endl;
            return nodes.size();
        }

        // general case
        // for each start-stop point, count gcd to another one
        int current_gcd = 0;
        for(Node *start : stop_nodes){
            //cout<<"Start: "<<start->value<<endl;
            // start from non-visited neighbours
            start->visited = true;
            for(Edge e : start->vic){
                if(!e.to->visited){
                    //cout<<"Direction: "<<e.to->value<<", len: ";
                    int length = 1+countFromHere(e.to);
                    //cout<<length<<endl;
                    current_gcd = GCD(current_gcd, length);
                }
            }
        }
        resetVisited();
        return current_gcd;
    }
};

void findBCCs(Node *u, stack<pair<Node *, Node *>> &edges, vector<BCC> &BCCs, int time) {
    //dbgBCC<<"In: "<<u->value<<endl;
    u->D = u->L = time + 1;
    time++;
    u->visited = true;
    int children = 0;
    for (Edge e : u->vic) {
        Node* v = e.to;
        if (!v->visited) {
            //dbgBCC<<"Edge: "<<u->value<<" - "<<v->value<<endl;
            children++;
            // push edge(u, v) to stack
            edges.push(make_pair(u, v));
            v->parent = u;
            findBCCs(v, edges, BCCs, time);
            u->L = min(u->L, v->L);
            if ((u->parent == nullptr && children > 1) || (u->parent != nullptr && v->L >= u->D)) {
                BCC bccTemp;
                while (!(edges.top().first == u && edges.top().second == v)) {
                    // print last element
                    //dbgBCC<<edges.top().first->value<<" - "<<edges.top().second->value<<endl;
                    bccTemp.add(edges.top().first);
                    bccTemp.add(edges.top().second);
                    edges.pop();
                }
                //dbgBCC<<edges.top().first->value<<" - "<<edges.top().second->value<<"  (last)"<<endl;
                bccTemp.add(edges.top().first);
                bccTemp.add(edges.top().second);
                edges.pop();
                //dbgBCC<<"Found a bic"<<endl;
                // we only care about size>2 BCCs
                if (bccTemp.nodes.size() > 2) {
                    BCCs.push_back(bccTemp);
                }
            }

        } else if (u->parent != v && v->D < u->D) {
            u->L = min(u->L, v->D);
            edges.push(make_pair(u, v));
        }
    }
    //dbgBCC<<"Out: "<<u->value<<endl;
}

vector<BCC> getBCCs(Graph &grafo) {

    vector<BCC> BCCs;

    for (int i = 0; i < grafo.size(); i++) {
        if (!grafo[i].visited) {
            stack<pair<Node *, Node *>> stack1;
            findBCCs(&grafo[i], stack1, BCCs, 0);

            BCC bccTemp;
            while (!stack1.empty()) {
                //dbgBCC<<stack1.top().first->value<<" - "<<stack1.top().second->value<<"  (BC)"<<endl;
                bccTemp.add(stack1.top().first);
                bccTemp.add(stack1.top().second);
                stack1.pop();
            }
            //dbgBCC<<endl;
            // we only care about size>2 BCCs
            if (bccTemp.nodes.size() > 2) {
                BCCs.push_back(bccTemp);
            }
        }
    }
    resetVisited(grafo);
    return BCCs;
}



int pokemon_number(Graph &graph){
    int finalGCD = 0;
    vector<BCC> BCCs = getBCCs(graph);
    for(auto &bcc : BCCs){
        //cout<<"BCC ("<<bcc.nodes.size()<<"): "<<endl<<bcc.toString()<<endl;
        //cout<<"ss-nodes: ("<<bcc.stop_nodes.size()<<"): "<<endl<<bcc.toStringSS()<<endl<<endl;
        finalGCD = GCD(finalGCD, bcc.gcd());
    }
    return finalGCD;
}


#endif //POKEMON3_GRAPH_UTILS_H
