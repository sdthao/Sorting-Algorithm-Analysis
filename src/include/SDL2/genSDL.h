/// @file: genSDL.h
/// @author: Sao Thao 
/// @date: 2022-17-08
/// @note: This header file demonstrates a real-time linear computation of
/// common sorting algorithms using the SDL API.
/// @note: https://www.libsdl.org/

#ifndef genSDL_H_
#define genSDL_H_

#include <SDL2\SDL.h>
#include <iostream>
#include <vector>

using namespace std;

/// ----------------------------------------------------------------------------
///                             genSDL Class
/// ----------------------------------------------------------------------------
template <class T>
class genSDL {
public:
    // Render SDL window for bubble sort method
    static void SDL_bubble_sort (std::vector<T>& vector);
    //  Render SDL window for selection sort method
    static void SDL_selection_sort (std::vector<T>& vector);
    //  Render SDL window for insertion sort method
    static void SDL_insertion_sort (std::vector<T>& vector);
    //  Render SDL window for quick sort
    static void SDL_quick_sort (std::vector<T>& vector);
    //  Render SDL window for merge sort
    static void SDL_merge_sort (std::vector<T>& vector);

private:
    // Partitioning portion of quick sort
    static int partition(std::vector<T>& vector, int first, int last,
                         int pivot, SDL_Renderer*& renderer);
    // Merge portion of merge sort
    static void merge(std::vector<T>& vector, int first, int split, int last,
                      SDL_Renderer*& renderer);
    // Quick sort method
    static void quick_sort (std::vector<T>& vector, int first, int last,
                            SDL_Renderer*& renderer);
    // Merge sort method
    static void merge_sort (std::vector<T>& vector, int first, int last,
                            SDL_Renderer*& renderer);
    // Display realtime colored sorting
    void display(std::vector<T>& vec, SDL_Renderer*& renderer, 
                 int red, int blue);
    //
    void displayQuick(std::vector<T>& vec, SDL_Renderer*& renderer, int first, 
             int red, int blue, int pivot);
};

/// ----------------------------------------------------------------------------
///  Generate bubble sort using SDL
/// ----------------------------------------------------------------------------
template <class T>
void SDL_bubble_sort (std::vector<T>& vector) {
    // Generate SDL Window object and renderer
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Event windowEvent;
    // Generate 1000x1000 window
    SDL_CreateWindowAndRenderer(1000, 1000, 0, &window, &renderer);
    SDL_RenderSetScale(renderer, 10, 10);

    // Iterate through the vector.
    for (int current = 0; current < vector.size(); current++) {
        for (int iterator = current; iterator < vector.size(); iterator++) {
            // If the current element is greater than the iterating position.
            if (vector[current] > vector[iterator]) {
                std::swap(vector[iterator], vector[current]);
            }
            // Set Window Title
            SDL_SetWindowTitle(window, "Bubble Sort");
            // Clear screen
            SDL_SetRenderDrawColor(renderer,0,0,0,255);
            SDL_RenderClear(renderer);
            
            // Color window
            display(vector, renderer, current, iterator);
            /*display(vector, renderer, iterator, current);*/

            // Present to window
            SDL_RenderPresent(renderer);
            SDL_PumpEvents();
            SDL_Delay(5);
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
}

/// ----------------------------------------------------------------------------
///  Generate selection sort using SDL
/// ----------------------------------------------------------------------------
template <class T>
void SDL_selection_sort (std::vector<T>& vector) {
    //
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Event windowEvent;
    SDL_CreateWindowAndRenderer(1080, 1080, 0, &window, &renderer);
    SDL_RenderSetScale(renderer, 10, 10);

    // Iterate through the vector.
    for (int index = 0; index < vector.size(); index++) {
        // Selected index.
        int selected = index;

        for (int iterator = index; iterator < vector.size(); iterator++) {
            // Smaller value found
            if (vector[selected] > vector[iterator]) {
                // Reassign selected index to smaller value
                selected = iterator;
            }
            // Set Window Title
            SDL_SetWindowTitle(window, "Selection Sort");
            // Clear screen
            SDL_SetRenderDrawColor(renderer,0,0,0,255);
            SDL_RenderClear(renderer);
            
            // Color window
            display(vector, renderer, index, iterator);

            // Present to window
            SDL_RenderPresent(renderer);
            SDL_PumpEvents();
            SDL_Delay(5);
        }

        std::swap(vector[selected], vector[index]);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
}

/// ----------------------------------------------------------------------------
/// Generate insertion sort using SDL
/// ----------------------------------------------------------------------------
template <class T>
void SDL_insertion_sort (std::vector<T>& vector) {
    // Generate Window and Renderer
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Event windowEvent;
    SDL_CreateWindowAndRenderer(1080, 1080, 0, &window, &renderer);
    SDL_RenderSetScale(renderer, 10, 10);

    // Temp memory to hold smaller value.
    int temp;

    // Iterate through the vector.
    for (int iterator = 0; iterator < vector.size(); iterator++) {
        // If the current value is smaller than the value to the left.
        if (vector[iterator] < vector[iterator - 1]) {
            // Store the current smaller value.
            temp = vector[iterator];

            // Store the index of the smaller value.
            int index = iterator;

            // While at the location of the smaller value
            // iterate the vector backwards sorting.
            while (index > 0 && vector[index - 1] > temp) {
                // Move the larger number to the right.
                vector[index] = vector[index - 1];
                // Iterate down the vector.
                index--;

                // Set Window Title
                SDL_SetWindowTitle(window, "Insertion Sort");
                //Clear screen
                SDL_SetRenderDrawColor(renderer,0,0,0,255);
                SDL_RenderClear(renderer);
                
                // Color window
                display(vector, renderer, iterator, index);

                // Present to window
                SDL_RenderPresent(renderer);
                SDL_PumpEvents();
                SDL_Delay(5);
            }
            // Move smaller value to the left.
            vector[index] = temp;
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
}

/// ----------------------------------------------------------------------------
///  Partition portion of quick sort
/// ----------------------------------------------------------------------------
template <class T>
static int partition(std::vector<T>& vector, int first, int last,
                     int pivot, SDL_Renderer*& renderer) {
    int leftIndex = first;
    int rightIndex = first;

    while(leftIndex <= last) {
        if(vector[leftIndex] > pivot) {
            leftIndex++;
        }
        else {
            std::swap(vector[leftIndex], vector[rightIndex]);
            leftIndex++;
            rightIndex++;
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);
        
        // Color window
        displayQuick(vector, renderer, first, leftIndex, rightIndex, pivot);

        // Present to window
        SDL_RenderPresent(renderer);
        SDL_PumpEvents();
        SDL_Delay(10);
    }

    return rightIndex - 1;
}

/// ----------------------------------------------------------------------------
///  Quick sort method
/// ----------------------------------------------------------------------------
template <class T>
static void quick_sort (std::vector<T>& vector, int first, int last,
                        SDL_Renderer*& renderer) {
    // Base case.
    if (first < last) {
        // Pivot
        int pivot = vector[last];

        // Position of partitioning
        int position = partition(vector, first, last, pivot, renderer);

        // Divide and sort left side from index of sorted portion.
        quick_sort(vector, first, position - 1, renderer);
        // Divide and sort right side from index of sorted portion.
        quick_sort(vector, position + 1, last, renderer);
    }
}

/// ----------------------------------------------------------------------------
///  Generate quick sort using SDL
/// ----------------------------------------------------------------------------
template <class T>
static void SDL_quick_sort (std::vector<T>& vector) {
    //
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Event windowEvent;
    SDL_CreateWindowAndRenderer(1080, 1080, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "Quick Sort");
    SDL_RenderSetScale(renderer, 10, 10);

    quick_sort(vector, 0, vector.size() - 1, renderer);

    SDL_DestroyWindow(window);
    SDL_Quit();
}

/// ----------------------------------------------------------------------------
///  Merge portion of merge sort
/// ----------------------------------------------------------------------------
template <class T>
static void merge(std::vector<T>& vector, int first, int split, int last,
                  SDL_Renderer*& renderer) {
    int n1 = split - first + 1;     // Index of left side
    int n2 = last - split;          // Index of right side
    int Left[n1];                   // Left split list
    int Right[n2];                  // Right split list

    // Fill left list
    for(int i = 0; i < n1; i++) {
        Left[i] = vector[first + i];
    }
    // Fill right list
    for(int j = 0; j < n2; j++) {
        Right[j] = vector[split + 1 + j]; 
    }

    int leftIndex = 0;          // Left list index
    int rightIndex = 0;         // Right list index
    int vecIndex = first;       // Vector index

    while(leftIndex < n1 && rightIndex < n2) {
        // Sort vector with smaller value from left container.
        if(Left[leftIndex] <= Right[rightIndex]) {
            vector[vecIndex] = Left[leftIndex];
            leftIndex++;
        }
        // Sort vector with smaller value from right container.
        else {
            vector[vecIndex] = Right[rightIndex];
            rightIndex++;
        }
        vecIndex++;

        // Clear screen
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);
        
        // Color window
        display(vector, renderer, leftIndex, vecIndex);

        // Present to window
        SDL_RenderPresent(renderer);
        SDL_PumpEvents();
        SDL_Delay(10);
    }

    // Insert remaining elements from left container.
    while (leftIndex < n1) {
        vector[vecIndex] = Left[leftIndex];
        leftIndex++;
        vecIndex++;
    }
    // Insert remaining elements from right container.
    while (rightIndex < n2) {
        vector[vecIndex] = Right[rightIndex];
        rightIndex++;
        vecIndex++;
    }
}

/// ----------------------------------------------------------------------------
///  Merge sort method
/// ----------------------------------------------------------------------------
template <class T>
static void merge_sort (std::vector<T>& vector, int first, int last,
                        SDL_Renderer*& renderer) {
    //
    if(first < last) {
        int split = (first + (last - first)/2);     // Index to split list

        // Split left side
        merge_sort(vector, first, split, renderer);
        // Split right side
        merge_sort(vector, split + 1, last, renderer);

        // Merge lists
        merge(vector, first, split, last, renderer);
    }
}

/// ----------------------------------------------------------------------------
///  Generate insertion sort using SDL
/// ----------------------------------------------------------------------------
template <class T>
static void SDL_merge_sort (std::vector<T>& vector) {
    //
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Event windowEvent;
    SDL_CreateWindowAndRenderer(1080, 1080, 0, &window, &renderer);
    SDL_RenderSetScale(renderer, 10, 10);
    SDL_SetWindowTitle(window, "Merge Sort");

    merge_sort(vector, 0, vector.size() - 1, renderer);

    SDL_DestroyWindow(window);
    SDL_Quit();
}

/// ----------------------------------------------------------------------------
/// Set colors of bars in SDL window
/// Green ==> Sorted
/// Blue ==> Traversing
/// Red ==> Value to compare
/// White ==> Unsorted values
/// ----------------------------------------------------------------------------
template <class T>
void display(std::vector<T>& vec, SDL_Renderer*& renderer, 
             int red, int blue) {
    // The index to color
    int index = 0;

    for(auto i : vec) {
        if(index == red) {
            // Number to compare "Red"
            SDL_SetRenderDrawColor(renderer, 255,0,0,255);
        }
        else if (index == blue){
            // Walker value "Blue"
            SDL_SetRenderDrawColor(renderer, 0,0,255,255);
        }
        else if (index < red) {
            // Sorted values "Green"
            SDL_SetRenderDrawColor(renderer, 122,195,106,255);
        }
        else {
            // Unsorted values "White"
            SDL_SetRenderDrawColor(renderer, 255,255,255,255);
        }

        // Render the lines
        SDL_RenderDrawLine(renderer, index, 99, index, 99 - i);
        // Increment our counter
        index++;

    }
}

/// ----------------------------------------------------------------------------
/// Set colors of bars in SDL window
/// Green ==> Sorted
/// Blue ==> Traversing
/// Red ==> Value to compare
/// White ==> Unsorted values
/// ----------------------------------------------------------------------------
template <class T>
void displayQuick(std::vector<T>& vec, SDL_Renderer*& renderer, int first,
             int red, int blue, int pivot) {
    // The index to color
    int index = 0;

    for(auto i : vec) {
        if(index == red) {
            // Number to compare "Red"
            SDL_SetRenderDrawColor(renderer, 255,0,0,255);
        }
        else if (index == blue){
            // Walker value "Blue"
            SDL_SetRenderDrawColor(renderer, 0,0,255,255);
        }
        else if(i == pivot) {
            SDL_SetRenderDrawColor(renderer, 255,191,0,255);
        }
        else if (index < first) {
            // Sorted values "Green"
            SDL_SetRenderDrawColor(renderer, 122,195,106,255);
        }
        else {
            // Unsorted values "White"
            SDL_SetRenderDrawColor(renderer, 255,255,255,255);
        }

        // Render the lines
        SDL_RenderDrawLine(renderer, index, 99, index, 99 - i);
        // Increment our counter
        index++;

    }
}

#endif  /* genSDL_H_ */
