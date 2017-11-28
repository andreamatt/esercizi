#include <iostream>
#include <fstream>

using namespace std;

void sum_N_NoSpace();

int main() {

    sum_N_NoSpace();

    return 0;
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