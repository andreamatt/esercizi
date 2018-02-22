#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int main() {

    srand(100);

    ofstream output("output.txt");

    float G = 0;
    float K = 4;
    float a = 0.125;
    float b = 0.25;
    float RTT = 150;
    float SRTT = RTT;
    float RTTVAR = SRTT/2;
    float RTO = SRTT + max(G, K*RTTVAR);

    for(int i=0; i<100; i++){
        output<<i<<","<<RTT<<","<<SRTT<<","<<RTTVAR<<","<<RTO<<endl;
        RTT = 100 + ((rand()%10 != 0) ? (rand()%21) : (rand()%100 + 100));
        RTTVAR = round((1-b)*RTTVAR + b*fabs(SRTT-RTT));
        SRTT = round((1-a)*SRTT + a*RTT);
        RTO = round(SRTT + max(G, K*RTTVAR));
    }




    return 0;
}