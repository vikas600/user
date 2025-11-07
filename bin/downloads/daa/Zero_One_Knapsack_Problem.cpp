#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ------------------- Recursive -------------------
int solveUsingRec(vector<int>& val, vector<int>& wt, int capacity, int index) {
    if (index == 0) {
        if (wt[0] <= capacity)
            return val[0];
        else
            return 0;
    }

    int incl = 0;
    if (wt[index] <= capacity)
        incl = val[index] + solveUsingRec(val, wt, capacity - wt[index], index - 1);

    int excl = solveUsingRec(val, wt, capacity, index - 1);

    return max(incl, excl);
}

// ------------------- Memoization -------------------
int solveUsingMem(vector<int>& val, vector<int>& wt, int capacity, int index, vector<vector<int>>& dp) {
    if (index == 0) {
        if (wt[0] <= capacity)
            return val[0];
        else
            return 0;
    }

    if (dp[index][capacity] != -1)
        return dp[index][capacity];

    int incl = 0;
    if (wt[index] <= capacity)
        incl = val[index] + solveUsingMem(val, wt, capacity - wt[index], index - 1, dp);

    int excl = solveUsingMem(val, wt, capacity, index - 1, dp);

    dp[index][capacity] = max(incl, excl);
    return dp[index][capacity];
}

// ------------------- Tabulation -------------------
int solveUsingTab(int capacity, vector<int>& wt, vector<int>& val) {
    int n = val.size();
    vector<vector<int>> dp(n, vector<int>(capacity + 1, 0));

    // Base case: fill first row (index 0)
    for (int w = wt[0]; w <= capacity; w++)
        dp[0][w] = val[0];

    // Build table
    for (int index = 1; index < n; index++) {
        for (int w = 0; w <= capacity; w++) {
            int incl = 0;
            if (wt[index] <= w)
                incl = val[index] + dp[index - 1][w - wt[index]];

            int excl = dp[index - 1][w];
            dp[index][w] = max(incl, excl);
        }
    }

    return dp[n - 1][capacity];
}

// ------------------- Main -------------------
int main() {
    int n, W;
    cout << "Enter number of items: ";
    cin >> n;

    vector<int> val(n), wt(n);
    cout << "Enter values of items:\n";
    for (int i = 0; i < n; i++)
        cin >> val[i];

    cout << "Enter weights of items:\n";
    for (int i = 0; i < n; i++)
        cin >> wt[i];

    cout << "Enter capacity of knapsack: ";
    cin >> W;

    int index = n - 1;

    // You can choose any method below 👇

    // int maxValue = solveUsingRec(val, wt, W, index);

    // vector<vector<int>> dp(n, vector<int>(W + 1, -1));
    // int maxValue = solveUsingMem(val, wt, W, index, dp);

    int maxValue = solveUsingTab(W, wt, val);

    cout << "\nMaximum value in Knapsack = " << maxValue << endl;
    return 0;
}



// No of items = 3
// val [1 ,2 , 3];
// wt = [4 , 5 ,1];
// capacity = 4
// Output must be 3