#include <bits/stdc++.h>
using namespace std;

class Item {
public:
    int value, weight;
    double ratio;
};

class Node {
public:
    int level, profit, weight;
    double bound;
};

// Comparison class for least-cost priority queue
class CompareCost {
public:
    bool operator()(const Node &a, const Node &b) {
        return a.bound > b.bound; // smaller cost = higher priority
    }
};

double bound(Node u, int n, int W, vector<Item> &arr) {
    if (u.weight >= W) return 0;

    double profit_bound = u.profit;
    int j = u.level + 1;
    int totweight = u.weight;

    // include items while possible
    while (j < n && totweight + arr[j].weight <= W) {
        totweight += arr[j].weight;
        profit_bound += arr[j].value;
        j++;
    }

    // add fractional part (for bound only)
    if (j < n)
        profit_bound += (W - totweight) * arr[j].ratio;

    return profit_bound;
}

int knapsackLeastCost(int W, vector<Item> &arr, int n) {
    // Sort items by decreasing value/weight ratio
    sort(arr.begin(), arr.end(), [](Item a, Item b) {
        return a.ratio > b.ratio;
    });

    priority_queue<Node, vector<Node>, CompareCost> pq;
    Node u, v;

    u.level = -1;
    u.profit = 0;
    u.weight = 0;
    u.bound = -bound(u, n, W, arr); // negative for least-cost
    pq.push(u);

    int maxProfit = 0;

    while (!pq.empty()) {
        u = pq.top();
        pq.pop();

        double realBound = -u.bound;

        if (realBound <= maxProfit) continue; // prune

        v.level = u.level + 1;

        // Include current item
        v.weight = u.weight + arr[v.level].weight;
        v.profit = u.profit + arr[v.level].value;

        if (v.weight <= W && v.profit > maxProfit)
            maxProfit = v.profit;

        v.bound = -bound(v, n, W, arr);
        if (-v.bound > maxProfit)
            pq.push(v);

        // Exclude current item
        v.weight = u.weight;
        v.profit = u.profit;
        v.bound = -bound(v, n, W, arr);
        if (-v.bound > maxProfit)
            pq.push(v);
    }

    return maxProfit;
}

int main() {
    int n, W;
    cout << "Enter number of items: ";
    cin >> n;

    vector<Item> arr(n);
    cout << "Enter value and weight of each item:\n";
    for (int i = 0; i < n; i++) {
        cout << "Item " << i + 1 << " (value weight): ";
        cin >> arr[i].value >> arr[i].weight;
        arr[i].ratio = (double)arr[i].value / arr[i].weight;
    }

    cout << "Enter Knapsack capacity: ";
    cin >> W;

    int maxProfit = knapsackLeastCost(W, arr, n);
    cout << "\nMaximum Profit = " << maxProfit << endl;

    return 0;
}

// Enter number of items: 4
// Enter value and weight of each item:
// Item 1 (value weight): 1 2
// Item 2 (value weight): 2 3
// Item 3 (value weight): 5 4
// Item 4 (value weight): 6 5
// Enter Knapsack capacity: 8

// Maximum Profit = 8