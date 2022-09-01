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
#include <unistd.h>
#include <Sort\Sort.h>


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
void test_runs();
void gen_header();
bool user_process(int option);
void run_benchmark(int start, int end);
bool print_benchmark(int start, int end);
void randFill (std::vector<int>& vector);
double measure(std::vector<int>& vector, const Function& function);

// Inline function declarations
inline void bubbleSort(std::vector<int>& vector) { Sort::bubble_sort(vector); }
inline void selectionSort(std::vector<int>& vector) { Sort::insertion_sort(vector); }
inline void insertionSort(std::vector<int>& vector) { Sort::selection_sort(vector); }
inline void mergeSort(std::vector<int>& vector) { Sort::merge_sort(vector, 0, vector.size() -1);}
inline void quickSort(std::vector<int>& vector) { Sort::quick_sort(vector, 0, vector.size() -1);}
inline void std_sort (std::vector<int>& vector) {std::sort(vector.begin(),vector.end());}

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
    {"Bubble:    ", &bubbleSort},
    {"Selection: ", &selectionSort},
    {"Insertion: ", &insertionSort},
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
            test_runs();

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
void test_runs() {
    // Header
    cout << "Test Run:" << setw(18) << "Unsorted:";
    cout << setw(23) << "Sorted\n" << line << flush;

    // Execute sort algorithms with size 10 vector
    std::vector<int> vector(10);
    randFill(vector);

    for(auto run : ALGORITHMS) {
        // Same vector to sort for fairness
        std::vector<int> process(vector);
        // Unsorted
        cout << run.name << process << " => ";
        // Execute sorts
        run.algorithm(process);
        // Sorted
        cout << process << '\n';
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
    for(auto function : ALGORITHMS) {
        cout << BAR << CW2 << function.name;
        DIV += (DIV2);
    }
    
    cout << BAR << '\n' << DIV <<'\n';
}

/// ----------------------------------------------------------------------------
/// Runs benchmark of sorting algorithms while printing elapsed time.
/// ----------------------------------------------------------------------------
void run_benchmark(int start, int end) {

    for(auto size = start; size <= end; size *= 2) {
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
bool print_benchmark(int start, int end) {
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
    for(auto size = start; size <= end; size *= 2) {
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
