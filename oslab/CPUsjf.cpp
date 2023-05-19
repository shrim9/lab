#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n = 4;
    vector<int> id = {1, 2, 3, 4};
    vector<int> bt = {9, 2, 5, 7};
    // Sorting the processes according to the Burst Time
    for(int i=0; i<n; ++i){
        for(int j=i+1; j<n; ++j){
            if(bt[j]<bt[i]){
                // Swapping burst time
                int temp = bt[j];
                bt[j] = bt[i];
                bt[i] = temp;
                // Swapping process id
                temp = id[j];
                id[j] = id[i];
                id[i] = temp;
            }
        }
        
    }
    vector<int> ct(n+1);
    ct[0] = 0;
    for(int i=1; i<=n; ++i){
        ct[i] = ct[i-1] + bt[i-1];
    }
    vector<int> wt(n);
    for(int i=0; i<n; ++i){
        wt[i] = ct[i+1] - bt[i];
    }
    cout<<"Gantt Chart for SJF (Non-Preemptive) :"<<endl;
    cout<<"ID\tBT\tCT\tWT"<<endl;
    for(int i=0; i<n; ++i){
        cout<<id[i]<<"\t"<<bt[i]<<"\t"<<ct[i+1]<<"\t"<<wt[i]<<endl;
    }
    return 0;
}
/*#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    
    vector<int> id(n);
    vector<int> bt(n);
    
    cout << "Enter the process IDs and burst times:\n";
    for (int i = 0; i < n; ++i) {
        cin >> id[i] >> bt[i];
    }

    // Sorting the processes according to the Burst Time
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (bt[j] < bt[i]) {
                swap(bt[j], bt[i]);
                swap(id[j], id[i]);
            }
        }
    }

    vector<int> ct(n + 1);
    ct[0] = 0;
    for (int i = 1; i <= n; ++i) {
        ct[i] = ct[i - 1] + bt[i - 1];
    }

    vector<int> wt(n);
    for (int i = 0; i < n; ++i) {
        wt[i] = ct[i + 1] - bt[i];
    }

    double avgTAT = static_cast<double>(ct[n]) / n;
    double avgWT = static_cast<double>(accumulate(wt.begin(), wt.end(), 0)) / n;

    cout << "Gantt Chart for SJF (Non-Preemptive):\n";
    cout << "ID\tBT\tCT\tWT\n";
    for (int i = 0; i < n; ++i) {
        cout << id[i] << "\t" << bt[i] << "\t" << ct[i + 1] << "\t" << wt[i] << "\n";
    }

    cout << "Average Turnaround Time: " << avgTAT << "\n";
    cout << "Average Waiting Time: " << avgWT << "\n";

    return 0;
}
*/