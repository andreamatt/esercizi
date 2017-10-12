#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int sum_N(vector<int>, int);
int sommaseq_N_quad(vector<int> seq, int n);
void sommaMat();
void sum_N_NoSpace();
void maxSubMatrixSum();
int maxSubArraySum(int *array, int size);

int main() {

    maxSubMatrixSum();


    return 0;
}

void sommaMat(){
    ifstream input("input.txt");
    int rows, cols;
    input>>rows;
    input>>cols;
    vector<vector<int>> matrix;
    matrix.resize(rows);
    for (int i = 0; i < matrix.size(); i++) {
        matrix[i].resize(cols);
    }

    int current;
    for (int i = 0; i < rows; ++i) {
        int tempsum = 0;
        for (int j = 0; j < cols; ++j) {
            input>>current;
            tempsum += current;
            matrix[i][j] = tempsum;
            cout<<matrix[i][j]<<", ";
        }
        cout<<endl;
    }

    // calcul

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {

        }
    }


}


void maxSubMatrixSum() {
    int y;
    int x;
    int sum;
    int maxSum = 0;
    ifstream in("input.txt");
    in >> y >> x;
    int matrix[y][x];

    // putting data into matrix
    for (int k = 0; k < y; ++k) {
        for (int i = 0; i < x; ++i) {
            in >> matrix[k][i];
        }
    }

    // main algorithm
    for (int left = 0; left < x; left++) {
        int temp[y] = {0};
        for (int right = left; right < x; right++) {
            for (int i = 0; i < y; ++i) {
                temp[i] += matrix[i][right];
            }
            sum = maxSubArraySum(temp, y);
            if (sum > maxSum)
                maxSum = sum;
        }
    }
    ofstream out("output.txt");
    out << maxSum;
}


int maxSubArraySum(int *array, int size) {
    int tmp = 0;
    int tmpMax = 0;

    for (int i = 0; i < size; ++i) {
        tmp += array[i];
        if (tmp < 0) {
            tmp = 0;
        }
        tmpMax = max(tmpMax, tmp);
    }
    return tmpMax;
}

void sum_N_NoSpace(){
    ifstream input("input.txt");
    int n;
    input>>n;
    if(n == 0) {
        fstream output("output.txt");
        output<<0;
    }
    else {
        int max_so_far, max_ending_here = 0;
        int num;
        input >> num;
        max_so_far = num;
        max_ending_here = max_ending_here + num;
        if (max_so_far < max_ending_here)
            max_so_far = max_ending_here;

        if (max_ending_here < 0)
            max_ending_here = 0;
        for (int i = 1; i < n; i++) {
            input >> num;
            max_ending_here = max_ending_here + num;
            if (max_so_far < max_ending_here)
                max_so_far = max_ending_here;

            if (max_ending_here < 0)
                max_ending_here = 0;
        }

        // out
        ofstream output("output.txt");
        output<<max_so_far;
    }
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
