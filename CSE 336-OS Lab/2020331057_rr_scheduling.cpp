#include<bits/stdc++.h>
using namespace std;

struct Process {
    int pid;           
    int burstTime;     
    int remainingTime; 
};

void roundRobinScheduling(vector<Process>& processes, int quantum) {
    int n = processes.size();
    queue<Process> readyQueue;

    for (int i = 0; i < n; ++i) {
        processes[i].remainingTime = processes[i].burstTime;
        readyQueue.push(processes[i]);
    }

    int currentTime = 0;
    vector<int> waitingTime(n, 0);

    while (!readyQueue.empty()) {
        Process currentProcess = readyQueue.front();
        readyQueue.pop();

        int executionTime = min(quantum, currentProcess.remainingTime);
        currentTime += executionTime;
        currentProcess.remainingTime -= executionTime;

        if (currentProcess.remainingTime > 0) {
            readyQueue.push(currentProcess); 
        } else {
            int turnaroundTime = currentTime - currentProcess.burstTime;
            waitingTime[currentProcess.pid - 1] = turnaroundTime; 
        }
    }

    vector<int> turnaroundTime(n, 0);
    for (int i = 0; i < n; ++i) {
        turnaroundTime[i] = processes[i].burstTime + waitingTime[i];
    }

    cout << "\nProcesses   Burst time   Waiting time   Turnaround time\n";
    for (int i = 0; i < n; ++i) {
        cout << " " << processes[i].pid << "\t\t" << processes[i].burstTime << "\t\t"
             << waitingTime[i] << "\t\t " << turnaroundTime[i] << endl;
    }

    double totalWaitingTime = 0, totalTurnaroundTime = 0;
    for (int i = 0; i < n; ++i) {
        totalWaitingTime += waitingTime[i];
        totalTurnaroundTime += turnaroundTime[i];
    }

    double avgWaitingTime = totalWaitingTime / n;
    double avgTurnaroundTime = totalTurnaroundTime / n;

    cout << "\nAverage waiting time = " << avgWaitingTime << endl;
    cout << "Average turnaround time = " << avgTurnaroundTime << endl;
}

int main() {
    vector<Process> processes = {
        {1, 10, 0},
        {2, 5, 0},
        {3, 8, 0}
    };

    int quantum = 2;

    cout << "Round-Robin Scheduling Simulation (Time Quantum = " << quantum << ")" << endl;
    roundRobinScheduling(processes, quantum);

    return 0;
}
