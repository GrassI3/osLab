#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

// FIFO Page Replacement Algorithm with Table Output
void fifo(vector<int> pages, int capacity) {
    vector<vector<int>> table(capacity, vector<int>(pages.size(), -1));
    vector<int> frames;
    vector<bool> pageFaults(pages.size(), false);
    int faultCount = 0;
    int index = 0; // Points to the oldest page
    
    for(int i = 0; i < pages.size(); i++) {
        bool found = false;
        
        // Check if page is already in frames
        for(int j = 0; j < frames.size(); j++) {
            if(frames[j] == pages[i]) {
                found = true;
                break;
            }
        }
        
        if(!found) {
            pageFaults[i] = true;
            faultCount++;
            
            if(frames.size() < capacity) {
                frames.push_back(pages[i]);
            } else {
                frames[index] = pages[i];
                index = (index + 1) % capacity;
            }
        }
        
        // Store current frame state in table
        for(int j = 0; j < frames.size(); j++) {
            table[j][i] = frames[j];
        }
    }
    
    // Display the table
    cout << "\n========== FIFO PAGE REPLACEMENT TABLE ==========\n\n";
    
    // Print page reference string
    cout << "Pages:      ";
    for(int i = 0; i < pages.size(); i++) {
        cout << setw(4) << pages[i];
    }
    cout << "\n";
    cout << string(12 + pages.size() * 4, '-') << "\n";
    
    // Print frames
    for(int i = 0; i < capacity; i++) {
        cout << "Frame " << i << ":   ";
        for(int j = 0; j < pages.size(); j++) {
            if(table[i][j] == -1)
                cout << setw(4) << "-";
            else
                cout << setw(4) << table[i][j];
        }
        cout << "\n";
    }
    
    cout << string(12 + pages.size() * 4, '-') << "\n";
    
    // Print page faults
    cout << "Fault:      ";
    for(int i = 0; i < pages.size(); i++) {
        if(pageFaults[i])
            cout << setw(4) << "F";
        else
            cout << setw(4) << "-";
    }
    cout << "\n\n";
    
    cout << "================================================" << endl;
    cout << "Total Page Faults: " << faultCount << endl;
    cout << "Total Page Hits: " << (pages.size() - faultCount) << endl;
    cout << "Hit Ratio: " << fixed << setprecision(2) 
         << ((float)(pages.size() - faultCount) / pages.size() * 100) << "%" << endl;
    cout << "================================================" << endl;
}

int main() {
    int n, capacity;
    
    cout << "================================================" << endl;
    cout << "     FIFO PAGE REPLACEMENT ALGORITHM" << endl;
    cout << "================================================" << endl;
    
    cout << "\nEnter number of frames (cache size): ";
    cin >> capacity;
    
    cout << "Enter number of pages in reference string: ";
    cin >> n;
    
    vector<int> pages(n);
    cout << "Enter the page reference string: ";
    for(int i = 0; i < n; i++) {
        cin >> pages[i];
    }
    
    // Run FIFO algorithm
    fifo(pages, capacity);
    
    return 0;
}