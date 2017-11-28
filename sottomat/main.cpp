#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void maxSubMatrixSum();
int maxSubArraySum(vector<int> &array, int size);

int main() {

    maxSubMatrixSum();

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