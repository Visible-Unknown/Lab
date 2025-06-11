#include <iostream>
#include <vector>

using namespace std;

// Function to check if the system is in a safe state
bool isSafe(vector<vector<int>> &allocation, vector<vector<int>> &max, vector<vector<int>> &need, vector<int> &available, int process, int resource, bool printSafeSequence = true) 
{
    vector<int> work = available;
    vector<bool> finish(process, false);
    vector<int> safeSequence(process);

    int count = 0;
    while (count < process) {
        bool found = false;
        for (int p = 0; p < process; ++p) {
            if (!finish[p]) {
                int r;
                for (r = 0; r < resource; ++r) {
                    if (need[p][r] > work[r]) {
                        break;
                    }
                }
                if (r == resource) {
                    for (int k = 0; k < resource; ++k) {
                        work[k] += allocation[p][k];
                    }
                    safeSequence[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            if (printSafeSequence) {
                cout << "System is not in a safe state" << endl;
            }
            return false;
        }
    }
    if (printSafeSequence) {
        cout << "System is in a safe state.\nSafe sequence is: ";
        for (int i = 0; i < process; ++i) {
            cout << safeSequence[i] << " ";
        }
        cout << endl;
    }
    return true;
}

// Function to request resources
bool requestResources(vector<vector<int>> &allocation, vector<vector<int>> &max, vector<vector<int>> &need, vector<int> &available, int process, int resource, int processNum, vector<int> &request) {
    for (int i = 0; i < resource; ++i) {
        if (request[i] > need[processNum][i]) {
            cout << "Error: Process has exceeded its maximum claim." << endl;
            return false;
        }
    }

    for (int i = 0; i < resource; ++i) {
        if (request[i] > available[i]) {
            cout << "Resources are not available." << endl;
            return false;
        }
    }

    for (int i = 0; i < resource; ++i) {
        available[i] -= request[i];
        allocation[processNum][i] += request[i];
        need[processNum][i] -= request[i];
    }

    if (isSafe(allocation, max, need, available, process, resource, false)) {
        return true;
    } else {
        for (int i = 0; i < resource; ++i) {
            available[i] += request[i];
            allocation[processNum][i] -= request[i];
            need[processNum][i] += request[i];
        }
        return false;
    }
}

int main() {
    int process = 5; // Number of processes
    int resource = 3; // Number of resources

    vector<vector<int>> allocation = { {0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2} };
    vector<vector<int>> max = { {7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3} };
    vector<vector<int>> need(process, vector<int>(resource));
    vector<int> available = {3, 3, 2};

    // Calculate need matrix
    for (int i = 0; i < process; ++i) {
        for (int j = 0; j < resource; ++j) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Check system state initially
    isSafe(allocation, max, need, available, process, resource);

    // Example request for process 1
    vector<int> request = {1, 0, 2};
    if (requestResources(allocation, max, need, available, process, resource, 1, request)) {
        cout << "Request granted." << endl;
    } else {
        cout << "Request denied." << endl;
    }

    return 0;
}
