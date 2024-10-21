#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <random>
using namespace std;

#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)

int quick_select_comparison_count = 0;

int quick_select(vector<int>& arr, int k);
int lazy_select(vector<int>& arr, int k);
int quick_sort(vector<int>& arr, int l, int r);


int main(){
    //quick_select_benchmark();
    vector<int> arr = {3, 2, 1, 5, 4, 10, 24, 245, 1, 234};
    lazy_select(arr, 3);
    return 0;

}

int quick_select_benchmark(){
    vector<int> sizes;
    for(int i = 1; i <= 10000; i += 100){
        sizes.push_back(i);
    }
    vector<int> k_values = {1, 5, 10, 50, 500}; // Different k values

    ofstream outfile("results.csv");
    outfile << "ArraySize,K,Comparisons\n";

    for(int size : sizes){
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


int lazy_select(vector<int>& arr, int k){
    int n = arr.size();
    // 1. pick n^3/4 elements at random
    int sample_size = pow(n, 3.0/4.0);
    vector<int> randomSample;
    std::mt19937 generator(time(0)); // Random number generator
    std::uniform_int_distribution<int> distribution(0, n - 1); // Random number generator using uniform distribution

    for (int i = 0; i < sample_size; i++){
        int index = distribution(generator);
        randomSample.push_back(arr[index]);
    }
    /* cout << "Éléments aléatoires sélectionnés :" << endl;
    for (int elem : randomSample) {
        cout << elem << " ";
    }
    cout << endl; */
    
    // 2. sort the sample using quick sort
    quick_sort(randomSample, 0, sample_size - 1);

    // 3.
    
    double x = k*pow(n, -1.0/4.0);
    int l = max(1, floor(x - sqrt(n)));
    int h = min(sample_size, ceil(x + sqrt(n)));

    int a = randomSample[l];
    int b = randomSample[h];

    // compute the rank of a and b by comparing them to all the element of arr
    int rank_a = 0;
    int rank_b = 0;
    // complexity : O(n) for this and we try to achieve O(n) for the whole algorithm so it's ok
    for(int i = 0; i < n; i++){
        if(arr[i] < a){
            rank_a++;
        }
        if(arr[i] < b){
            rank_b++;
        }
    }

    // 4. Find in wich interval the kth smallest element is (< n^1/4, > n-n^1/4, in between)
    vector<int> new_sample;
    if (k < pow(n, 1.0/4.0)){
        for(int i; i <= b, i++){
            new_sample.push_back(i);
        }
    }
    else if (k > n - pow(n, 1.0/4.0)){
        for(int i; i >= a, i--){
            new_sample.push_back(i);
        }
    }
    else{
        for(int i = a; i <= b; i++){
            new_sample.push_back(i);
        }
    }

    //Check whether S(k) is in P and |P|  <= 4n^3/4 + 2. If not, repeat Steps 1-3 until such set P is found.
    
    


    return 0;
}


int quick_sort(vector<int>& arr, int l, int r){
    if(l < r){
        int pivot = arr[r];
        int i = l;
        for(int j = l; j < r; j++){
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