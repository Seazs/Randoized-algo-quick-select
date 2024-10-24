#include "quick_select.h"
#include <vector>
#include <algorithm> // for swap

int quick_select_comparison_count = 0;

int quick_select(std::vector<int>& arr, int k){
    int n = arr.size();
    int l = 0, r = n - 1;
    while(l <= r){
        int pivot = arr[r];
        int i = l;
        for(int j = l; j < r; j++){
            quick_select_comparison_count++; // Increment comparison count
            if(arr[j] < pivot){
                std::swap(arr[i], arr[j]);
                i++;
            }
        }
        std::swap(arr[i], arr[r]);
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
