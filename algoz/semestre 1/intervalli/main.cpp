#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void intervalSort();
void merge(vector<pair<int,int>> &seq, int S_A, int E_A, int S_B, int E_B);
void mergeSort(vector<pair<int,int>> &seq, int start, int end);


int main() {

    intervalSort();

    return 0;
}

void intervalSort(){
    ifstream input("input.txt");
    int size;
    input>>size;

    vector<pair<int,int>> intervals;
    intervals.resize(size);
    for(int i=0; i<size; i++){
        input>>intervals[i].first;
        input>>intervals[i].second;
    }

    // sort by interval start
    mergeSort(intervals, 0, size-1);

    // FIND MAX EMPTY INTER
    int start = 0;
    int end = 0;
    int maxEnding=0;
    for(int i=0; i<size-1; i++){
        if(intervals[i].second > maxEnding){
            maxEnding = intervals[i].second;
        }
        if(intervals[i+1].first - maxEnding > end-start){
            start = maxEnding;
            end = intervals[i+1].first;
        }
    }

    ofstream output("output.txt");
    if(end-start == 0){
        output<<"0";
    }
    else{
        output<<start<<" "<<end;
    }
}

void mergeSort(vector<pair<int,int>> &seq, int start, int end){

    if(end-start == 0){
        return;
    }
    else if(end-start == 1){
        if(seq[start] > seq[end]){
            pair<int,int> t = seq[end];
            seq[end].first = seq[start].first;
            seq[end].second = seq[start].second;

            seq[start].first = t.first;
            seq[start].second = t.second;
        }
    }
    else{
        mergeSort(seq, start, (start+end)/2);
        mergeSort(seq, (start+end)/2 +1, end);
        merge(seq, start, (start+end)/2, (start+end)/2+1, end);
    }

}

void merge(vector<pair<int,int>> &seq, int S_A, int E_A, int S_B, int E_B){

    if(E_A +1 != S_B){
        cout<<"Non consecutive"<<endl;
        return;
    }

    vector<pair<int,int>> result;
    result.resize(E_B-S_A+1);
    int a=S_A, b=S_B, k=0;
    while(a<=E_A && b<=E_B){
        if(seq[a].first < seq[b].first){
            result[k].first = seq[a].first;
            result[k].second = seq[a].second;
            a++;
        }
        else{
            result[k].first = seq[b].first;
            result[k].second = seq[b].second;
            b++;
        }
        k++;
    }

    while(a <= E_A){
        result[k].first = seq[a].first;
        result[k].second = seq[a].second;
        a++;
        k++;
    }
    while(b <= E_B){
        result[k].first = seq[b].first;
        result[k].second = seq[b].second;
        b++;
        k++;
    }

    for(int i=0; i<result.size(); i++){
        seq[S_A+i].first = result[i].first;
        seq[S_A+i].second = result[i].second;
    }

}
