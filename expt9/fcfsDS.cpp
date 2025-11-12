#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

int main() {
    int blockSize, currentHead, previousHead, track;
    vector<int> requestQueue;
    int totalMovements = 0;
    stringstream trackSequence;

    cout << "Enter block size: ";
    cin >> blockSize; 

    cout << "Enter request queue (-1 to exit): ";
    while (cin >> track && track != -1) {
        requestQueue.push_back(track);
    }

    cout << "Enter current head position: ";
    cin >> currentHead;

    cout << "\nOUTPUT:\n" << endl;
    cout << "from\tto\tdistance" << endl;

    trackSequence << currentHead; 

    for (int nextTrack : requestQueue) {
        int distance = abs(nextTrack - currentHead);
        totalMovements += distance;

        cout << currentHead << "\t" << nextTrack << "\t" << distance << endl;

        currentHead = nextTrack;
        trackSequence << "->" << currentHead;
    }

    cout << "\nTrack Sequence: " << trackSequence.str() << endl;
    cout << "Total head movements: " << totalMovements << endl;

    return 0;
}