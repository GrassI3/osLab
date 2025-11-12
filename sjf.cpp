#include <bits/stdc++.h>
using namespace std;

struct Process {
    int AT, BT, CT, TAT, WT, idx;
};

int main() {
    int n;
    cout << "Enter The Num Of Processes: ";
    cin >> n;

    vector<Process> p(n);
    cout << "Enter The BT and AT of Processes:\n";
    for (int i = 0; i < n; i++) {
        cin >> p[i].BT >> p[i].AT;
        p[i].idx = i + 1;
    }

    vector<Process> done;
    int time = 0;
    vector<Process> gantt;

    sort(p.begin(), p.end(), [](auto &a, auto &b) {
        return a.AT < b.AT;
    });

    time = p[0].AT; 

    while (!p.empty()) {
        vector<int> available;
        for (int i = 0; i < p.size(); i++) {
            if (p[i].AT <= time) available.push_back(i);
        }   
        int best = available[0];
        for (int idx : available) {
            if (p[idx].BT < p[best].BT) best = idx;
        }
        time += p[best].BT;
        p[best].CT = time;
        p[best].TAT = p[best].CT - p[best].AT;
        p[best].WT = p[best].TAT - p[best].BT;
        done.push_back(p[best]);
        gantt.push_back(p[best]);
        p.erase(p.begin() + best);
    }

    double ATAT = 0, AWT = 0;
    for (auto &pr : done) {
        ATAT += pr.TAT;
        AWT += pr.WT;
    }
    ATAT /= n;
    AWT /= n;

    cout << "\nGantt Chart:\n|";
    cout << "\nGantt Chart:\n";
    cout << "|";
    for (auto &pr : gantt) {
        int len = pr.BT;
        cout << string(len, '_') << "P" << pr.idx << string(len, '_') << "|";
    }
    cout << "\n";

    cout << gantt[0].AT; 
    for (auto &pr : gantt) {
        int space = pr.BT * 2 + 3;
        cout << setw(space) << pr.CT;
    }
    cout << "\n";
    cout << "\n";

    cout << "\nPROCESS\tAT\tBT\tCT\tTAT\tWT\n";
    for (auto &pr : done) {
        cout << "P" << pr.idx << "\t" << pr.AT << "\t" << pr.BT << "\t"
             << pr.CT << "\t" << pr.TAT << "\t" << pr.WT << "\n";
    }

    cout << "\nATAT = " << fixed << setprecision(2) << ATAT;
    cout << "\nAWT = " << fixed << setprecision(2) << AWT << "\n";
}
