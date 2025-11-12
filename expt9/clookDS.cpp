#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm> 

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

    cout << "Enter previous head position: ";
    cin >> previousHead;

    string direction = (currentHead > previousHead) ? "up" : "down";

    vector<int> downList, upList;
    for (int t : requestQueue) {
        if (t < currentHead) {
            downList.push_back(t);
        } else {
            upList.push_back(t);
        }
    }

    cout << "\nOUTPUT:\n" << endl;
    cout << "from\tto\tdistance" << endl;

    trackSequence << currentHead;

    if (direction == "down") {
        sort(downList.rbegin(), downList.rend()); 
        sort(upList.rbegin(), upList.rend());

        for (int nextTrack : downList) {
            int distance = abs(nextTrack - currentHead);
            totalMovements += distance;
            cout << currentHead << "\t" << nextTrack << "\t" << distance << endl;
            currentHead = nextTrack;
            trackSequence << "->" << currentHead;
        }
        for (int nextTrack : upList) {
            int distance = abs(nextTrack - currentHead);
            totalMovements += distance;
            cout << currentHead << "\t" << nextTrack << "\t" << distance << endl;
            currentHead = nextTrack;
            trackSequence << "->" << currentHead;
        }
    } else { 
        sort(upList.begin(), upList.end());
        sort(downList.begin(), downList.end());

        for (int nextTrack : upList) {
            int distance = abs(nextTrack - currentHead);
            totalMovements += distance;
            cout << currentHead << "\t" << nextTrack << "\t" << distance << endl;
            currentHead = nextTrack;
            trackSequence << "->" << currentHead;
        }
        for (int nextTrack : downList) {
            int distance = abs(nextTrack - currentHead);
            totalMovements += distance;
            cout << currentHead << "\t" << nextTrack << "\t" << distance << endl;
            currentHead = nextTrack;
            trackSequence << "->" << currentHead;
        }
    }

    cout << "\nTrack Sequence: " << trackSequence.str() << endl;
    cout << "Total head movements: " << totalMovements << endl;

    return 0;
}