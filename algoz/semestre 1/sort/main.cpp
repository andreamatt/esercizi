#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void merge(vector<int> &seq, int, int, int, int);
void mergeSort(vector<int> &seq, int, int);

int main() {

    ifstream input("input.txt");
    int size;
    input>>size;

    vector<int> seq;
    seq.resize(size);
    for(int i=0; i<size; i++){
        input>>seq[i];
    }

    mergeSort(seq, 0, seq.size()-1);

    ofstream output("output.txt");
    for(int i=0; i<seq.size(); i++){
        output<<seq[i]<<" ";
    }

    return 0;
}

void mergeSort(vector<int> &seq, int start, int end){
    // 1 element
    if(end-start == 0){
        return;
    }

    // 2 elements
    else if(end-start == 1){
        if(seq[start] > seq[end]){
            int t = seq[end];
            seq[end] = seq[start];
            seq[start] = t;
        }
    }

    // more than 2 => split
    else{
        mergeSort(seq, start, (start+end)/2);
        mergeSort(seq, (start+end)/2 +1, end);
        merge(seq, start, (start+end)/2, (start+end)/2+1, end);
    }
    
}

void merge(vector<int> &seq, int S_A, int E_A, int S_B, int E_B){

    if(E_A +1 != S_B){
        // ending of A must be exactly before starting of B
        cout<<"Non consecutive"<<endl;
        return;
    }

    vector<int> result;
    result.resize(E_B-S_A+1);
    int a=S_A, b=S_B, k=0;
    // insert until one of them is over
    while(a<=E_A && b<=E_B){
        if(seq[a] < seq[b]){
            result[k] = seq[a];
            a++;
        }
        else{
            result[k] = seq[b];
            b++;
        }
        k++;
    }

    // insert all remaining items either from A or from B
    while(a <= E_A){
        result[k] = seq[a];
        a++;
        k++;
    }
    while(b <= E_B){
        result[k] = seq[b];
        b++;
        k++;
    }

    // put back in input array
    for(int i=0; i<result.size(); i++){
        seq[S_A+i] = result[i];
    }

}