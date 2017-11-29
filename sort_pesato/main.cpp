#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int minSwaps(vector<int> &seq);
int minPeso(vector<int> &seq);

int main() {
    vector<int> seq;
    //Contiene quali posizioni sono state processate
    ifstream input("input.txt");
    int N;
    input >> N;
    seq.resize(N+1); // La posizione 0 viene semplicemente ignorata
    for(int i=1;i<=N;i++) {
        input >> seq[i];
    }

    int swaps = minSwaps(seq);
    int peso = minPeso(seq);

    ofstream output("output.txt");
    output<<swaps<<" "<<peso;

    return 0;
}

int minSwaps(vector<int> &seq){
    int N = seq.size()-1;
    vector<bool> vis;
    vis.resize(N+1, false); // La posizione 0 viene semplicemente ignorata
    int mosse=0;
    for(int i=1;i<=N;i++) {
        //Se non abbiamo ancora lavorato con questa posizione
        if (!vis[i]) {
            //Se non è già al suo posto
            if (seq[i] != i) {
                int cur=i;
                int num=0;
                //Scorro finchè è indipendente da altri cicli
                while(!vis[seq[cur]]){
                    vis[seq[cur]]=true;
                    cur=seq[cur];
                    num++;
                }
                //Un ciclo di num interi ha bisogno di num-1 mosse
                mosse+=num-1;
            }
            vis[i]=true;
        }
    }
    return mosse;
}

int minPeso(vector<int> &seq){
    int N = seq.size()-1;
    vector<bool> vis;
    vis.resize(N+1, false); // La posizione 0 viene semplicemente ignorata
    int prezzo=0;
    for(int i=1;i<=N;i++) {
        //Se non abbiamo ancora lavorato con questa posizione
        if (!vis[i]) {
            //Se non è già al suo posto
            if (seq[i] != i) {
                //Mantengo la somma del ciclo di posizioni
                int sum=0;
                //Il piú piccolo degli interi di questo ciclo
                int minN=INT_MAX;
                int cur=i;
                int num=0;
                //Scorro finchè è indipendente da altri cicli
                while(!vis[seq[cur]]){
                    minN=min(minN,seq[cur]);
                    sum+=seq[cur];
                    vis[seq[cur]]=true;
                    cur=seq[cur];
                    num++;
                }
                int mosse = num-1;  // mosse per questo ciclo
                //Tolgo il min dalla somma: sum è il totale degli N swappati USANDO minN => minN escluso
                sum = sum-minN;
                //Prezzo senza "prendere in prestito"
                // min+N1 + min+N2 + ... + min+Ni = min*mosse + sum
                int cp = mosse*minN + sum;
                //Prezzo prendendo in prestito:
                //   swap 2 volte tra 1 e min + mosse*1 + sum
                int prestito = 2*(1+minN) + mosse*1 + sum;

                prezzo += min(cp, prestito);
            }
            vis[i]=true;
        }
    }
    return prezzo;
}


