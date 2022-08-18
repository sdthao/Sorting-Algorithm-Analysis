/// @file: sort.cpp
/// @author: Sao Thao
/// @date: 2022-10-02
/// @brief: This program implements common sorting algorithms and
/// uses the std::chrono function to time the duration it takes to
/// iterate through each vector of size defined by the user.
/// @note: Option to print results for graphical representation
/// plotting with API's such as gnuplot.
/// @note: http://www.gnuplot.info/

#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include <numeric>
#include <fstream>
#include <cassert>
#include <cctype>
#include <unistd.h>

using namespace std;

/// ----------------------------------------------------------------------------
///                      Type Definitions
/// ----------------------------------------------------------------------------

// Alias for wrapper around function (vector<int>) returning void
using Function = void (*) (std::vector<int>&);

// Stores address of algorithm name and function to implement
struct sor_algorithms {
    std::string name;
    Function algorithm;
} ;

/// ----------------------------------------------------------------------------
///                      Prototype Function(s)
/// ----------------------------------------------------------------------------
void test_run();
void gen_header();
bool user_process(int option);
void run_benchmark(int begin, int end);
bool print_benchmark(int begin, int end);
void randFill (std::vector<int>& vector);
void bubble_sort (std::vector<int>& vector);
void selection_sort (std::vector<int>& vector);
void insertion_sort (std::vector<int>& vector);
int partition(std::vector<int>& vector, int first, int last);
void quick_sort (std::vector<int>& vector, int first, int last);
void merge(std::vector<int>& vector, int first, int split,int last);
void merge_sort (std::vector<int>& vector, int first, int last);
double measure(std::vector<int>& vector, const Function& function);

// Inline function declarations
inline void mergeSort(std::vector<int>& vector)
{merge_sort(vector, 0, vector.size() -1);}
inline void quickSort(std::vector<int>& vector)
{quick_sort(vector, 0, vector.size() -1);}
inline void std_sort (std::vector<int>& vector)
{std::sort(vector.begin(),vector.end());}

// Overload operator function
std::ostream& operator<< (std::ostream& output, const std::vector<int>& vec);

/// ----------------------------------------------------------------------------
///                      Global Constants
/// ----------------------------------------------------------------------------
static const string BAR = " |";                         //< Column separator   
static const auto CW = setw(8);                         //< Column width
static const auto CW2 = setw(13);                       //< Column width
const std::string line = "-"+(string(56,'-')+='\n');    //< Header

// Set of sorting algorithms to be benchmarked
static const std::vector<sor_algorithms> ALGORITHMS = {
    {"Bubble:    ", &bubble_sort},
    {"Selection: ", &selection_sort},
    {"Insertion: ", &insertion_sort},
    {"MergeSort: ", &mergeSort},
    {"QuickSort: ", &quickSort},
    {"std::sort: ", &std_sort},
};


/// ----------------------------------------------------------------------------
///                      Main Function
/// ----------------------------------------------------------------------------
int main() {
    // Array of user options
    const char* options[4] = {"Test Run", 
                              "Run Benchmark", 
                              "Run Benchmark and Print Data",
                              "End The Program"};
    // Entry Prompt
    cout << "This program tests the following sorting algorithms:\n" + line;
    // List algorithms used.
    for (auto titles : ALGORITHMS) {
        cout << titles.name.substr(0,titles.name.find_last_of(':')) << '\n'; 
    }

    sleep(1);

    while(cin.good()) {
        // Header
        cout << line + "Please select from the following options\n" + line;

        // List options
        for (int i = 0; i < 4; i++) {
            cout << i + 1 << " => " << options[i] << '\n';
        }

        // Prompt user
        cout << "\n\nUser Select: ";
        
        // User option
        int user = 0; 
        cin >> user;

        if(user == 4) {
            cout << "\nProgram ended.\n";
            break;
        }
        else if(user > 0 && user < 4) {
            assert(user > 0 && user < 4);
            // Status for user to test again
            bool status = user_process(user);
            
            // End program
            if(status == false) {
                assert(status == false);
                cout << "\nProgram ended.\n";
                break;
            }
        }
        else {
            cout << "Error, please try again.\n\n";
            sleep(2);
        }
    }
    
    return EXIT_SUCCESS;
}

/// ----------------------------------------------------------------------------
/// Processes user request.
/// @param [in] option Option provided by user.
/// ----------------------------------------------------------------------------
bool user_process(int option){
    // Prompt
    cout << line +"User Selected: " << option << '\n' << flush;
    int from = 0;       // Starting range
    int to = 0;         // End range
    
    sleep(2);

    switch(option) {
        // Option 1: Test Run
        case 1:
            // Execute test run
            cout << "Simulation of size 10 unsorted vector executed.\n" + line;
            test_run();

            break;
        // Option 2: Run benchmark test
        case 2:
            // Prompt user
            cout << line;
            cout << "Insert a range of vector size to randomly fill:\n";
            cout << "\t0 > x > 2,147,488,647\n";
            cout << "Note: Vector size will double until end range is met\n";
            cout << "Ex:From: 10000  To: 20000\n" + line;
            // Take input
            cout << "\nFrom: ";
            cin >> from;
            cout << "To: ";
            cin >> to;

            assert(from >= 0 && to <= 2147488647);
            cout << '\n';
            // Run benchmark
            gen_header();
            run_benchmark(from, to);

            break;
        // Option 3: Run and print benchmark test
        case 3:
            // Prompt user
            cout << line;
            cout << "Insert a range of vector size to randomly fill:\n";
            cout << "\t0 > x > 2,147,488,647\n";
            cout << "Note: Vector size will double until end range is met\n";
            cout << "Ex:From: 10000  To: 20000\n" + line;
            // Take user input
            cout << "\nFrom: ";
            cin >> from;
            cout << "To: ";
            cin >> to;

            assert(from >= 0 && to <= 2147488647);
            cout << '\n';
            // Run benchmark and check if file generated with no errors
            if(print_benchmark(from, to)) {
                cout << "File generated successfully.\n";
            }
            else {
                cout << "Failed to generate file.\n";
            }
            
            break;

        default:
            cout << "Invalid Input\n";
            break;
    }

    // Re-prompt user
    cout << '\n' + line + "Do you want to select again?\n";
    cout << "Y for Yes | N for no\n" + line + "User Select: ";

    char decision;          // User decision
    cin >> decision;
    
    return std::toupper(decision) == 'Y' ? true : false;
}

/// ----------------------------------------------------------------------------
/// Sorts a vector using the bubble sort algorithm.
/// @param [in] vector The vector to sort.
/// ----------------------------------------------------------------------------
void bubble_sort (std::vector<int>& vector) {
    // Temp memory for smaller vector element.
    int temp;

    // Iterate through the vector.
    for (auto iterator = vector.begin(); iterator < vector.end(); iterator++) {
        for (auto index = vector.begin(); index < vector.end() - 1; index++) {
            // If the current index is greater than the adjacent index.
            if (*index > *(index + 1)) {
                // Temporarily store the larger value.
                temp = *index;
                // Swap values
                *index = *(index + 1);
                // Assign larger value to the right
                *(index + 1) = temp;
            }
        }
    }
}

/// ----------------------------------------------------------------------------
/// Sorts a vector using the selection sort algorithm.
/// @param [in] vector The vector to sort.
/// ----------------------------------------------------------------------------
void selection_sort (vector<int>& vector) {
    // Temp memory to hold smaller value.
    int temp;

    // Iterate through the vector.
    for (auto iterator = vector.begin(); iterator < vector.end() - 1; iterator++) {
        // Selected value to compare.
        std::vector<int>::iterator selected = iterator;

        for (auto index = iterator + 1; index < vector.end(); index++) {
            // If the current value is smaller than the selected value.
            if (*index < *selected) {
                // Reassign the selected index with the smaller value.
                selected = index;
            }
        }
        // Temp store smaller value.
        temp = *selected;
        // Move the smaller value to the left.
        *selected = *iterator;
        // Move the larger value to the right. 
        *iterator = temp;
    }
}

/// ----------------------------------------------------------------------------
/// Sorts a vector using the insertion sort algorithm.
/// @param [in] vector The vector to sort.
/// ----------------------------------------------------------------------------
void insertion_sort (vector<int>& vector) {
    // Temp memory to hold smaller value.
    int temp;

    // Iterate through the vector.
    for (auto iteration = vector.begin() + 1; iteration < vector.end(); iteration++) {
        // If the current value is smaller than the value to the left.
        if (*iteration < *(iteration - 1)) {
            // Store the current smaller value.
            temp = *iteration;
            // Store the index of the smaller value.
            std::vector<int>::iterator index = iteration;

            // While at the location of the smaller value
            // iterate the vector backwards sorting.
            while (index > vector.begin() && *(index - 1) > temp) {
                // Move the larger number to the right.
                *index = *(index - 1);
                // Iterate down the vector.
                index--;
            }
            // Move smaller value to the left.
            *index = temp;  
        }
    }
}

/// ----------------------------------------------------------------------------
/// Sorts a vector using the merge sort algorithm.
/// @param [in] first The beginning of the range of elements to sort.
/// @param [in] last The end of the range of elements to sort.
/// ----------------------------------------------------------------------------
void merge_sort(vector<int>& vec, int first, int last) {
    if(first < last) {
        int split = (first + (last - first)/2);     // Index to split list

        // Split left side
        merge_sort(vec, first, split);
        // Split right side
        merge_sort(vec, split + 1, last);

        // Merge lists
        merge(vec, first, split, last);
    }
}

/// ----------------------------------------------------------------------------
/// Performs merging of merge sort.
/// @param [in] first The beginning of the range of elements to sort.
/// @param [in] split The middle index of the vector.
/// @param [in] last The end of the range of elements to sort.
/// ----------------------------------------------------------------------------
void merge(vector<int>& vec, int first, int split,int last) {
    int n1 = split - first + 1;     // Index of left side
    int n2 = last - split;          // Index of right side
    int Left[n1];                   // Left split list
    int Right[n2];                  // Right split list

    // Fill left list
    for(int i = 0; i < n1; i++) {
        Left[i] = vec[first + i];
    }
    // Fill right list
    for(int j = 0; j < n2; j++) {
        Right[j] = vec[split + 1 + j]; 
    }

    int leftIndex = 0;          // Left list index
    int rightIndex = 0;         // Right list index
    int vecIndex = first;       // Vector index

    while(leftIndex < n1 && rightIndex < n2) {
        // Sort vector with smaller value from left container.
        if(Left[leftIndex] <= Right[rightIndex]) {
            vec[vecIndex] = Left[leftIndex];
            leftIndex++;
        }
        // Sort vector with smaller value from right container.
        else {
            vec[vecIndex] = Right[rightIndex];
            rightIndex++;
        }
        vecIndex++;
    }

    // Insert remaining elements from left container.
    while (leftIndex < n1) {
        vec[vecIndex] = Left[leftIndex];
        leftIndex++;
        vecIndex++;
    }
    // Insert remaining elements from right container.
    while (rightIndex < n2) {
        vec[vecIndex] = Right[rightIndex];
        rightIndex++;
        vecIndex++;
    }
}

/// ----------------------------------------------------------------------------
/// Performs partitioning of quick sort.
/// @param [in] first The beginning of the range of elements to sort.
/// @param [in] last The end of the range of elements to sort.
/// @note First index is always chosen as pivot.
/// @returns the index to the partitioned value.
/// ----------------------------------------------------------------------------
int partition(vector<int>& vec, int first, int last) {
    int pivot = vec[first];     // First index as pivot
    int count = 0;              // Index counter

    // Find index of smallest and update pivot
    for (int i = first + 1; i <= last; i++) {
        if (vec[i] <= pivot) {
            count++;
        }
    }
 
    int partIndex = first + count;     // Index to divide

    swap(vec[partIndex], vec[first]);  // Assign smallest index
 
    int leftIndex = first;       // Left index
    int rightIndex = last;       // Right index
 
    while (leftIndex < partIndex && rightIndex > partIndex) {
        // Find index to sort from left side of pivot
        while (vec[leftIndex] <= pivot) {
            leftIndex++;
        }
        // Find index to sort from right side of pivot
        while (vec[rightIndex] > pivot) {
            rightIndex--;
        }
        // Sort list
        if (leftIndex < partIndex && rightIndex > partIndex) {
            swap(vec[leftIndex++], vec[rightIndex--]);
        }
    }

    return partIndex;
}

/// ----------------------------------------------------------------------------
/// Sorts a vector using the quick sort algorithm.
/// @param [in] first The beginning of the range of elements to sort.
/// @param [in] last The end of the range of elements to sort.
/// ----------------------------------------------------------------------------
void quick_sort(vector<int>& vec, int first, int last) {
    // Base case.
    if (first >= last) {
        return;
    }

    // Partitioning of the vector.
    int pivot = partition(vec, first, last);
 
    // Divide and sort left side from index of sorted portion.
    quick_sort(vec, first, pivot - 1);
    // Divide and sort right side from index of sorted portion.
    quick_sort(vec, pivot + 1, last);
}

/// ----------------------------------------------------------------------------
/// Fills and shuffles the elements of the vector with non-repeated numbers.
/// @param [in] vector The vector to fill and shuffle.
/// ----------------------------------------------------------------------------
void randFill (vector<int>& vector) {
    // Fill the vector with incrementing values first starting at 0.
    std::iota(vector.begin(), vector.end(), 0);

    // Randomly shuffles the elements in the vector.
    std::random_shuffle(vector.begin(), vector.end());
}

/// ----------------------------------------------------------------------------
/// Provides the stream operator << for ouput use.
/// @param [in] output The output stream.
/// @param [in] vector The vector to print.
/// @returns output The data from the vector.
/// ----------------------------------------------------------------------------
std::ostream& operator<< (std::ostream& output, const std::vector<int>& vector){
    // Space between each elements, the comma an space.
    char separator[] {'\0','\0'};
    // Prints the opening bracket.
    output << '[';
    // Loop to print the contents in the container.
    for (auto& item : vector) {
        // For every element, print separator, the comma and space.
        output << separator << item;
        // This loop first prints the null byte, than after the first print
        // separator is now ','
        *separator = ',';
    }
    // Prints the last closing bracket.
    return output << ']';
}

/// ----------------------------------------------------------------------------
/// Measures the execution time of a function.
/// @param [in] vector The vector to sort and measure.
/// @param [in] function Pointer to the sorting function being benchmarked.
/// @returns elapsed The execution elapsed time in seconds.
/// ----------------------------------------------------------------------------
double measure(std::vector<int>& vector, const Function& function) {
    // Start time
    auto start = std::chrono::high_resolution_clock::now();
    // Run the sorting algorithm
    function(vector);
    // Stop time
    auto stop = std::chrono::high_resolution_clock::now();
    // Elapsed time
    std::chrono::duration<double> elapsed = stop - start;

    return elapsed.count();
}

/// ----------------------------------------------------------------------------
/// Test run of all sorting algorithm with a size 10 vector and no time.
/// ----------------------------------------------------------------------------
void test_run() {
    // Header
    cout << "Test Run:" << setw(18) << "Unsorted:";
    cout << setw(23) << "Sorted\n" << line << flush;

    // Execute sort algorithms with size 10 vector
    for(auto size = 10; size <= 10; size *= 2) {
        std::vector<int> vector(size);
        randFill(vector);
        for(auto run : ALGORITHMS) {
            // Same vector to sort for fairness
            std::vector<int> process(vector);
            cout << run.name << process << " => ";
            run.algorithm(process);
            cout << process << '\n';
        }
    }
}

/// ----------------------------------------------------------------------------
/// Generates the report header.
/// ----------------------------------------------------------------------------
void gen_header() {
    // Print Header
    std::string DIV = "+---------+";                 ///< Header divider
    std::string DIV2 = "--------------+";            ///< Header divider
    cout << std::setprecision(6) << std::showpoint << std::fixed;
    cout << '\n' << BAR[1] << CW << "Size: " << flush;
    
    // Print sorting algorithm names
    for(auto func : ALGORITHMS) {
        cout << BAR << CW2 << func.name;
        DIV += (DIV2);
    }
    
    cout << BAR << '\n' << DIV <<'\n';
}

/// ----------------------------------------------------------------------------
/// Runs benchmark of sorting algorithms while printing elapsed time.
/// ----------------------------------------------------------------------------
void run_benchmark(int begin, int end) {

    for(auto size = begin; size <= end; size *= 2) {
        std::vector<int> vector(size);
        randFill(vector);
        cout << BAR[1] << CW << size;
        for(auto run : ALGORITHMS) {
            // Same unsorted vector for fairness.
            std::vector<int> process(vector);
            cout << BAR << CW2 << measure(process, run.algorithm);
        }
        cout << BAR << '\n';
    }
}

/// ----------------------------------------------------------------------------
/// Prints benchmark data.
/// ----------------------------------------------------------------------------
bool print_benchmark(int begin, int end) {
    bool fileStatus = true;
    std::ofstream file("Sorting_Results.txt");

    file << std::left << std::setprecision(6) << std::showpoint << std::fixed;
    file << CW2 << "Size" << flush;

    // Print header of algorithm names
    for (auto header : ALGORITHMS) {
        file << CW2 << header.name ;
    }

    file << '\n';

    // Run benchmark test
    for(auto size = begin; size <= end; size *= 2) {
        std::vector<int> vector(size);
        randFill(vector);
        file << CW2 << size;
        for(auto run : ALGORITHMS) {
            // Same unsorted vector for fairness.
            std::vector<int> process(vector);
            file << CW2 << measure(process, run.algorithm);
        }
        file << '\n';
    }

    // Check if file had issues
    if(file.bad()) {
        fileStatus = false;
    }
    
    file.close();

    return fileStatus;
}
