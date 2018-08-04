// Esercizio 3 compito 15-11-05

#include <iostream>
#include <vector>

using namespace std;

struct Tree{
    char type;
    Tree* left;
    Tree* right;
    Tree(){
        type = 'L';
        left = nullptr;
        right = nullptr;
    }
    Tree(Tree* left, Tree* right){
        type = 'I';
        this->left = left;
        this->right = right;
    }
};

string preOrder(Tree* tree){
    return (tree->type == 'L') ? "L" : "I" + preOrder(tree->left) + preOrder(tree->right);
}

string postOrder(Tree* tree){
    return (tree->type == 'L') ? "L" : postOrder(tree->left) + postOrder(tree->right) + "I";
}

string inOrder(Tree *tree){
    return (tree->type == 'L') ? "L" : inOrder(tree->left) + "I" + inOrder(tree->right);
}

bool bilanciata(string);
Tree* buildTree(string preVisit, int& position);
Tree* buildTreePost(string postVisit, int& position);
int depth(Tree* tree);

int main(){

    Tree* root = new Tree(new Tree(), new Tree(new Tree(new Tree(), new Tree()), new Tree()));

    int position = 0;
    cout<<"Pre:  "<<preOrder(root)<<endl<<"In:   "<<inOrder(root)<<endl<<"Post: "<<postOrder(root)<<endl;

    return 0;
}

// bilanciata:
//  w è una stringa vuota
//  w = (x), x bilanciata
//  w = xy, x e y bilanciate (())(())

// cout<<bilanciata("((())(())(()))(()()()((())))");

bool bilanciata(string w){
    if(w == ""){
        return true;
    }

    int opening = 0;
    for(int i=0; i<w.size(); i++){
        if(w[i] == '('){
            opening++;
        }
        else{
            opening--;
        }
        if(opening < 0){
            return false;
        }
        if(opening == 0){
            if(i == w.size()-1){
                return bilanciata(w.substr(1, w.size()-2));
            }
            int leftLen = i+1;
            int rightLen = w.size() - leftLen;
            return bilanciata(w.substr(0, leftLen)) && bilanciata(w.substr(i+1, rightLen));
        }
    }
    return false;
}

Tree* buildTree(string preVisit, int& position){
    return (preVisit[++position-1] == 'L') ? new Tree() : new Tree(buildTree(preVisit, position), buildTree(preVisit, position));
}

Tree* buildTreePost(string postVisit, int& position){
    if(postVisit[position] == 'L'){
        position--;
        return new Tree();
    }
    else{
        position--;
        Tree* right = buildTreePost(postVisit, position);
        Tree* left = buildTreePost(postVisit, position);
        return new Tree(left, right);
    }
}

int depth(Tree* tree){
    return (tree == nullptr) ? -1 : 1 + max(depth(tree->left), depth(tree->right));
}