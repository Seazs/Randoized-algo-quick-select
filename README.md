# Randoized-algo-quick-select

## How to Build and Run the Project

### Prerequisites

- Ensure you have `g++` installed for compiling the C++ code.
- Ensure you have Python installed along with the `matplotlib`, `pandas` and `numpy` libraries for plotting.

### Building the Project

1. Open a terminal and navigate to the project directory.
2. Run the following command to build the project:

    ```sh
    make
    ```

3. This will compile the source files, create an executable named `benchmark` and **run** the benchmark.

### Running the Benchmark

1. Once it is built, run the following command to execute the benchmark:

    ```sh
    ./benchmark
    ```
2. This will run the benchmark for both Quick Select and Lazy Select algorithms and store the results in CSV files.

### Plotting the Results


2. Run the `plot_complexity.py` script from the root folder to generate plots:

    ```sh
    python ./Scripts/plot_complexity.py
    ```

3. This script will read the results from the CSV files and generate plots for time complexity and comparison count for both Quick Select and Lazy Select algorithms.

## Files and Directories

- `src/`: Contains the source code for the Quick Select and Lazy Select algorithms, as well as the benchmarking code.
- `build/`: Contains the compiled object files.
- `Scripts/`: Contains the Python script for plotting the results.
- `Makefile`: Contains the build instructions.
- `Lazy_results.csv` and `Quick_results.csv`: Contain the benchmark results for Lazy Select and Quick Select algorithms, respectively.

## Contact

For any questions or issues, please contact the project maintainer.