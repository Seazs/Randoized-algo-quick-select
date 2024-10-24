import matplotlib.pyplot as plt
import pandas as pd
import numpy as np


def main():
    # Get the file path from command line argument
    lazy_results_file_path = "Lazy_results.csv"
    quick_select_results_file_path = "Quick_results.csv"
    
    plot_comparison_data(quick_select_results_file_path, lazy_results_file_path)
    plot_time_comparison(quick_select_results_file_path, lazy_results_file_path)
    


# Define the function
def quick_select_theoretical_complexity(n, k):
    # Handle both scalar and array-like n and k
    n = np.asarray(n)  # Convert to array if not already
    k = np.asarray(k)  # Convert to array if not already

    # Ensure k is in the valid range [1, n-1] to avoid division by zero
    k = np.minimum(k, n - 1)  # Limit k to n-1 to avoid log(0)

    # Theoretical complexity formula
    res = 2 * n + 2 * k * np.log((n - k) / k) + 2 * n * np.log(n / (n - k))
    return res

def lazy_time_complexity(n, k):
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
        theoretical_values = quick_select_theoretical_complexity(n_values, k_values)
        plt.plot(n_values, theoretical_values, label=f'k={k} (theoretical)', linestyle='--')

        plt.xlabel('Array Size')
        plt.ylabel('Number of Comparisons')
        plt.title(f'Lazy Select Comparison Count vs Array Size (k={k})')
        plt.legend()
        plt.grid(True)
        plt.axis('equal')  # Set the axes to have the same scale
        plt.show()


def plot_comparison_data(quick_select_file, lazy_file):
    # Read the results from the CSV files
    df_quick_select = pd.read_csv(quick_select_file)
    df_lazy = pd.read_csv(lazy_file)

    k_values = ["1", "1/4", "1/2", "3/4", "4/4"]
    for k in k_values:
        plt.figure(figsize=(12, 6))  # Create a new figure for each k value
        subset_quick_select = df_quick_select[df_quick_select['K'] == k]
        subset_lazy = df_lazy[df_lazy['K'] == k]

        plt.plot(subset_quick_select['ArraySize'], subset_quick_select['Comparisons'], label=f'Quick Select k={k}')
        plt.plot(subset_lazy['ArraySize'], subset_lazy['Comparisons'], label=f'Lazy Select k={k}')

        # Compute theoretical complexity
        n_values = subset_quick_select['ArraySize']
        k_values = n_values * eval(k)
        theoretical_values = quick_select_theoretical_complexity(n_values, k_values)
        plt.plot(n_values, theoretical_values, label=f'k={k} (theoretical)', linestyle='--', color='black')

        plt.xlabel('Array Size')
        plt.ylabel('Number of Comparisons')
        plt.title(f'Comparison Count Comparison: Quick Select vs Lazy Select (k={k})')
        plt.legend()
        plt.grid(True)
        # plt.axis('equal')  # Set the axes to have the same scale
    plt.show()


def plot_quick_select_time(file_path):
    # Read the results from the CSV file
    df = pd.read_csv(file_path)

    # Plot the results
    plt.figure(figsize=(12, 6))

    k_values = ["1", "1/4", "1/2", "3/4", "4/4"]
    for k in k_values:
        subset = df[df['K'] == k]
        print(subset['Time'])
        plt.figure(figsize=(12, 6))  # Create a new figure for each k value
        plt.plot(subset['ArraySize'], subset['Time']*1000, label=f'k={k}')

        plt.xlabel('Array Size')
        plt.ylabel('Time (ms)')
        plt.title(f'Quick Select Time Complexity vs Array Size (k={k})')
        plt.legend()
        plt.grid(True)

    plt.show()

def plot_lazy_time(file_path):
    # Read the results from the CSV file
    df = pd.read_csv(file_path)

    # Plot the results
    plt.figure(figsize=(12, 6))

    k_values = ["1", "1/4", "1/2", "3/4", "4/4"]
    for k in k_values:
        subset = df[df['K'] == k]
        # multiply the time by 1000 to convert it to ms
        subset.loc[:, 'Time'] *= 1000
        print(subset['Time'])
        
        plt.figure(figsize=(12, 6))  # Create a new figure for each k value
        plt.plot(subset['ArraySize'], subset['Time'], label=f'k={k}')

        plt.xlabel('Array Size')
        plt.ylabel('Time (ms)')
        plt.title(f'Lazy Select Time Complexity vs Array Size (k={k})')
        plt.legend()
        plt.grid(True)
        
    plt.show()

def plot_time_comparison(quick_select_file, lazy_file):
    # Read the results from the CSV files
    df_quick_select = pd.read_csv(quick_select_file)
    df_lazy = pd.read_csv(lazy_file)

    # Plot the results
    plt.figure(figsize=(12, 6))

    k_values = ["1", "1/4", "1/2", "3/4", "4/4"]
    for k in k_values:
        plt.figure(figsize=(12, 6))  # Create a new figure for each k value
        subset_quick_select = df_quick_select[df_quick_select['K'] == k]
        subset_lazy = df_lazy[df_lazy['K'] == k]

        # Multiply the time by 1000 to convert it to ms
        subset_quick_select.loc[:, 'Time'] *= 1000
        subset_lazy.loc[:, 'Time'] *= 1000

        plt.plot(subset_quick_select['ArraySize'], subset_quick_select['Time'], label=f'Quick Select k={k}')
        plt.plot(subset_lazy['ArraySize'], subset_lazy['Time'], label=f'Lazy Select k={k}')


        plt.xlabel('Array Size')
        plt.ylabel('Time (ms)')
        plt.title('Time Complexity Comparison: Quick Select vs Lazy Select')
        plt.legend()
        plt.grid(True)
    plt.show()



if __name__ == "__main__":
    main()