#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <iomanip>
using namespace std;

struct Process
{
    string name;
    int arrival_time, burst_time, turn_arround, waiting_time, completion_time, priority, quantum;
};
bool compare_time(Process p1, Process p2)
{
    return p1.arrival_time < p2.arrival_time; // return true if this condition meets
}
bool compare_priority(Process p1, Process p2)
{
    return p1.priority < p2.priority; // Lower number = higher priority
}
void display_avg(string algo_name, vector<Process> p)
{
    double total_wt = 0, total_tat = 0;
    for (int i = 0; i < p.size(); i++)
    {
        total_wt += p[i].waiting_time;
        total_tat += p[i].turn_arround;
    }
    double avg_wt = total_wt / p.size();
    double avg_tat = total_tat / p.size();

    // cout << left << setw(15) << "Algorithm" 
    //      << setw(15) << "Avg WT" 
    //      << setw(15) << "Avg TAT" << endl;
    // cout << "---------------------------------------------" << endl;
    cout<<left<<setw(15)<<algo_name<<setw(15)<<avg_wt<<setw(15)<<setw(15)<<avg_tat<<endl;
}
void display_process_detail(vector<Process> p)
{
    cout << "Process\tArrivalTime\tBurstTime\tCompletionTime\tTurnaroundTime\tWaitingTime" << endl;
    for (int i = 0; i < p.size(); i++)
    {
        cout << p[i].name << "\t" << p[i].arrival_time << "\t" << p[i].burst_time << "\t\t" << p[i].completion_time << "\t\t\t" << p[i].turn_arround << "\t\t" << p[i].waiting_time << endl;
    }
}
void FCFS(vector<Process> p, int n)
{
    sort(p.begin(), p.end(), compare_time);
    p[0].completion_time = p[0].arrival_time + p[0].burst_time;
    p[0].turn_arround = p[0].completion_time - p[0].arrival_time;
    p[0].waiting_time = p[0].turn_arround - p[0].burst_time;

    for (int i = 1; i < n; i++)
    {
        p[i].completion_time = max(p[i].arrival_time, p[i-1].completion_time) + p[i].burst_time;
        // cout<<"\nCurrent: "<<p[i].completion_time;
        p[i].turn_arround = p[i].completion_time - p[i].arrival_time;
        // cout<<"\nturn: "<<p[i].turn_arround;
        p[i].waiting_time = p[i].turn_arround - p[i].burst_time;
        // cout<<"\nwaiting: "<<p[i].waiting_time;
    }
    display_avg("FCFS", p);
}

void SJF(vector<Process> p, int n)
{
    int remaining[n];
    for (int i = 0; i < n; i++)
    {
        remaining[i] = p[i].burst_time; // copy burst time
    }
    int currentTime = 0;
    int complete = 0;       // counter until process of remaining does not finish
    int shortest = 0;       // index of min from ready_queue/remaining
    int minBurst = INT_MAX; // value of shortest index
    while (complete < n)
    {
        minBurst = INT_MAX; // reset
        int found = 0;
        for (int i = 0; i < n; i++)
        {
            // ariival_time<=current if ct=5 then all at before 5 added to ready queue
            // to find min from ready queue check with previous min
            // >0 becaude always by decremention count that remaining[i] will be 0 so it should not be stored in min
            if (p[i].arrival_time <= currentTime && remaining[i] < minBurst && remaining[i] > 0)
            {
                minBurst = remaining[i];
                shortest = i; // index of min elelement
                found = 1;
            }
        }
        if (found == 0)
        {
            currentTime++; // No process is ready, increment time
            continue;
        }
        remaining[shortest]--;
        if (remaining[shortest] == 0)
        {
            complete++;                                    // since one process completed
            p[shortest].completion_time = currentTime + 1; // since we are stopping above before zero
            p[shortest].turn_arround = p[shortest].completion_time - p[shortest].arrival_time;
            p[shortest].waiting_time = p[shortest].turn_arround - p[shortest].burst_time;
        }
        currentTime++; // as remaining[shortest]-- currentTime++
    }

    // display_process_detail(p);
    display_avg("SJF", p);
}

void RoundRobin(vector<Process> p, int n, int quantum)
{
    int remaining[n];
    for (int i = 0; i < n; i++)
    {
        remaining[i] = p[i].burst_time;
    }
    int currentTime = 0, complete = 0;

    while (1)
    {
        bool done = true;
        for (int i = 0; i < n; i++)
        {
            if (remaining[i] > 0)
            {
                done = false;
                if (remaining[i] > quantum)
                {
                    currentTime += quantum;
                    remaining[i] -= quantum;
                }
                else
                {
                    currentTime += remaining[i];
                    p[i].completion_time = currentTime;
                    p[i].turn_arround = p[i].completion_time - p[i].arrival_time;
                    p[i].waiting_time = p[i].turn_arround - p[i].burst_time;
                    remaining[i] = 0;
                }
            }
        }
        if (done)
            break;
    }

    // display_process_detail(p);
    display_avg("Round Robin", p);
}

void PriorityScheduling(vector<Process> p, int n)
{
    sort(p.begin(), p.end(), compare_time);

    p[0].completion_time = p[0].arrival_time + p[0].burst_time; // as for some case 0 may not be the arrival time
    p[0].turn_arround = p[0].completion_time - p[0].arrival_time;
    p[0].waiting_time = p[0].turn_arround - p[0].burst_time;
    int currentTime = p[0].completion_time; // keep track of previos completion

    for (int i = 1; i < n; i++)
    {

        sort(p.begin() + i, p.end(), compare_priority); // since only the process that arrived should be compared
        if (currentTime < p[i].arrival_time)            // if completion is at 10 and arrival at 15 and bt=5 then completion= 15+5
            currentTime = p[i].arrival_time;

        p[i].completion_time = currentTime + p[i].burst_time;
        p[i].turn_arround = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turn_arround - p[i].burst_time;
        currentTime = p[i].completion_time;
    }
    // display_process_detail(p);
    display_avg("Priority", p);
}

int main()
{

    int n;

    cout << "\nEnter the number of process: ";
    cin >> n;
    vector<Process> prc(n);
    cout << "\nEnter the Credentials: ";
    for (int i = 0; i < n; i++)
    {
        cout << "\nName: ";
        cin >> prc[i].name;
        cout << "\nArrival time: ";
        cin >> prc[i].arrival_time;
        cout << "\nBurst time: ";
        cin >> prc[i].burst_time;
        cout << "\nPriority: ";
        cin >> prc[i].priority;
    }
    for (int i = 0; i < n; i++)
    {
        cout << prc[i].name << endl;
    }
    int q;
    cout << "\nEnter quantum: ";
    cin >> q;
    cout << left << setw(15) << "Algorithm" 
         << setw(15) << "Avg WT" 
         << setw(15) << "Avg TAT" << endl;
    cout << "---------------------------------------------" << endl;
    FCFS(prc,n);
    SJF(prc,n);
    PriorityScheduling(prc,n);
    RoundRobin(prc, n, q);
    return 0;
}