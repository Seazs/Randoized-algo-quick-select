import matplotlib.pyplot as plt
import pandas as pd
import sys
import pandas as pd
import numpy as np


# Define the function
def theoretical_complexity(n, k):
    # this function retrun the teritical complexity of quickSelect algorithm
    return 2 * n + 2 * k * np.log((n-k) / k) + 2 * n * np.log(n / (n - k))


# Get the file path from command line argument
file_path = sys.argv[1]

# Read the results from the CSV file
df = pd.read_csv(file_path)

# Plot the results
plt.figure(figsize=(12, 6))

for k in df['K'].unique():
    subset = df[df['K'] == k]
    plt.figure(figsize=(12, 6))  # Create a new figure for each k value
    plt.plot(subset['ArraySize'], subset['Comparisons'], label=f'k={k}')

    # Compute theoretical complexity
    n_values = subset['ArraySize']
    theoretical_values = theoretical_complexity(n_values, k)
    plt.plot(n_values, theoretical_values, label=f'k={k} (theoretical)', linestyle='--')

    plt.xlabel('Array Size')
    plt.ylabel('Number of Comparisons')
    plt.title(f'Quick Select Comparison Count vs Array Size (k={k})')
    plt.legend()
    plt.grid(True)
    plt.axis('equal')  # Set the axes to have the same scale
    plt.show()

