#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

// Optimal Page Replacement Algorithm with Limited Lookahead
void optimal(vector<int> pages, int capacity, int lookahead = 3) {
    vector<vector<int>> table(capacity, vector<int>(pages.size(), -1));
    vector<int> frames;
    vector<bool> pageFaults(pages.size(), false);
    int faultCount = 0;
    
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
                // Find the page to replace (used farthest in future within lookahead window)
                int farthest = i + 1, replaceIndex = 0;
                int lookupLimit = min((int)pages.size(), i + 1 + lookahead); // Look only 'lookahead' pages ahead
                
                for(int j = 0; j < frames.size(); j++) {
                    int k;
                    for(k = i + 1; k < lookupLimit; k++) {
                        if(frames[j] == pages[k])
                            break;
                    }
                    
                    // If page not found within lookahead window, replace it
                    if(k == lookupLimit) {
                        replaceIndex = j;
                        break;
                    }
                    
                    if(k > farthest) {
                        farthest = k;
                        replaceIndex = j;
                    }
                }
                
                frames[replaceIndex] = pages[i];
            }
        }
        
        // Store current frame state in table
        for(int j = 0; j < frames.size(); j++) {
            table[j][i] = frames[j];
        }
    }
    
    // Display the table
    cout << "\n========== OPTIMAL PAGE REPLACEMENT TABLE ==========\n";
    cout << "           (Lookahead Window: " << lookahead << " pages)\n\n";
    
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
    int n, capacity, lookahead;
    
    cout << "================================================" << endl;
    cout << "    OPTIMAL PAGE REPLACEMENT ALGORITHM" << endl;
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
    
    cout << "Enter lookahead window size: ";
    cin >> lookahead;
    
    // Run Optimal algorithm with limited lookahead
    optimal(pages, capacity, lookahead);
    
    return 0;
}