#include "benchmark.h"
#include "lazy_select.h"
#include <iostream>
#include <vector>

using namespace std;

int main(){
    // // array of size 10 with random values
    // vector<int> arr = {1, 243, 123, 4, 24, 6, 7, 853, 9, 10344};

    // // kth smallest element
    // int k = 1;
    // int res = lazy_select(arr, k);
    // cout << "The " << k << "th smallest element is: " << res << endl;


    quick_select_benchmark();
    lazy_select_benchmark();
    return 0;
}