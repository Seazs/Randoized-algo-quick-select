#include "sorting.h"
#include <vector>
#include <algorithm>

extern int lazy_select_comparison_count;

using namespace std;



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
