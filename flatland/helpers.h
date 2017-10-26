//
// Created by andrea on 27/10/2017.
//

#ifndef FLATLAND_HELPERS_H
#define FLATLAND_HELPERS_H

#include <cmath>

using namespace std;
//  0 1 2 3 4 5 6
//  s s s s d s s

vector<char> copy(vector<char> seq);
vector<pair<int, char>> copyRemoving(vector<pair<int, char>> seq, int a);
vector<vector<pair<int, char>>> allSequences(int length);


bool isThisSolution(vector<pair<int, char>> seq, int index){





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

#endif //FLATLAND_HELPERS_H
