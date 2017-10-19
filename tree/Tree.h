//
// Created by andrea on 18/10/2017.
//

#ifndef TREE_TREE_H
#define TREE_TREE_H

#include <string.h>
#include <iostream>
using namespace std;

struct Tree {
    Tree* parent;
    Tree* rightC;
    Tree* leftC;
    int value;

    Tree(){
        parent = rightC = leftC = nullptr;
        value = 0;
    }

    Tree(int value){
        parent = rightC = leftC = nullptr;
        this->value = value;
    }

    Tree(Tree* parent, int value){
        rightC = leftC = nullptr;
        this->parent = parent;
        this->value = value;
    }

    Tree* addLeftC(Tree* child){
        this->leftC = child;
        child->parent = this;
        return child;
    }

    Tree* addRightC(Tree* child){
        this->rightC = child;
        child->parent = this;
        return child;
    }

    ~Tree(){
        if(leftC != nullptr){
            delete  leftC;
        }
        cout<<"Deleting "<<value<<endl;
        if(rightC != nullptr){
            delete  rightC;
        }
    }

    string toStringIN(){
        string result;
        if(leftC != nullptr){
            result.append(leftC->toStringIN());
        }
        cout<<value<<", ";
        result.append(to_string(value) + ", ");
        if(rightC != nullptr){
            result.append(rightC->toStringIN());
        }
        return result;
    }

    Tree* leftMostC(){
        if(leftC != nullptr){
            return leftC->leftMostC();
        }
        else{
            if(rightC != nullptr){
                return rightC->leftMostC();
            }
            else{
                return this;
            }
        }
    }

    Tree* firstC(){
        if(leftC != nullptr){
            return leftC;
        }
        else if(rightC != nullptr){
            return rightC;
        }
        else{
            return nullptr;
        }
    }

    Tree* rightSibling(){
        if(parent == nullptr){
            return nullptr;
        }
        else{
            if(parent->leftC == this){
                if(parent->rightC != nullptr){
                    return parent->rightC;
                }
            }
            Tree* parentSib = parent->rightSibling();
            if(parentSib == nullptr){
                return nullptr;
            }
            else {
                return parentSib->firstC();
            }
        }
    }

    string toStringBF(){
        string result = to_string(value) + ", ";
        cout<<result;
        Tree* starter;
        if(leftC != nullptr){
            starter = leftC;
        }
        else if(rightC != nullptr){
            starter = rightC;
        }
        while(starter != nullptr){
            result.append(to_string(starter->value) + ", ");
        }
    }

    Tree* insertBRT(int value){
        if(value < this->value){
            if(leftC != nullptr){
                return leftC->insertBRT(value);
            }
            else{
                return addLeftC(new Tree(value));
            }
        }
        else{
            if(rightC != nullptr){
                return rightC->insertBRT(value);
            }
            else{
                return addRightC(new Tree(value));
            }
        }
    }

};


#endif //TREE_TREE_H
