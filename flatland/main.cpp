#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <ctime>
#include <cmath>

using namespace std;

vector<char> copy(vector<char> seq);
vector<pair<int, char>> copyRemoving(vector<pair<int, char>> seq, int a);
vector<vector<pair<int, char>>> allSequences(int length);
set<int> allCombsTest(vector<pair<int, char>> seq);
set<int> allCombsTestNew(vector<pair<int, char>> seq);
void allCombs();
void submission();
void testAll(int len);
void checkNewSuper(int len);
bool isThisSolution(vector<pair<int, char>> seq, int candidate);
set<int> newAlgoz(vector<pair<int, char>> seq);
bool canGive(vector<pair<int, char>> seq, int start, int end, bool giveS);

int main() {

    //testAll(5);
    checkNewSuper(13);
    //allCombs();
    //submission();

    return 0;
}

set<int> newAlgoz(vector<pair<int, char>> seq){
    set<int> solutions;
    for(int i=0; i<seq.size(); i+=2){
        if(isThisSolution(seq, i)){
            solutions.insert(i);
        }
    }
    return solutions;
}

bool isThisSolution(vector<pair<int, char>> seq, int candidate){

    // check if has 'd' in dx(cand) and 's' in sx(cand)
    // NB: gli estremi no! => da 1 a penultimo
    bool sx = false;
    if(candidate == 0) {
        sx = true;
    }
    else{
        for (int i = 1; i < candidate; i += 2) {    // could put (i<indicate || sx)
            if (seq[i].second == 's') {
                sx = true;
            }
        }
    }

    bool dx = false;
    if(candidate == seq.size()-1){
        dx = true;
    }
    else {
        for (int i = candidate + 1; i < seq.size() - 1; i+=2) {
            if (seq[i].second == 'd') {
                dx = true;
            }
        }
    }

    return sx && dx;
}

// start e end inclusi
bool canGive(vector<pair<int, char>> seq, int start, int end, bool give_D){
    char x = (give_D) ? 'd' : 's';
    
}

void checkNewSuper(int len){
    int discrepanze = 0;
    vector<vector<pair<int, char>>> sequences = allSequences(len);
    ofstream output("output.txt");
    output<<"0 = d,   1 = s"<<endl;
    for(vector<pair<int, char>> seq : sequences){
        clock_t begin1 = clock();
        set<int> result = newAlgoz(seq);
        clock_t end1 = clock();
        set<int> resultOld = allCombsTestNew(seq);
        clock_t end2 = clock();
        for(int i=0; i<seq.size(); i++){
            if((result.find(i) != result.end()) != (resultOld.find(i) != resultOld.end())){
                discrepanze++;
            }
            //cout<<seq[i].first;
            if(resultOld.find(i) != resultOld.end()){
                output<<"("<<seq[i].second<<")";
            }
            else{
                output<<" "<<seq[i].second<<" ";
            }
        }
        output<<endl;
        for(int i=0; i<seq.size(); i++){
            //cout<<seq[i].first;
            if(result.find(i) != result.end()){
                output<<"("<<seq[i].second<<")";
            }
            else{
                output<<" "<<seq[i].second<<" ";
            }
        }
        //for(int i : resultOld){cout<<i<<" ";}cout<<endl;for(int i: result){cout<<i<<" ";}
        output<<"   Old: "<<end1-begin1<<", New: "<<end2-end1<<endl<<endl;
    }
    output<<"0 = d,   1 = s"<<endl;
    cout<<discrepanze / (pow(2, len) )<<" discrepanze per sequenza";
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
        //cout<<" "<<starting[i].second<<" ";
    }
    cout<<endl;
    set<int> result = newAlgoz(starting);

    ofstream output("output.txt");
    output<<result.size()<<endl;
    for(int i : result){
        output<<i<<" ";
    }

}





vector<pair<int, char>> copyRemoving(vector<pair<int, char>> seq, int a){
    vector<pair<int, char>> result;
    result.resize(seq.size()-2);
    for(int i=0; i<a; i++){
        result[i].first = seq[i].first;
        result[i].second = seq[i].second;
    }
    for(int i=a+2; i<seq.size(); i++){
        result[i-2].first = seq[i].first;
        result[i-2].second = seq[i].second;
    }
    return result;
};

vector<vector<pair<int, char>>> allSequences(int length){
    vector<vector<char>> result;
    result.resize(pow(2, length));

    result[0].push_back('d');
    result[1].push_back('s');

    for(int i=1; i<length; i++){
        int currentLength = pow(2, i);
        for(int k=0; k<currentLength; k++){
            vector<char> added = copy(result[k]);
            result[k].insert(result[k].begin(), 'd');
            added.insert(added.begin(), 's');

            result[currentLength+k] = added;
        }
    }

    vector<vector<pair<int, char>>> resultFinal;
    resultFinal.resize(result.size());
    for(int i=0; i<resultFinal.size(); i++){
        resultFinal[i].resize(length);
        for(int k=0; k<length; k++){
            resultFinal[i][k].first = k;
            resultFinal[i][k].second = result[i][k];
        }
    }

    return resultFinal;
}

vector<char> copy(vector<char> seq){
    vector<char> result;
    result.resize(seq.size());
    for(int i=0; i<seq.size(); i++){
        result[i] = seq[i];
    }
    return result;
}






