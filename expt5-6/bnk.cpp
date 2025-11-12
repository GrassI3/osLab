#include <iostream>
#include <iomanip>
using namespace std;
int m, n, flag;
int allocation[10][10], max_v[10][10], need[10][10];
int available[10];

void safety() {
    int safe[10], work[10];
    bool finish[10];
    for (int i = 0; i < n; i++) {
        safe[i] = -1;
        finish[i] = false;
    }
    for (int i = 0; i < m; i++)
        work[i] = available[i];
    
    int count = 0;
    while (count < n) {
        bool found = false;
        
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < m; j++)
                    if (need[i][j] > work[j])
                        break;
                
                if (j == m) {
                    for (int k = 0; k < m; k++)
                        work[k] += allocation[i][k];
                    safe[count] = i;
                    finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }
        
        if (!found) {
            flag = 1;
            cout << "\nNo Safe sequence exists" << endl;
            return;
        }
    }
    
    flag = 0;
    cout << "\nSafe Sequence: ";
    for (int j = 0; j < n; j++)
        cout << safe[j] << " ";
    cout << endl;
}

void display() {
    int k = 0;
    cout << "\nAllocation\tMax\tAvailable\tNeed" << endl;
    for (int i = 0; i < n; i++) {
        cout << setiosflags(ios::right) << " ";
        for (int j = 0; j < m; j++)
            cout << allocation[i][j] << " ";
        cout << setw(9);
        for (int j = 0; j < m; j++)
            cout << max_v[i][j] << " ";
        cout << setw(6);
        for (int j = 0; j < m; j++) {
            if (k == 1) {
                cout << "  ";
                continue;
            } else
                cout << available[j] << " ";
        }
        if (k == 1)
            cout << " ";
        cout << setw(8);
        for (int j = 0; j < m; j++)
            cout << need[i][j] << " ";
        k = 1;
        cout << endl;
    }
}

int main() {
    cout << "\nEnter the number of Processes: ";
    cin >> n;
    cout << "\nEnter the number of Resource types: ";
    cin >> m;
    cout << "\nEnter Allocated Resources for each process:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "P" << i << ": ";
        for (int j = 0; j < m; j++)
            cin >> allocation[i][j];
    }
    cout << "\nEnter max_v Resources for each process:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "R" << i + 1 << ": ";
        for (int j = 0; j < m; j++)
            cin >> max_v[i][j];
    }
    cout << "\nEnter Available Resources:" << endl;
    for (int i = 0; i < m; i++)
        cin >> available[i];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max_v[i][j] - allocation[i][j];
    display();
    safety();
    
    char ans = 'y';
    do {
        int request[10], p;
        cout << "\nEnter Process Number: ";
        cin >> p;
        
        if (p < 0 || p >= n) {
            cout << "\nInvalid process number." << endl;
            cout << "\nTry another Process? (Y/N): ";
            cin >> ans;
            continue;
        }
        
        cout << "Enter Request: ";
        for (int i = 0; i < m; i++)
            cin >> request[i];
        
        // Check if request exceeds need
        bool exceeds_need = false;
        for (int i = 0; i < m; i++) {
            if (request[i] > need[p][i]) {
                cout << "\nProcess P" << p << " is asking for more than its declared maximum need." << endl;
                cout << "Process must wait -- resources are busy.\nRequest cannot be granted." << endl;
                exceeds_need = true;
                break;
            }
        }
        
        if (exceeds_need) {
            cout << "\nCurrent state unchanged:" << endl;
            display();
            cout << "\nTry another Process? (Y/N): ";
            cin >> ans;
            continue;
        }
        
        // Check if resources are available
        bool not_available = false;
        for (int i = 0; i < m; i++) {
            if (request[i] > available[i]) {
                cout << "\nResources not available right now." << endl;
                cout << "Process P" << p << " must wait.\nRequest cannot be granted." << endl;
                not_available = true;
                break;
            }
        }
        
        if (not_available) {
            cout << "\nCurrent state unchanged:" << endl;
            display();
            cout << "\nTry another Process? (Y/N): ";
            cin >> ans;
            continue;
        }
        
        // Check if request will make all available resources zero
        bool all_zero = true;
        for (int i = 0; i < m; i++) {
            if (available[i] - request[i] != 0) {
                all_zero = false;
                break;
            }
        }
        
        if (all_zero) {
            cout << "\nRequest violates Banker's algorithm!" << endl;
            cout << "Process must wait -- resources are busy.\nRequest cannot be granted." << endl;
            cout << "\nCurrent state unchanged:" << endl;
            display();
            cout << "\nTry another Process? (Y/N): ";
            cin >> ans;
            continue;
        }
        
        // Save old state
        int old_available[10], old_allocation[10][10], old_need[10][10];
        for (int i = 0; i < m; i++)
            old_available[i] = available[i];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                old_allocation[i][j] = allocation[i][j];
                old_need[i][j] = need[i][j];
            }
        
        // Temporarily allocate resources
        for (int i = 0; i < m; i++) {
            available[i] -= request[i];
            allocation[p][i] += request[i];
            need[p][i] -= request[i];
        }
        
        cout << "\nTemporary State After Request:" << endl;
        int k = 0;
        cout << "\nAllocation\tAvailable\tNeed" << endl;
        for (int i = 0; i < n; i++) {
            cout << setiosflags(ios::right) << " ";
            for (int j = 0; j < m; j++)
                cout << allocation[i][j] << " ";
            cout << setw(6);
            for (int j = 0; j < m; j++) {
                if (k == 1) {
                    cout << "  ";
                    continue;
                } else
                    cout << available[j] << " ";
            }
            if (k == 1)
                cout << " ";
            cout << setw(8);
            for (int j = 0; j < m; j++)
                cout << need[i][j] << " ";
            k = 1;
            cout << endl;
        }
        
        safety();
        
        if (flag == 1) {
            cout << "\nRequest cannot be granted (unsafe state)." << endl;
            // Restore previous state
            for (int i = 0; i < m; i++)
                available[i] = old_available[i];
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++) {
                    allocation[i][j] = old_allocation[i][j];
                    need[i][j] = old_need[i][j];
                }
            cout << "\nState Restored:" << endl;
            display();
        } else {
            cout << "\nSafe Sequence Exists. Request granted.\nSnapshot after request:" << endl;
            display();
        }
        
        cout << "\nTry another Process? (Y/N): ";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');
    
    return 0;
}