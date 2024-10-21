#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

int quick_select_comparison_count = 0;

int quick_select(vector<int>& arr, int k);

int main(){
    //rand(time(0)); // Seed for random number generation
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
            return arr[i];
        }
        else if(i < k - 1){
            l = i + 1;
        }
        else{
            r = i - 1;
        }
    }
    return -1;
}

