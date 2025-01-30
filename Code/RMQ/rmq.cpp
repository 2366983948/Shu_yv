#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 100050, MAXF = 18;
int ar[MAXN];
int dp[MAXN][MAXF];
int LOG[MAXN];

// Function to compute the maximum value in a range using the given segment tree
int queryMax(int L, int R) {
    int d = LOG[R - L + 1];
    return max(dp[L][d], dp[R - (1 << d) + 1][d]);
}

int main() {
    int n, q, L, R;
    // Input prompt: Enter the number of elements and queries
    cout << "Enter the number of elements (n): ";
    cin >> n;
    cout << "Enter the number of queries (q): ";
    cin >> q;

    LOG[1] = 0;
    for (int i = 2; i <= n; i++)
        LOG[i] = LOG[i / 2] + 1;

    // Input prompt: Enter the array elements
    cout << "Enter the array elements:\n";
    for (int i = 1; i <= n; i++) {
        cin >> ar[i];
        dp[i][0] = ar[i];
    }

    for (int j = 1; (1 << j) <= n; j++)
        for (int i = 1; i + (1 << (j - 1)) <= n; i++)
            dp[i][j] = max(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);

    // Input prompt: Enter query ranges
    cout << "Enter the query ranges (L R separated by space):\n";
    while (q--) {
        cin >> L >> R;
        cout << "Maximum value in range [" << L << ", " << R << "]: " << queryMax(L, R) << endl;
    }

    return 0;
}