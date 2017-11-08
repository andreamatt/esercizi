#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void interval();

int main() {

    interval();

    return 0;
}

void interval() {
    ifstream input("input.txt");
    int size;
    input >> size;

    pair<int, int> current;
    pair<int, int> limits;
    vector<pair<int, int>> emptyIntervals;

    // first one is manual
    input >> current.first;
    input >> current.second;
    limits.first = current.first;
    limits.second = current.second;

    for (int i = 1; i < size; i++) {
        input >> current.first;
        input >> current.second;

        // modify current emptyInters
        int currentIntervalsSize = emptyIntervals.size();
        for (int k = 0; k < currentIntervalsSize; k++) {
            // case 1: the k-inter is covered by i => delete k-inter
            if (current.first <= emptyIntervals[k].first && current.second >= emptyIntervals[k].second) {
                emptyIntervals.erase(emptyIntervals.begin() + k);
            }

                // case 2: have to divide k-inter in 2 intervals
            else if (current.first > emptyIntervals[k].first && current.second < emptyIntervals[k].second) {
                // right one
                pair<int, int> rightInter;
                rightInter.first = current.second;
                rightInter.second = emptyIntervals[k].second;
                emptyIntervals.push_back(rightInter);

                // left one
                emptyIntervals[k].second = current.first;
            }

                // case 3: first is inside
            else if (current.first > emptyIntervals[k].first && current.first < emptyIntervals[k].second) {
                emptyIntervals[k].second = current.first;
            }

                // case 4: second is inside
            else if (current.second > emptyIntervals[k].first && current.second < emptyIntervals[k].second) {
                emptyIntervals[k].first = current.second;
            }
        }

        // add possible new-start and new-end inters
        if (current.first < limits.first) {
            if (current.second < limits.first) {
                pair<int, int> left;
                left.first = current.second;
                left.second = limits.first;
                emptyIntervals.push_back(left);
            }

            limits.first = current.first;
        }
        if (current.second > limits.second) {
            if (current.first > limits.second) {
                pair<int, int> right;
                right.first = limits.second;
                right.second = current.first;
                emptyIntervals.push_back(right);
            }

            limits.second = current.second;
        }
    }

    // END. NOW PRINT RESULT
    ofstream output("output.txt");
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