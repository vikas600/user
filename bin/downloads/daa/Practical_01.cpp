#include <iostream>
using namespace std;

// Recursive function
int fibRecursive(int n) {
    if (n <= 1) return n;
    return fibRecursive(n - 1) + fibRecursive(n - 2);
}

// Iterative function
void fibIterative(int n) {
    int a = 0, b = 1, c;
    cout << "Iterative Fibonacci: ";
    for (int i = 0; i < n; i++) {
        cout << a << " ";
        c = a + b;
        a = b;
        b = c;
    }
    cout << endl;
}

int main() {
    int n;
    cout << "Enter number of terms: ";
    cin >> n;

    // Recursive output
    cout << "Recursive Fibonacci: ";
    for (int i = 0; i < n; i++) {
        cout << fibRecursive(i) << " ";
    }
    cout << endl;

    // Iterative output
    fibIterative(n);

    return 0;
}
