#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>

using namespace std;

void interval();
void intervalSort();
void merge(vector<pair<int,int>> &seq, int S_A, int E_A, int S_B, int E_B);
void mergeSort(vector<pair<int,int>> &seq, int start, int end);


int main() {

    /*
    srand(clock());
    ofstream input("input.txt");
    input<<200<<endl;
    for(int i=0; i<200; i++){
        int n = rand()%1000;
        input<<n<<" "<<n + rand()%20<<endl;
    }
    */

    intervalSort();
    //interval();

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

    mergeSort(intervals, 0, size-1);

    // FIND MAX EMPTY INTER
    //ofstream output2("output2.txt");
    //output2<<size<<endl;

    int start = 0;
    int end = 0;
    int maxEnding=0;
    for(int i=0; i<size-1; i++){
        //output2<<intervals[i].first<<" "<<intervals[i].second<<endl;
        if(intervals[i].second > maxEnding){
            maxEnding = intervals[i].second;
        }
        if(intervals[i+1].first - maxEnding > end-start){
            start = maxEnding;
            end = intervals[i+1].first;
            //cout<<start<<" "<<end<<endl;
        }
    }

    ofstream output("output.txt");
    //output<<"Solution: "<<endl;
    if(end-start == 0){
        output<<"0";
    }
    else{
        output<<start<<" "<<end;
    }

    //interval();
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

void interval() {
    ifstream input("output2.txt");
    int size;
    input >> size;

    int curFirst;
    int curSecond;
    pair<int, int> limits;
    vector<pair<int, int>> emptyIntervals;

    // first one is manual
    input >> curFirst;
    input >> curSecond;
    limits.first = curFirst;
    limits.second = curSecond;

    for (int i = 1; i < size; i++) {
        input >> curFirst;
        input >> curSecond;

        // modify current emptyInters
        int currentIntervalsSize = emptyIntervals.size();
        for (int k = 0; k < currentIntervalsSize; k++) {
            // case 1: the k-inter is covered by i => delete k-inter
            if (curFirst <= emptyIntervals[k].first && curSecond >= emptyIntervals[k].second) {
                emptyIntervals.erase(emptyIntervals.begin() + k);
            }

                // case 2: have to divide k-inter in 2 intervals
            else if (curFirst > emptyIntervals[k].first && curSecond < emptyIntervals[k].second) {
                // right one
                pair<int, int> rightInter;
                rightInter.first = curSecond;
                rightInter.second = emptyIntervals[k].second;
                emptyIntervals.push_back(rightInter);

                // left one
                emptyIntervals[k].second = curFirst;
            }

                // case 3: first is inside
            else if (curFirst > emptyIntervals[k].first && curFirst < emptyIntervals[k].second) {
                emptyIntervals[k].second = curFirst;
            }

                // case 4: second is inside
            else if (curSecond > emptyIntervals[k].first && curSecond < emptyIntervals[k].second) {
                emptyIntervals[k].first = curSecond;
            }
        }

        // add possible new-start and new-end inters
        if (curFirst < limits.first) {
            if (curSecond < limits.first) {
                pair<int, int> left;
                left.first = curSecond;
                left.second = limits.first;
                emptyIntervals.push_back(left);
            }

            limits.first = curFirst;
        }
        if (curSecond > limits.second) {
            if (curFirst > limits.second) {
                pair<int, int> right;
                right.first = limits.second;
                right.second = curFirst;
                emptyIntervals.push_back(right);
            }

            limits.second = curSecond;
        }
    }

    // END. NOW PRINT RESULT
    ofstream output("output3.txt");
    if (emptyIntervals.size() == 0) {
        output << "0";
    }
    else {
        pair<int, int> longest;
        longest.first = emptyIntervals[0].first;
        longest.second = emptyIntervals[0].second;

        //output<<"size: "<<emptyIntervals.size()<<endl;

        for (int i = 1; i < emptyIntervals.size(); i++) {
            //output<<emptyIntervals[i].first<<" "<<emptyIntervals[i].second<<endl;
            if (emptyIntervals[i].second - emptyIntervals[i].first > longest.second - longest.first) {
                longest.first = emptyIntervals[i].first;
                longest.second = emptyIntervals[i].second;
            } else if (emptyIntervals[i].second - emptyIntervals[i].first == longest.second - longest.first) {
                if (emptyIntervals[i].first < longest.first) {
                    longest.first = emptyIntervals[i].first;
                    longest.second = emptyIntervals[i].second;
                }
            }
        }
        //output<<"Longest: ";
        output << longest.first << " " << longest.second << endl;
    }
}