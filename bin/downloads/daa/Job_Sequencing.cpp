#include <bits/stdc++.h>
using namespace std;

// Class to represent a Job
class Job {
public:
    char id;        // Job ID (e.g., A, B, C)
    int deadline;   // Deadline of job
    int profit;     // Profit if job is completed before or on deadline

    Job(char id, int deadline, int profit) {
        this->id = id;
        this->deadline = deadline;
        this->profit = profit;
    }
};

// Comparator function to sort jobs by descending profit
bool compare(Job &a, Job &b) {
    return a.profit > b.profit;
}

// Class implementing Job Sequencing using Greedy Method
class JobSequencing {
public:
    void findJobSequence(vector<Job> &jobs) {
        // Step 1: Sort jobs by profit (high → low)
        sort(jobs.begin(), jobs.end(), compare);

        // Step 2: Find the maximum deadline
        int maxDeadline = 0;
        for (auto &job : jobs)
            maxDeadline = max(maxDeadline, job.deadline);

        // Step 3: Create time slots (empty initially)
        vector<char> schedule(maxDeadline + 1, '-');
        int totalProfit = 0;

        // Step 4: Assign jobs to slots
        for (auto &job : jobs) {
            // Find a free slot before or on the job's deadline
            for (int j = job.deadline; j > 0; j--) {
                if (schedule[j] == '-') {
                    schedule[j] = job.id;
                    totalProfit += job.profit;
                    break;
                }
            }
        }

        // Step 5: Display the job sequence and total profit
        cout << "\nJob sequence for maximum profit: ";
        for (int i = 1; i <= maxDeadline; i++) {
            if (schedule[i] != '-')
                cout << schedule[i] << " ";
        }
        cout << "\nTotal Profit = " << totalProfit << endl;
    }
};

// Main function
int main() {
    int n;
    cout << "Enter number of jobs: ";
    cin >> n;

    vector<Job> jobs;
    cout << "Enter Job ID, Deadline, and Profit for each job:\n";
    for (int i = 0; i < n; i++) {
        char id;
        int deadline, profit;
        cin >> id >> deadline >> profit;
        jobs.push_back(Job(id, deadline, profit));
    }

    JobSequencing js;
    js.findJobSequence(jobs);

    return 0;
}

// 6
// A 2 100
// B 1 19
// C 2 27
// D 1 25
// E 3 15
// F 2 30
