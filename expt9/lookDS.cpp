#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    int n;
    long long totalHeadMovement = 0;
    cout << "Enter number of requests: ";
    if (!(cin >> n) || n <= 0) {
        cerr << "Invalid number of requests.\n";
        return 1;
    }

    vector<int> requests(n);
    cout << "Enter Request Queue (" << n << " values): ";
    for (int i = 0; i < n; ++i) cin >> requests[i];

    int head, prevHead;
    cout << "Enter Current Head Position: ";
    cin >> head;
    cout << "Enter Previous Head Position: ";
    cin >> prevHead;

    // Determine direction: 1 => moving right (increasing), 0 => moving left (decreasing)
    int direction = (head > prevHead) ? 1 : 0;

    // Sort requests
    sort(requests.begin(), requests.end());

    // Find the first request index that is >= head
    int pos = n; // default: no request >= head
    for (int i = 0; i < n; ++i) {
        if (requests[i] >= head) {
            pos = i;
            break;
        }
    }

    cout << "\n--- LOOK Disk Scheduling Algorithm ---\n\n";
    cout << "--------------------------------------------------\n";
    cout << "From\t\tTo\t\tDistance\n";
    cout << "--------------------------------------------------\n";

    vector<int> seekSequence;
    int current = head;

    if (direction == 1) { // moving right
        // serve requests to the right (>= head)
        for (int i = pos; i < n; ++i) {
            cout << current << "\t\t" << requests[i] << "\t\t" << llabs((long long)current - requests[i]) << "\n";
            totalHeadMovement += llabs((long long)current - requests[i]);
            current = requests[i];
            seekSequence.push_back(current);
        }
        // then reverse and serve left side
        for (int i = pos - 1; i >= 0; --i) {
            cout << current << "\t\t" << requests[i] << "\t\t" << llabs((long long)current - requests[i]) << "\n";
            totalHeadMovement += llabs((long long)current - requests[i]);
            current = requests[i];
            seekSequence.push_back(current);
        }
    } else { // moving left
        // serve requests to the left (< head)
        for (int i = pos - 1; i >= 0; --i) {
            cout << current << "\t\t" << requests[i] << "\t\t" << llabs((long long)current - requests[i]) << "\n";
            totalHeadMovement += llabs((long long)current - requests[i]);
            current = requests[i];
            seekSequence.push_back(current);
        }
        // then serve right side
        for (int i = pos; i < n; ++i) {
            cout << current << "\t\t" << requests[i] << "\t\t" << llabs((long long)current - requests[i]) << "\n";
            totalHeadMovement += llabs((long long)current - requests[i]);
            current = requests[i];
            seekSequence.push_back(current);
        }
    }

    cout << "--------------------------------------------------\n\n";
    // print full seek sequence starting with initial head
    cout << "Seek Sequence: " << head;
    for (size_t i = 0; i < seekSequence.size(); ++i) {
        cout << " -> " << seekSequence[i];
    }
    cout << "\nTotal Number of Head Movements: " << totalHeadMovement << "\n";

    return 0;
}
