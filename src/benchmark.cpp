#include "benchmark.h"
#include "quick_select.h"
#include "lazy_select.h"
#include <vector>
#include <fstream>
#include <chrono>
#include <iostream>

using namespace std;

int quick_select_benchmark(){
    std::vector<int> sizes;
    for(int i = 5000; i <= 500000; i += 5000){
        sizes.push_back(i);
    }
    std::ofstream outfile("Quick_results.csv");
    outfile << "ArraySize,K,Comparisons,Time\n";

    for(int size : sizes){
        std::cout << "Size: " << size << std::endl;
        std::vector<int> k_values = {1, size / 4, size / 2, 3 * size / 4, size-1}; 
        std::vector<std::string> k_labels = {"1", "1/4", "1/2", "3/4", "4/4"}; 

        for(size_t i = 0; i < k_values.size(); i++){
            int k = k_values[i];
            std::string k_label = k_labels[i];
            double total_comparisons = 0;
            double total_time = 0;

            for (int run = 0; run < 5; run++) { // Run 5 times for each size
                std::vector<int> arr(size);
                for(int j = 0; j < size; j++){
                    arr[j] = rand() % 10000;
                }
                quick_select_comparison_count = 0;

                auto start = std::chrono::high_resolution_clock::now();
                quick_select(arr, k);
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;

                total_comparisons += quick_select_comparison_count;
                total_time += elapsed.count();
            }

            double mean_comparisons = total_comparisons / 5;
            double mean_time = total_time / 5;

            outfile << size << "," << k_label << "," << mean_comparisons << "," << mean_time << "\n";
        }
    }
    outfile.close();
    return 0;
}

int lazy_select_benchmark(){
    vector<int> sizes;
    for(int i = 5000; i <= 500000; i += 5000){
        sizes.push_back(i);
    }
    ofstream outfile("Lazy_results.csv");
    outfile << "ArraySize,K,Comparisons,Time\n";

    for(int size : sizes){
        cout << "Size: " << size << endl;
        vector<int> k_values = {1, size / 4, size / 2, 3 * size / 4, size-1}; // k values as ratios of size
        vector<string> k_labels = {"1", "1/4", "1/2", "3/4", "4/4"}; // Corresponding labels

        for(size_t i = 0; i < k_values.size(); i++){
            int k = k_values[i];
            string k_label = k_labels[i];
            double total_comparisons = 0;
            double total_time = 0;

            for (int run = 0; run < 5; run++) { // Run 5 times for each size
                vector<int> arr(size);
                for(int j = 0; j < size; j++){
                    arr[j] = rand() % 10000; // Fill array with random values
                }
                lazy_select_comparison_count = 0; // Reset comparison count

                auto start = chrono::high_resolution_clock::now();
                lazy_select(arr, k);
                auto end = chrono::high_resolution_clock::now();
                chrono::duration<double> elapsed = end - start;

                total_comparisons += lazy_select_comparison_count;
                total_time += elapsed.count();
            }

            double mean_comparisons = total_comparisons / 5;
            double mean_time = total_time / 5;

            outfile << size << "," << k_label << "," << mean_comparisons << "," << mean_time << "\n";
        }
    }
    outfile.close();
    return 0;
}
