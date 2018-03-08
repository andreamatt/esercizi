#include <iostream>
#include <vector>
#include <set>
#include <fstream>

using namespace std;

bool isThisSolution(vector<pair<int, char>> seq, int candidate);
set<int> newAlgoz(vector<pair<int, char>> seq);
bool isDestructible(vector<pair<int, char>> seq, int start, int end);


int main() {

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
        if(seq[start].second == 's' && seq[end].second == 'd'){
            for(int i=start+1; i<=end-2; i+=2){
                if(seq[i].second == 's'){
                    for(int k=i+1; k<end; k+=2){
                        if(seq[k].second == 'd'){   // i = 1, k = 4
                            // found candidate couple: i, k;
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
        // cercare 's', capire se sx(s) è distruttibile e dx(s) pure
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







