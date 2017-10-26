#include <iostream>
using namespace std;

struct Tree{
    Tree* left;
    Tree* right;
    int leaves;
    int degree;

    Tree(){
        left = nullptr;
        right = nullptr;
        leaves = 0;
        degree = 0;
    }

    int maxDegree(){
        if(left == nullptr && right == nullptr){
            leaves = 1;
            return 0;
        }
        else{
            int dx=0, sx=0, Mdx=0, Msx=0;
            if(left != nullptr){
                Msx = left->maxDegree();
                sx = left->leaves;
            }
            if(right != nullptr){
                Mdx = right->maxDegree();
                dx = right->leaves;
            }
            leaves = sx + dx;
            degree = abs(sx-dx);
            return max(degree, max(Mdx, Msx));
        }
    }

};

int main() {

    Tree* mainT = new Tree();
    mainT->left = new Tree();
    mainT->right = new Tree();
    Tree* newT = new Tree();
    newT->right = mainT;
    newT->left = new Tree();
    mainT = newT;
    newT = new Tree();
    newT->right = new Tree();
    newT->left = new Tree();
    Tree* final = new Tree();
    final->left = mainT;
    final->right = newT;

    cout<<final->maxDegree();


    return 0;
}

