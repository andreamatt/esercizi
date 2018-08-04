//
// Created by andrea on 01/11/2017.
//

#ifndef SORTING_OLDMERGESORT_H
#define SORTING_OLDMERGESORT_H

#include <vector>

using namespace std;

vector<int> split(vector<int>, int, int);
vector<int> mergeSort(vector<int>);
vector<int> merge(vector<int>, vector<int>);


vector<int> mergeSort(vector<int> seq){
    if(seq.size()==1){
        return seq;
    }
    else if(seq.size()==2){
        if(seq[0]>seq[1]){
            int t=seq[1];
            seq[1] = seq[0];
            seq[0] = t;
        }
        return seq;
    }
    else{
        vector<int> sx = mergeSort(split(seq, 0, seq.size()/2));
        vector<int> dx = mergeSort(split(seq, seq.size()/2, seq.size()));
        return merge(sx, dx);
    }
}




vector<int> merge(vector<int> seq_A, vector<int> seq_B){

    vector<int> result;
    result.resize(seq_A.size() + seq_B.size());

    int a=0, b=0, k=0;
    while(a!=seq_A.size() && b!=seq_B.size()){
        if(seq_A[a] < seq_B[b]){
            result[k] = seq_A[a];
            a++;
        }
        else{
            result[k] = seq_B[b];
            b++;
        }
        k++;
    }

    // insert remaining
    while(a != seq_A.size()){
        result[k] = seq_A[a];
        a++;
        k++;
    }

    while(b != seq_B.size()){
        result[k] = seq_B[b];
        b++;
        k++;
    }

    return result;
}

vector<int> split(vector<int> seq, int from, int to){
    vector<int> result;
    result.resize(to-from);

    for(int i=from; i<to; i++){
        result[i-from] = seq[i];
    }

    return result;
}

#endif //SORTING_OLDMERGESORT_H
