#include "lazy_select.h"
#include "sorting.h"
#include <random>
#include <cmath>

#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)

using namespace std;

int lazy_select_comparison_count = 0;

// Lazy Select Function
int lazy_select(vector<int>& arr, int k) {
    int n = arr.size();
    if (k > n || k < 1) {
        return -1; // k is out of valid index range
    }

    int sample_size = pow(n, 3.0 / 4.0); // Size of the random sample

    while (true) {
        // 1. Select a random sample
        vector<int> randomSample;
        random_device rd;
        mt19937 generator(rd());
        uniform_int_distribution<int> distribution(0, n - 1);

        for (int i = 0; i < sample_size; i++) {
            int index = distribution(generator);
            randomSample.push_back(arr[index]);
        }

        // 2. Sort the sample
        quick_sort(randomSample, 0, sample_size - 1);

        // 3. Determine a and b, the bounds of the interval containing the k-th element
        double x = k*pow(n, -1.0/4.0);
        int l = max(1, floor(x - sqrt(n)));
        int h = min(sample_size, ceil(x + sqrt(n)));

        int a = randomSample[l - 1]; // Lower bound
        int b = randomSample[h - 1]; // Upper bound

        // Compute the rank of a and b in the original array
        int rank_a = 1, rank_b = 1;
        for (int i = 0; i < n; i++) {
            if (arr[i] < a) rank_a++; // we use < because we want rank_a to be smallest element in the case where we have multiple
            if (arr[i] <= b) rank_b++; // we use <= because we want rank_b to be the highest element in the case where we have multiple 
        }

        // 4. Select the relevant elements for P
        vector<int> P;
        int type;
        if (k < pow(n, 1.0 / 4.0)) {
            for (int y : arr) {
                if (y <= b) P.push_back(y);
                type = 1;
            }
        } else if (k > n - pow(n, 1.0 / 4.0)) {
            for (int y : arr) {
                if (y >= a) P.push_back(y);
                type = 2;
            }
        } else {
            // Otherwise, k is in between
            for (int y : arr) {
                if (y >= a && y <= b) P.push_back(y);
                type = 3;
            }
        }

        // 5. Check the size of P and if S(k) is in P
        if (P.size() <= 4 * pow(n, 3.0 / 4.0) + 2) {
            // print all type of information
            // cout << "n: " << n << endl;
            // cout << "k: " << k << endl;
            // cout << "a: " << a << endl;
            // cout << "b: " << b << endl;
            // cout << "rank_a: " << rank_a << endl;
            // cout << "rank_b: " << rank_b << endl;
            // cout << "P: ";
            // for (int i : P) {
            //     cout << i << " ";
            // }
            // cout << endl;
            // cout << "Type: " << type << endl;

            quick_sort(P, 0, P.size() - 1);
            int index = k - rank_a; // Adjusted index to find the k-th element
            index = max(0, index); // Ensure index is not negative
            switch (type) {
                case 1:
                    if (k >= rank_a) return P[index];
                    break;
                case 2:
                    if (k <= rank_b) return P[index];
                    break;
                case 3:
                    if (k >= rank_a && k <= rank_b) return P[index];
                    break;
                default:
                    break;
            }
        }
    }
    return -1; // For safety (this should not happen)
}

