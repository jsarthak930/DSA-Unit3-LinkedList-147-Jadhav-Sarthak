
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct Process
{
    string id;
    int burstTime;
    int remainingTime;
    int waitingTime;
    int turnaroundTime;
    Process *next;
};

Process* createProcess(string id, int burst)
{
    Process *p = new Process;

    p->id = id;
    p->burstTime = burst;
    p->remainingTime = burst;
    p->waitingTime = 0;
    p->turnaroundTime = 0;
    p->next = NULL;

    return p;
}

void addProcess(Process *&head, string id, int burst)
{
    Process *p = createProcess(id, burst);

    if (head == NULL)
    {
        head = p;
        p->next = head;
    }
    else
    {
        Process *temp = head;

        while (temp->next != head)
        {
            temp = temp->next;
        }

        temp->next = p;
        p->next = head;
    }

    cout << "Process added successfully.\n";
}

void displayProcesses(Process *head)
{
    if (head == NULL)
    {
        cout << "No processes available.\n";
        return;
    }

    Process *temp = head;

    cout << "\nProcess\tBurst Time\n";

    do
    {
        cout << temp->id << "\t"
             << temp->burstTime << endl;

        temp = temp->next;
    }
    while (temp != head);
}

void simulate(Process *head, int quantum)
{
    if (head == NULL || quantum <= 0)
    {
        cout << "Add processes and enter a valid quantum.\n";
        return;
    }

    Process *p = head;
    int currentTime = 0;
    int completed = 0;
    int total = 0;
    int count = 0;

    // Count the processes
    Process *temp = head;

    do
    {
        count++;
        temp = temp->next;
    }
    while (temp != head);

    cout << "\nGantt Chart:\n";
    cout << "0";

    while (completed < count)
    {
        if (p->remainingTime > 0)
        {
            int runTime;

            if (p->remainingTime > quantum)
                runTime = quantum;
            else
                runTime = p->remainingTime;

            p->remainingTime -= runTime;
            currentTime += runTime;

            cout << " --" << p->id
                 << "-- " << currentTime;

            if (p->remainingTime == 0)
            {
                p->turnaroundTime = currentTime;
                p->waitingTime =
                    p->turnaroundTime - p->burstTime;

                completed++;
            }
        }

        p = p->next;
    }

    cout << "\n\nProcess\tBurst\tWaiting\tTurnaround\n";

    p = head;

    do
    {
        cout << p->id << "\t"
             << p->burstTime << "\t"
             << p->waitingTime << "\t"
             << p->turnaroundTime << endl;

        total += p->waitingTime;
        temp = p;
        p = p->next;
    }
    while (p != head);

    cout << fixed << setprecision(2);

    cout << "\nAverage Waiting Time: "
         << (double)total / count << endl;

    double totalTurnaround = 0;
    p = head;

    do
    {
        totalTurnaround += p->turnaroundTime;
        p = p->next;
    }
    while (p != head);

    cout << "Average Turnaround Time: "
         << totalTurnaround / count << endl;

    // Reset remaining times for another simulation
    p = head;

    do
    {
        p->remainingTime = p->burstTime;
        p = p->next;
    }
    while (p != head);
}

int main()
{
    Process *head = NULL;
    int choice;
    int burst;
    int quantum;
    string id;

    do
    {
        cout << "\n--- Round Robin CPU Scheduler ---\n";
        cout << "1. Add Process\n";
        cout << "2. Display Processes\n";
        cout << "3. Simulate Scheduling\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                cout << "Enter Process ID: ";
                cin >> id;

                cout << "Enter Burst Time: ";
                cin >> burst;

                if (burst <= 0)
                {
                    cout << "Burst time must be positive.\n";
                    break;
                }

                addProcess(head, id, burst);
                break;

            case 2:
                displayProcesses(head);
                break;

            case 3:
                cout << "Enter Time Quantum: ";
                cin >> quantum;

                simulate(head, quantum);
                break;

            case 4:
                cout << "Exiting program.\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 4);

    return 0;
}
