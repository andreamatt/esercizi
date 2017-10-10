#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int sum_N(vector<int>, int);
int sum_DeI(vector<int>, int, int);
int sommaseq_N_quad(vector<int> seq, int n);

int main() {
    vector<int> seq;
    ifstream inputs("input.txt");
    int len;
    inputs>>len;
    seq.resize(len);
    for(int i=0; i<len; i++){
        inputs>>seq[i];
    }


    ofstream out("output.txt");
    out<<sum_N(seq, len);



    return 0;
}

int sum_DeI(vector<int> seq, int i, int j){
    return 0;
}

int max(int a, int b){
    return (a>b) ? a : b;
}

int sum_N(vector<int> seq, int n){
    if(n == 0) {
        return 0;
    }
    int max_so_far = seq[0], max_ending_here = 0;

    for (int i = 0; i < n; i++) {
        max_ending_here = max_ending_here + seq[i];
        if (max_so_far < max_ending_here)
            max_so_far = max_ending_here;

        if (max_ending_here < 0)
            max_ending_here = 0;
    }
    return max_so_far;
}

int sommaseq_N_quad(vector<int> seq, int n){
    // calc
    int sum_max=seq[0];
    for(int i=0; i<n; i++){
        int sum_prec = 0;
        for(int j=i; j<n; j++){
            int sum = sum_prec + seq[j];
            if(sum>sum_max) sum_max = sum;
            sum_prec = sum;
        }
    }
    return sum_max;
}

void somma(){
    int a, b;
    ifstream inputs("input.txt");
    inputs>>a;
    inputs>>b;
    ofstream output("output.txt");
    output<<(a+b);
}
