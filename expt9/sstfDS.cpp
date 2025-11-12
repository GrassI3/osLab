#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>
#include <climits> 

using namespace std;

int findNearestTrack(int currentHead, const vector<int>& queue, vector<bool>& serviced) {
    int minDistance = INT_MAX;
    int minIndex = -1;

    for (int i = 0; i < queue.size(); ++i) {
        if (!serviced[i]) {
            int distance = abs(queue[i] - currentHead);
            if (distance < minDistance) {
                minDistance = distance;
                minIndex = i;
            }
        }
    }
    return minIndex;
}

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
    int numRequests = requestQueue.size();
    vector<bool> serviced(numRequests, false); 

    cout << "\nOUTPUT:\n" << endl;
    cout << "from\tto\tdistance" << endl;

    trackSequence << currentHead;

    for (int i = 0; i < numRequests; ++i) {
        int nearestIndex = findNearestTrack(currentHead, requestQueue, serviced);
        
        if (nearestIndex == -1) break; 

        int nextTrack = requestQueue[nearestIndex];
        serviced[nearestIndex] = true; 

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