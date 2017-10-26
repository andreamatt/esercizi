#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <ctime>
#include "helpers.h"

using namespace std;

set<int> allCombsTest(vector<pair<int, char>> seq);
set<int> allCombsTestNew(vector<pair<int, char>> seq);
void allCombs();
void submission();
void testAll(int len);


int main() {

    //testAll(5);
    allCombs();
    //submission();

    return 0;
}

void testAll(int len){
    vector<vector<pair<int, char>>> sequences = allSequences(len);
    ofstream output("output.txt");
    output<<"0 = d,   1 = s"<<endl;
    for(vector<pair<int, char>> seq : sequences){
        clock_t begin1 = clock();
        set<int> resultOld = allCombsTest(seq);
        clock_t end1 = clock();
        set<int> result = allCombsTestNew(seq);
        clock_t end2 = clock();
        for(int i=0; i<seq.size(); i++){
            if((result.find(i) != result.end()) != (resultOld.find(i) != resultOld.end())){
                cout<<"Discrepanzaaaaaa"<<endl;
            }
            //cout<<seq[i].first;
            if(result.find(i) != result.end()){
                output<<"("<<seq[i].second / 115<<")";
            }
            else{
                output<<" "<<seq[i].second / 115<<" ";
            }
        }
        //for(int i : resultOld){cout<<i<<" ";}cout<<endl;for(int i: result){cout<<i<<" ";}
        output<<"   Old: "<<end1-begin1<<", New: "<<end2-end1<<endl;
    }
    output<<"0 = d,   1 = s"<<endl;

}

void allCombs(){

    ifstream input("input.txt");
    int size;
    input>>size;
    vector<pair<int, char>> starting;
    starting.resize(size);
    for(int i=0; i<size; i++){
        starting[i].first = i;
        input>>starting[i].second;
    }
    clock_t begin1 = clock();
    set<int> resultOld = allCombsTest(starting);
    clock_t end1 = clock();
    set<int> result = allCombsTestNew(starting);
    clock_t end2 = clock();
    ofstream output("output.txt");
    for(int i=0; i<starting.size(); i++){
        if(result.find(i) != result.end()){
            cout<<"("<<starting[i].second<<")";
        }
        else{
            cout<<" "<<starting[i].second<<" ";
        }
    }
    //for(int i : resultOld){cout<<i<<" ";}cout<<endl;for(int i: result){cout<<i<<" ";}
    cout<<endl<<"Old: "<<end1-begin1<<", New: "<<end2-end1;
}

set<int> allCombsTestNew(vector<pair<int, char>> seq){
    set<int> result;
    if(seq.size() == 3){
        if(seq[1].second == 's'){
            result.insert(seq[2].first);
        }
        else{
            result.insert(seq[0].first);
        }
    }
    else {
        vector<pair<int, char>> tempVec;
        int index;
        char prev = 'a', pre_prev = 'b';
        for (int i = 1; i < seq.size() - 1; i++) {
            bool skippable = false;
            if(seq[i].second == 'd'){
                if((seq[i+1].second == 's') && (i+1 != seq.size()-1) || ((prev == pre_prev) && (prev == seq[i].second))){
                    skippable = true;
                    index = -1;
                }
                else {
                    index = i;
                }
            }
            else{
                index = i-1;
            }
            if(! skippable) {
                tempVec = copyRemoving(seq, index);
                set<int> tempSet = allCombsTest(tempVec);
                for(int k : tempSet){
                    if(result.find(k) != result.end()){
                        //cout<<i<<endl;
                    }
                }
                result.insert(tempSet.begin(), tempSet.end());
            }
            pre_prev = prev;
            prev = seq[i].second;
        }
    }
    return result;
}

set<int> allCombsTest(vector<pair<int, char>> seq){
    set<int> result;
    if(seq.size() == 3){
        if(seq[1].second == 's'){
            result.insert(seq[2].first);
        }
        else{
            result.insert(seq[0].first);
        }
    }
    else {
        vector<pair<int, char>> tempVec;
        int index;
        for (int i = 1; i < seq.size() - 1; i++) {
            bool skippable = false;
            if(seq[i].second == 'd'){
                if((seq[i+1].second == 's') && (i+1 != seq.size()-1)){
                    skippable = true;
                    index = -1;
                }
                else {
                    index = i;
                }
            }
            else{
                index = i-1;
            }
            if(! skippable) {
                tempVec = copyRemoving(seq, index);
                set<int> tempSet = allCombsTest(tempVec);
                for(int k : tempSet){
                    if(result.find(k) != result.end()){
                        //cout<<i<<endl;
                    }
                }
                result.insert(tempSet.begin(), tempSet.end());
            }
        }
    }
    return result;
}


void submission(){
    ifstream input("input.txt");
    int size;
    input>>size;
    vector<pair<int, char>> starting;
    starting.resize(size);
    for(int i=0; i<size; i++){
        starting[i].first = i;
        input>>starting[i].second;
        cout<<" "<<starting[i].second<<" ";
    }
    cout<<endl;
    set<int> result = allCombsTestNew(starting);

}











