/// @file: genSDL.cpp
/// @author: Sao Thao
/// @date: 2022-10-5
/// @brief: This program utilizes the author defined genSDL.h
/// file to implement the SDL API for displaying a graphical
/// representation of common sorting algorithms.
/// @note: All functions can be invoked statically.
/// @note: genSDL.h located: /src/include/genSDL.h


#include <iostream>
#include <random>
#include <unistd.h>
#include <SDL2\genSDL.h>

using namespace std;

/// ----------------------------------------------------------------------------
///                      Prototype Function(s)
/// ----------------------------------------------------------------------------
void randomFill(std::vector<int>& vec);
void printVec(std::vector<int>& vec);
void gen(std::vector<int> vec, int choice);

// Inline function declarations
inline static void bubbleSDL(std::vector<int>& vector) {SDL_bubble_sort(vector);}
inline static void insertSDL(std::vector<int>& vector) {SDL_insertion_sort(vector);}
inline static void selectSDL(std::vector<int>& vector) {SDL_selection_sort(vector);}
inline static void qsortSDL(std::vector<int>& vector) {SDL_quick_sort(vector);}
inline static void msortSDL(std::vector<int>& vector) {SDL_merge_sort(vector);}

/// ----------------------------------------------------------------------------
///                      Global Constants
/// ----------------------------------------------------------------------------
const std::string line = "-"+(string(60,'-')+='\n');    //< Header

/// ----------------------------------------------------------------------------
///                      Main Function
/// ----------------------------------------------------------------------------
int main (int argc, char* argv[]) {
    //
    const char* options[6] = {"Bubble Sort", 
                            "Insertion Sort", 
                            "Selection Sort",
                            "Merge Sort",
                            "Quick Sort",
                            "To end the program"};
    // Entry prompt
    cout << "This program generates a graphical representation of the following:\n";

    for(int l = 0; l < 6; l++) {
        cout << l + 1 << " => " << options[l] << '\n';
    }

    sleep(1);

    while(cin.good()) {
        // User prompt
        cout << line + "Please select from the options above: ";
        // User input
        int choice = 0;
        cin >> choice;

        if(choice == 5) {
            cout << line + "\nProgram ended." + line;
            break;
        }
        else if(choice > 0 && choice < 5) {
            std::vector<int> vector;        // Container to sort
            randomFill(vector);             // Randomly fill vector
            sleep(2);

            // Print to ensure random
            cout << '\n' + line+"Vector generated and randomly filled\n\n";
            printVec(vector);

            // Generate SDL window               
            cout << line + line + options[choice] +
            " visual generating...\n" + "Note: Ctrl-C to end\n" +
            "The program will end when visual is completed.\n" + line;
            sleep(4);
            gen(vector, choice);
            break;

        }
        else {
            cout << line + "Error, try again\n" + line;
            sleep(2);
        }
    }

    return EXIT_SUCCESS;
}

/// ----------------------------------------------------------------------------
/// Randomly fill the the vector.
/// @param [in] vec the container to print.
/// ----------------------------------------------------------------------------
void gen(std::vector<int> vec, int choice) {
    // Generate SDL on user request
    switch(choice) {
        case 1:
            bubbleSDL(vec);
            break;
        case 2:
            insertSDL(vec);
            break;
        case 3:
            selectSDL(vec);
            break;
        case 4:
            msortSDL(vec);
            break;
        case 5:
            qsortSDL(vec);
            break;
        default:
            cout << "Error with SDL genrating.\n";
            break;
    }
}

/// ----------------------------------------------------------------------------
/// Randomly fill the the vector.
/// @param [in] vec the container to print.
/// ----------------------------------------------------------------------------
void randomFill(std::vector<int>& vec) {
    // Random generator
    std::random_device random;
    // Random numbers (1 == 1 pixel tall, 99 == 99 pixels tall)
    std::uniform_int_distribution<> number(1,99);

    // Randomly fill
    for(int i = 0; i <= 100; i++) {
        vec.push_back(number(random));
    }
}

/// ----------------------------------------------------------------------------
/// Prints the content of the vector.
/// @param [in] vec the container to print.
/// ----------------------------------------------------------------------------
void printVec(std::vector<int>& vec) {
    // Space between each elements, the comma an space.
    char separator[] {'\0','\0'};
    // Prints the opening bracket.
    cout << '[';
    // Print the vector's contents
    for(auto& element : vec) {
        cout << separator << element;
        *separator = ',';
    }
    cout << "]\n";
}


// #endif