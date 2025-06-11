// //Reg:2020331024

// #include <bits/stdc++.h>
// using namespace std;

// struct Process
// {
//     string name;
//     int arrivalTime;
//     int burstTime;
// };

// float fcfs(vector<Process> &processes)
// {
//     int n = processes.size();
//     vector<int> waitingTime(n, 0);
//     vector<int> turnaroundTime(n, 0);
//     int totalWaitingTime = 0;
//     int currentTime = 0;

//     for (int i = 0; i < n; i++)
//     {
//         Process &p = processes[i];
//         currentTime = max(currentTime, p.arrivalTime);
//         waitingTime[i] = currentTime - p.arrivalTime;
//         totalWaitingTime += waitingTime[i];
//         turnaroundTime[i] = waitingTime[i] + p.burstTime;
//         currentTime += p.burstTime;
//     }

//     float avgWaitingTime = totalWaitingTime / static_cast<float>(n);
//     return avgWaitingTime;
// }

// int main()
// {
//     cout << "Enter the number of processes: ";
//     int n;
//     cin >> n;

//     vector<Process> processes;
//     for (int i = 0; i < n; i++)
//     {
//         cout << "Enter process name, arrival time, and burst time: ";
//         string name;
//         int arrivalTime, burstTime;
//         cin >> name >> arrivalTime >> burstTime;
//         processes.push_back({name, arrivalTime, burstTime});
//     }

//     float avgWaitingTime = fcfs(processes);
//     cout << "Average Waiting Time (FCFS): " << avgWaitingTime << endl;

//     return 0;
// }




// C++ program for implementation of FCFS 
// scheduling
#include<iostream>
using namespace std;

// Function to find the waiting time for all 
// processes
void findWaitingTime(int processes[], int n, int bt[], int wt[])
{
    // waiting time for first process is 0
    wt[0] = 0;

    // calculating waiting time
    for (int  i = 1; i < n ; i++ )
        wt[i] =  bt[i-1] + wt[i-1] ;
}

// Function to calculate turn around time
void findTurnAroundTime( int processes[], int n, int bt[], int wt[], int tat[])
{
    // calculating turnaround time by adding
    // bt[i] + wt[i]
    for (int  i = 0; i < n ; i++)
        tat[i] = bt[i] + wt[i];
}

//Function to calculate average time
void findavgTime( int processes[], int n, int bt[])
{
    int wt[n], tat[n], total_wt = 0, total_tat = 0;

    //Function to find waiting time of all processes
    findWaitingTime(processes, n, bt, wt);

    //Function to find turn around time for all processes
    findTurnAroundTime(processes, n, bt, wt, tat);

    //Display processes along with all details
    cout << "Processes  "<< " Burst time  " << " Waiting time  " << " Turn around time\n";

    // Calculate total waiting time and total turn 
    // around time
    for (int  i=0; i<n; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        cout << "   " << i+1 << "\t\t" << bt[i] <<"\t    "<< wt[i] <<"\t\t  " << tat[i] <<endl;
    }

    cout << "Average waiting time = " << (float)total_wt / (float)n;
    cout << "\nAverage turn around time = " << (float)total_tat / (float)n;
}

// Driver code
int main()
{
    //process id's
    int processes[] = { 1, 2, 3};
    int n = sizeof (processes) / sizeof (processes[0]);

    //Burst time of all processes
    int  burst_time[] = {10, 5, 8};

    findavgTime(processes, n,  burst_time);
    return 0;
}