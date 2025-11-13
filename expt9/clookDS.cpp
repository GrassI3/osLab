#include <bits/stdc++.h>
#include <cmath> // For llabs
using namespace std;

int main() {
    int blockSize, currentHead, previousHead, track;
    vector<int> requestQueue;
    long long totalMovements = 0; // Matched long long from example
    stringstream trackSequence;
    cout << "Enter request queue (-1 to exit): ";
    while (cin >> track && track != -1)
        requestQueue.push_back(track);
    cout << "Enter current head position: ";
    cin >> currentHead;
    cout << "Enter previous head position: ";
    cin >> previousHead;

    // --- LOGIC UNCHANGED ---
    string direction = (currentHead > previousHead) ? "up" : "down";
    vector<int> downList, upList;
    for (int t : requestQueue) {
        if (t < currentHead)
            downList.push_back(t);
        else
            upList.push_back(t);
    }
    // --- END LOGIC ---

    // --- OUTPUT SECTION (Formatted as requested) ---
    cout << "\n--- C-LOOK Disk Scheduling Algorithm ---\n\n";
    cout << "--------------------------------------------------\n";
    cout << "From\t\tTo\t\tDistance\n";
    cout << "--------------------------------------------------\n";

    trackSequence << currentHead; // Start sequence

    // --- LOGIC UNCHANGED (with formatting fixes) ---
    if (direction == "down") {
        sort(downList.rbegin(), downList.rend());
        sort(upList.rbegin(), upList.rend());

        for (int nextTrack : downList) {
            long long distance = llabs((long long)nextTrack - currentHead); // Matched llabs
            totalMovements += distance;
            cout << currentHead << "\t\t" << nextTrack << "\t\t" << distance << "\n"; // Matched tabbing
            currentHead = nextTrack;
            trackSequence << " -> " << currentHead; // Added spaces
        }
        for (int nextTrack : upList) {
            long long distance = llabs((long long)nextTrack - currentHead); // Matched llabs
            totalMovements += distance;
            cout << currentHead << "\t\t" << nextTrack << "\t\t" << distance << "\n"; // Matched tabbing
            currentHead = nextTrack;
            trackSequence << " -> " << currentHead; // Added spaces
        }
    } else { // direction == "up"
        sort(upList.begin(), upList.end());
        sort(downList.begin(), downList.end());

        for (int nextTrack : upList) {
            long long distance = llabs((long long)nextTrack - currentHead); // Matched llabs
            totalMovements += distance;
            cout << currentHead << "\t\t" << nextTrack << "\t\t" << distance << "\n"; // Matched tabbing
            currentHead = nextTrack;
            trackSequence << " -> " << currentHead; // Added spaces
        }
        for (int nextTrack : downList) {
            long long distance = llabs((long long)nextTrack - currentHead); // Matched llabs
            totalMovements += distance;
            cout << currentHead << "\t\t" << nextTrack << "\t\t" << distance << "\n"; // Matched tabbing
            currentHead = nextTrack;
            trackSequence << " -> " << currentHead; // Added spaces
        }
    }
    // --- END LOGIC ---

    cout << "--------------------------------------------------\n\n"; // Added footer
    
    // Matched final output format
    cout << "Seek Sequence: " << trackSequence.str() << "\n";
    cout << "Total Number of Head Movements: " << totalMovements << "\n";

    return 0;
}
