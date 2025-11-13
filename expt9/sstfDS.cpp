#include <bits/stdc++.h>
#include <cmath> // For llabs
#include <climits> // For INT_MAX
using namespace std;

// --- LOGIC UNCHANGED ---
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
// --- END LOGIC ---

int main() {
    int currentHead, track;
    vector<int> requestQueue;
    long long totalMovements = 0; // Matched long long from example
    stringstream trackSequence;

    // --- INPUT SECTION (Unchanged) ---
    cout << "Enter request queue (-1 to exit): ";
    while (cin >> track && track != -1) {
        requestQueue.push_back(track);
    }
    cout << "Enter current head position: ";
    cin >> currentHead;

    int numRequests = requestQueue.size();
    vector<bool> serviced(numRequests, false);

    // --- OUTPUT SECTION (Formatted as requested) ---
    cout << "\n--- SSTF Disk Scheduling Algorithm ---\n\n";
    cout << "--------------------------------------------------\n";
    cout << "From\t\tTo\t\tDistance\n";
    cout << "--------------------------------------------------\n";

    trackSequence << currentHead; // Start sequence

    // --- LOGIC UNCHANGED (with formatting fixes) ---
    for (int i = 0; i < numRequests; ++i) {
        int nearestIndex = findNearestTrack(currentHead, requestQueue, serviced);
        if (nearestIndex == -1) break;

        int nextTrack = requestQueue[nearestIndex];
        serviced[nearestIndex] = true;
        
        long long distance = llabs((long long)nextTrack - currentHead); // Matched llabs
        totalMovements += distance;

        cout << currentHead << "\t\t" << nextTrack << "\t\t" << distance << "\n"; // Matched tabbing

        currentHead = nextTrack;
        trackSequence << " -> " << currentHead; // Added spaces
    }
    // --- END LOGIC ---

    cout << "--------------------------------------------------\n\n"; // Added footer
    
    // Matched final output format
    cout << "Seek Sequence: " << trackSequence.str() << "\n";
    cout << "Total Number of Head Movements: " << totalMovements << "\n";
    
    return 0;
}