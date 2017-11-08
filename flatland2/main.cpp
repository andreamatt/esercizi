#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
#include <set>
#include <cmath>
#include <ctime>

using namespace std;

bool isThisSolution(vector<pair<int, char>> seq, int candidate);
set<int> newAlgoz(vector<pair<int, char>> seq);
bool isDestructible(vector<pair<int, char>> seq, int start, int end);
vector<vector<pair<int, char>>> allSequences(int length);
vector<char> copy(vector<char> seq);

ofstream output("output.txt");

int main() {

    for(int i=5; i<22; i+=2){
        vector<vector<pair<int, char>>> seq_s = allSequences(i);
        clock_t before = clock();
        for(vector<pair<int, char>> seq : seq_s){
            newAlgoz(seq);
        }
        output<<"i = "<<i<<", time: "<<(clock()-before)<<", time/seq: "<<(clock()-before)/pow(2, i)<<endl;
    }

    return 0;
}

bool isDestructible(vector<pair<int, char>> seq, int start, int end){
    // indexes included
    // if len==0, true
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