#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <ctime>
#include <cmath>

using namespace std;
ofstream output2("output2.txt");

vector<char> copy(vector<char> seq);
vector<pair<int, char>> copyRemoving(vector<pair<int, char>> seq, int a);
vector<vector<pair<int, char>>> allSequences(int length);
set<int> allCombsTestNew(vector<pair<int, char>> seq);
void checkNewSuper(int len);
bool isThisSolution(vector<pair<int, char>> seq, int candidate);
set<int> newAlgoz(vector<pair<int, char>> seq);
bool isDestructible(vector<pair<int, char>> seq, int start, int end);


int main() {
    /*
    vector<vector<pair<int, char>>> seqs = allSequences(6);
    ofstream output("output.txt");
    for(int i=0; i<seqs.size(); i++){
        for(int k=0; k<seqs[i].size(); k++){
            output<<seqs[i][k].second<<" ";
        }
        output<<" :  "<<((isDestructible(seqs[i], 0, seqs[i].size()-1)) ? "true" : "false" )<<endl<<endl;
    }*/




    //checkNewSuper(13);


    ifstream input("input.txt");
    int size;
    input>>size;
    vector<pair<int, char>> seq;
    seq.resize(size);
    for(int i=0; i<size; i++){
        seq[i].first = i;
        input>>seq[i].second;
    }
    set<int> result = newAlgoz(seq);

    ofstream output("output.txt");
    output<<result.size()<<endl;
    for(int i : result){
        output<<i<<" ";
    }
    

    return 0;
}

bool isDestructible(vector<pair<int, char>> seq, int start, int end){
    // indexes included
    // if len==0, true
    output2<<"Start: "<<start<<", end: "<<end<<endl;
    if(end-start == -1){
        //cout<<"Case 1"<<endl;
        return true;
    }

    // if len==2 estremi diversi da <> (GIUSTO)
    else if(end-start == 1){
        //cout<<"Case 2"<<endl;
        return !(seq[start].second == 's' && seq[end].second == 'd');
    }

    // if len==4
    else if(end-start == 3){
        //cout<<"Case 3"<<endl;
        // estremi verso esterno
        if(seq[start].second == 's' && seq[end].second == 'd'){
            return (seq[start+1].second == 's') && (seq[end-1].second == 'd');
        }
        // altrimenti
        else{
            return true;
        }
    }

    else{
        //cout<<"Case 4"<<endl;
        if(seq[start].second == 's' && seq[end].second == 'd'){
            for(int i=start+1; i<=end-2; i+=2){
                if(seq[i].second == 's'){
                    for(int k=i+1; k<end; k+=2){
                        if(seq[k].second == 'd'){   // i = 1, k = 4
                            //cout<<"found candidate couple: i="<<i<<", k="<<k<<endl;
                            if((isDestructible(seq, start+1, i-1) && isDestructible(seq, i+1, k-1)) && isDestructible(seq, k+1, end-1)){
                                return true;
                            }
                        }
                    }
                }
            }
            return false;
        }
        else{
            return true;
        }
    }
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

    // check if has 's' in sx(cand) && 'd' in dx(cand)
    // NB: gli estremi no! => da 1 a penultimo
    bool sx = false;
    if(candidate == 0) {
        sx = true;
    }
    else if(seq[candidate-1].second == 'd'){
        // casino: cercare 's', capire se sx(s) è distrutt e dx(s) pure
        for(int i=1; i<candidate; i+=2){
            if(seq[i].second == 's'){
                if(isDestructible(seq, 1, i-1) && isDestructible(seq, i+1, candidate-1)){
                    sx = true;
                }
            }
        }

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
    else if(seq[candidate+1].second == 's'){
        // casino: cercare 'd', capire se sx(d) è distrutt e dx(d) pure
        for(int i=candidate+1; i<seq.size()-1; i+=2){
            if(seq[i].second == 'd'){
                if(isDestructible(seq, candidate+1, i-1) && isDestructible(seq, i+1, seq.size()-2)){
                    dx = true;
                }
            }
        }

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
        output<<"   Old: "<<end2-end1<<", New: "<<end1-begin1<<endl<<endl;
    }
    output<<"0 = d,   1 = s"<<endl;
    cout<<discrepanze / (pow(2, len) )<<" discrepanze per sequenza";
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
                set<int> tempSet = allCombsTestNew(tempVec);
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






