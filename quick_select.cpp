#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <random>
using namespace std;

#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)

int quick_select_comparison_count = 0;
int lazy_select_comparison_count = 0;

int quick_select_benchmark();
int lazy_select_benchmark();

int quick_select(vector<int>& arr, int k);
int lazy_select(vector<int>& arr, int k);
int quick_sort(vector<int>& arr, int l, int r);
string get_kvalue_text(int k);



int main(){

    // vector<int> my_array = {1, 23, 434, 500, 723, 1230, 1584, 4323, 9321, 9876};
    // int k = 10;
    // cout << "Quick Select: " << quick_select(my_array, k) << endl;

    lazy_select_benchmark();
    return 0;
    

}

int quick_select_benchmark(){
    vector<int> sizes;
    for(int i = 1; i <= 10000; i += 100){
        sizes.push_back(i);
    }
    ofstream outfile("Quick_results.csv");
    outfile << "ArraySize,K,Comparisons\n";

    for(int size : sizes){
        vector<int> k_values;
        for(int i = 1; i <= 10; i++){
            k_values.push_back(size * i / 10); // k values as ratios of size
        }

        for(int k : k_values){
            vector<int> arr(size);
            for(int i = 0; i < size; i++){
                arr[i] = rand() % 10000; // Fill array with random values
            }
            quick_select_comparison_count = 0; // Reset comparison count
            quick_select(arr, k);
            outfile << size << "," << k << "," << quick_select_comparison_count << "\n";
            // print array
        }
    }
    outfile.close();
    return 0;
}

int lazy_select_benchmark(){
    vector<int> sizes;
    for(int i = 1; i <= 10000; i += 100){
        sizes.push_back(i);
    }
    ofstream outfile("Lazy_results.csv");
    outfile << "ArraySize,K,Comparisons\n";

    for(int size : sizes){
        vector<int> k_values = {1, size / 4, size / 2, 3 * size / 4, size-1}; // k values as ratios of size
        vector<string> k_labels = {"1", "1/4", "1/2", "3/4", "4/4"}; // Corresponding labels

        for(size_t i = 0; i < k_values.size(); i++){
            int k = k_values[i];
            string k_label = k_labels[i];
            vector<int> arr(size);
            for(int j = 0; j < size; j++){
                arr[j] = rand() % 10000; // Fill array with random values
            }
            lazy_select_comparison_count = 0; // Reset comparison count
            lazy_select(arr, k);
            outfile << size << "," << k_label << "," << lazy_select_comparison_count << "\n";
            // print array
        }
    }
    outfile.close();
    return 0;
    
}

int quick_select(vector<int>& arr, int k){
    int n = arr.size();
    int l = 0, r = n - 1;
    while(l <= r){
        int pivot = arr[r];
        int i = l;
        for(int j = l; j < r; j++){
            quick_select_comparison_count++; // Increment comparison count
            if(arr[j] < pivot){
                swap(arr[i], arr[j]);
                i++;
            }
        }
        swap(arr[i], arr[r]);
        if(i == k - 1){
            return arr[i];  // if pivot is the kth smallest element
        }
        else if(i < k - 1){
            l = i + 1;  // if pivot is less than kth smallest element
        }
        else{
            r = i - 1;  // if pivot is greater than kth smallest element
        }
    }
    return -1;
}



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



int quick_sort(vector<int>& arr, int l, int r){
    if(l < r){
        int pivot = arr[r];
        int i = l;
        for(int j = l; j < r; j++){
            lazy_select_comparison_count++; // Increment comparison count
            if(arr[j] < pivot){
                swap(arr[i], arr[j]);
                i++;
            }
        }
        swap(arr[i], arr[r]);
        quick_sort(arr, l, i - 1);
        quick_sort(arr, i + 1, r);
    }
    return 0;

}
