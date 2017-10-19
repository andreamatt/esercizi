#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int sum_N(vector<int>, int);
void sum_N_NoSpace();
void maxSubMatrixSum();
int maxSubArraySum(int* array, int size);
int maxSubArraySum(vector<int> &array, int size);


int main() {

    sum_N_NoSpace();


    return 0;
}

void maxSubMatrixSum() {
    int y;
    int x;
    int sum;
    int maxSum = 0;
    ifstream in("input.txt");
    in >> y >> x;
    //int matrix[y][x];
    vector<vector<int>> matrix;
    matrix.resize(y);
    for(int i=0; i<y; i++){
        matrix[i].resize(x);
    }

    // putting data into matrix
    for (int k = 0; k < y; ++k) {
        for (int i = 0; i < x; ++i) {
            in >> matrix[k][i];
            //cout<<matrix[k][i]<<", ";
        }
        //cout<<endl;
    }

    // main algorithm
    vector<int> temp;
    temp.resize(y);

    for (int left = 0; left < x; left++) {
        //int temp[y] = {0};
        for(int i=0; i<y; i++){
            temp[i] = 0;
        }
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

int maxSubArraySum(vector<int> &array, int size) {
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

int maxSubArraySum(int* array, int size) {
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

void somma(){
    int a, b;
    ifstream inputs("input.txt");
    inputs>>a;
    inputs>>b;
    ofstream output("output.txt");
    output<<(a+b);
}
