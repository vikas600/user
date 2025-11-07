#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Class to represent an item
class Item {
public:
    int value;
    int weight;

    Item(int value, int weight) {
        this->value = value;
        this->weight = weight;
    }
};

// Comparator function to sort items by value/weight ratio
bool compare(Item a, Item b) {
    double r1 = (double)a.value / a.weight;
    double r2 = (double)b.value / b.weight;
    return r1 > r2; // higher ratio first (Greedy choice)
}

// Function to solve Fractional Knapsack problem
double fractionalKnapsack(int W, vector<Item>& items) {
    // Sort items based on value-to-weight ratio
    sort(items.begin(), items.end(), compare);

    int currentWeight = 0;
    double totalValue = 0.0;

    for (auto item : items) {
        // If full item can be added
        if (currentWeight + item.weight <= W) {
            currentWeight += item.weight;
            totalValue += item.value;
        }
        else {
            // Take fractional part of the item
            int remain = W - currentWeight;
            totalValue += item.value * ((double)remain / item.weight);
            break; // Knapsack is full
        }
    }

    return totalValue;
}

int main() {
    int n, W;
    cout << "Enter number of items: ";
    cin >> n;

    vector<Item> items;
    cout << "Enter value and weight of each item:\n";
    for (int i = 0; i < n; i++) {
        int value, weight;
        cin >> value >> weight;
        items.push_back(Item(value, weight));
    }

    cout << "Enter capacity of knapsack: ";
    cin >> W;

    double maxValue = fractionalKnapsack(W, items);

    cout << "\nMaximum value in Knapsack = " << maxValue << endl;
    return 0;
}

// Enter number of items: 3
// Enter value and weight of each item:
// 10 60
// 20 100
// 30 120
// Enter capacity of knapsack: 50

// Maximum value in Knapsack = 12.5