#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

typedef vector<vector<int>> Mat;

void printMat(Mat& mat){
    for(int i=0; i<mat.size(); i++){
        cout<<i<<", "<<mat[i].size()<<": ";
        for(int j=0; j<mat[i].size(); j++){
            cout<<mat[i][j]<<", ";
        }
        cout<<endl;
    }
    cout<<endl;
}


// trasforma da stringa a vettore di lunghezze
// es: da JJJHHHHHJHHJJ => {3, 5, 1, 2, 2}
// es: da JJJJJJJJJJJJJ => {13}
Mat clean(vector<string>& serate) {
    int N = serate.size();
    int M = serate[0].size();
	Mat cleaned(N);
	
	for (int i = 0; i < N; i++) {
		int count = 1;
		for (int j = 1; j < M; j++) {
			if (serate[i][j] == serate[i][j - 1])
				count++;
			else {
				cleaned[i].push_back(count);
				count = 1;
			}
		}
		cleaned[i].push_back(count);
	}

    return cleaned;
}

// da vettore di lunghezze a vettore di guadagni: in posizione i quanto guadagno con capacità i
// es: {1, 3, 2, 2}(JHHHJJHH) => {0, 5, 6, 7, 8, 8, 8, ...}
vector<int> stringToGuad(vector<int>& seq, int T) {
	int S = seq.size();
	Mat res(S + 1, vector<int>(T + 1, 0));

	for (int t = 1; t <= T; t++) {
		res[S - 1][t] = seq[S - 1];
		res[S][t] = 0;
	}

    printMat(res);

	for (int i = S - 2; i >= 0; i--) {
		for (int t = 1; t <= T; t++) {
			res[i][t] = res[i + 1][t];
			int cur = 0;
			for (int j = i; j < S; j += 2) {
				cur += seq[j];
				res[i][t] = max(res[i][t], res[j + 1][t - 1] + cur);
			}
		}
	}

    //for(int i=0; i<res[0].size(); i++)  cout<<res[0][i]<<", ";  cout<<endl;

	return res[0];
}

int sherlock(Mat& cleaned, int N, int T){

    Mat Tab(N);
    Tab[0] = stringToGuad(cleaned[0], T);

    for(int i=1; i<N; i++){
        vector<int> cur = stringToGuad(cleaned[i], T);
        Tab[i].resize(T+1);
        
        for(int tot=0; tot<=T; tot++){
            for(int here=0; here<=tot; here++){
                Tab[i][tot] = max(Tab[i][tot], cur[here] + Tab[i-1][tot-here]);
            }
        }
    }

    return Tab[N-1][T];
}

int main() {
	ifstream in("input.txt");

    int N, M, T;
    vector<string> serate;
	in >> N >> M >> T;
	serate.resize(N);
	for (int i = 0; i < N; i++){
		in >> serate[i];
    }

	Mat cleaned = clean(serate);
    
	int result = sherlock(cleaned, N, T);

	ofstream out("output.txt");
    out<<result;

	return 0;
}