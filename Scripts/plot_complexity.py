import matplotlib.pyplot as plt
import pandas as pd
import numpy as np


def main():
    # Get the file path from command line argument
    lazy_results_file_path = "Lazy_results.csv"
    quick_select_results_file_path = "Quick_results.csv"
    plot_lazy_data(lazy_results_file_path)
    plot_quick_select_data(quick_select_results_file_path)


# Define the function
def quick_select_theoretical_complexity(n, k):
    # this function retrun the teritical complexity of quickSelect algorithm
    
    for i in range(len(k)):
        k.iloc[i] = min(k.iloc[i], n.size-1) # to avoid the case of k = n.size which will cause a division by zero
    
        
    return 2 * n + 2 * k * np.log((n-k) / k) + 2 * n * np.log(n / (n - k))

def lazy_complexity(n, k):
    return 2*n


def plot_quick_select_data(file_path):
    # Read the results from the CSV file
    df = pd.read_csv(file_path)

    # Plot the results
    plt.figure(figsize=(12, 6))

    k_values = ["1", "1/4", "1/2", "3/4", "4/4"]
    for k in k_values:
        print(eval(k))
    for k in k_values:
        subset = df[df['K'] == k]
        plt.figure(figsize=(12, 6))  # Create a new figure for each k value
        plt.plot(subset['ArraySize'], subset['Comparisons'], label=f'k={k}')

        # Compute theoretical complexity
        n_values = subset['ArraySize']
        k_values = n_values * eval(k)
        theoretical_values = quick_select_theoretical_complexity(n_values, k_values)
        plt.plot(n_values, theoretical_values, label=f'k={k} (theoretical)', linestyle='--')

        plt.xlabel('Array Size')
        plt.ylabel('Number of Comparisons')
        plt.title(f'Quick Select Comparison Count vs Array Size (k={k})')
        plt.legend()
        plt.grid(True)
        plt.axis('equal')  # Set the axes to have the same scale
    plt.show()


def plot_lazy_data(file_path):
    # Read the results from the CSV file
    df = pd.read_csv(file_path)

    # Plot the results
    plt.figure(figsize=(12, 6))

    k_values = ["1", "1/4", "1/2", "3/4", "4/4"]
    for k in k_values:
        subset = df[df['K'] == k]
        plt.figure(figsize=(12, 6))  # Create a new figure for each k value
        plt.plot(subset['ArraySize'], subset['Comparisons'], label=f'k={k}')

        # Compute theoretical complexity
        n_values = subset['ArraySize']
        k_values = n_values * eval(k)
        theoretical_values = lazy_complexity(n_values, k_values)
        plt.plot(n_values, theoretical_values, label=f'k={k} (theoretical)', linestyle='--')

        plt.xlabel('Array Size')
        plt.ylabel('Number of Comparisons')
        plt.title(f'Lazy Select Comparison Count vs Array Size (k={k})')
        plt.legend()
        plt.grid(True)
        plt.axis('equal')  # Set the axes to have the same scale
    plt.show()



if __name__ == "__main__":
    main()