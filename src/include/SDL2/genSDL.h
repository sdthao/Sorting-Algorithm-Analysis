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
    static int partition(std::vector<T>& vector, int first, int last);
    // Merge portion of merge sort
    static void merge(std::vector<T>& vector, int first, int split, int last);
    // Quick sort method
    static void quick_sort (std::vector<T>& vector, int first, int last,
                            SDL_Renderer* renderer);
    // Merge sort method
    static void merge_sort (std::vector<T>& vector, int first, int last,
                            SDL_Renderer* renderer);
    // Display realtime colored sorting
    void display(std::vector<T>& vec, SDL_Renderer* renderer, 
                 int red, int blue);

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
    SDL_CreateWindowAndRenderer(1000, 1000, 0, &window, &renderer);
    SDL_RenderSetScale(renderer, 10, 10);

    // Temp memory for smaller vector element.
    int temp;

    // Iterate through the vector.
    for (auto iterator = 0; iterator < vector.size(); iterator++) {
        for (auto index = iterator; index < vector.size(); index++) {
            // If the current element is greater than the adjacent element.
            if (vector[iterator] > vector[index]) {
                std::swap(vector[index], vector[iterator]);
            }
            // Clear screen
            SDL_SetRenderDrawColor(renderer,0,0,0,255);
            SDL_RenderClear(renderer);
            
            // Color window
            display(vector, renderer, iterator, index);

            // Present to window
            SDL_RenderPresent(renderer);
            SDL_PumpEvents();
            SDL_Delay(20);
        }
    }
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

        // Clear screen
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);
        
        // Color window
        display(vector, renderer, *iterator, *selected);

        // Present to window
        SDL_RenderPresent(renderer);
        SDL_PumpEvents();
        SDL_Delay(20);
    }
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
            
            // ****TODO****
            // Clear screen
            // SDL_SetRenderDrawColor(renderer,0,0,0,255);
            // SDL_RenderClear(renderer);
            
            // // Color window
            // display(vector, renderer, *iteration, *index);

            // // Present to window
            // SDL_RenderPresent(renderer);
            // SDL_PumpEvents();
            // SDL_Delay(20);
        }
    }
}

/// ----------------------------------------------------------------------------
///  Partition portion of quick sort
/// ----------------------------------------------------------------------------
template <class T>
static int partition(std::vector<T>& vector, int first, int last) {
    int pivot = vector[first];     // First index as pivot
    int count = 0;                 // Index counter

    // Find index of smallest and update pivot
    for (int i = first + 1; i <= last; i++) {
        if (vector[i] <= pivot) {
            count++;
        }
    }
 
    int partIndex = first + count;     // Index to divide

    std::swap(vector[partIndex], vector[first]);  // Assign smallest index
 
    int leftIndex = first;       // Left index
    int rightIndex = last;       // Right index
 
    while (leftIndex < partIndex && rightIndex > partIndex) {
        // Find index to sort from left side of pivot
        while (vector[leftIndex] <= pivot) {
            leftIndex++;
        }
        // Find index to sort from right side of pivot
        while (vector[rightIndex] > pivot) {
            rightIndex--;
        }
        // Sort list
        if (leftIndex < partIndex && rightIndex > partIndex) {
            std::swap(vector[leftIndex++], vector[rightIndex--]);
        }
    }

    return partIndex;
}

/// ----------------------------------------------------------------------------
///  Quick sort method
/// ----------------------------------------------------------------------------
template <class T>
static void quick_sort (std::vector<T>& vector, int first, int last,
                        SDL_Renderer* renderer) {
    // Base case.
    if (first >= last) {
        return;
    }

    // Partitioning of the vector.
    int pivot = partition(vector, first, last);

    // Clear screen
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);
    
    // Color window
    display(vector, renderer, first, last);

    // Present to window
    SDL_RenderPresent(renderer);
    SDL_PumpEvents();
    SDL_Delay(10);
 
    // Divide and sort left side from index of sorted portion.
    quick_sort(vector, first, pivot - 1, renderer);
    // Divide and sort right side from index of sorted portion.
    quick_sort(vector, pivot + 1, last, renderer);
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
    SDL_RenderSetScale(renderer, 10, 10);

    quick_sort(vector, 0, vector.size() - 1, renderer);
}

/// ----------------------------------------------------------------------------
///  Merge portion of merge sort
/// ----------------------------------------------------------------------------
template <class T>
static void merge(std::vector<T>& vector, int first, int split, int last) {
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
                        SDL_Renderer* renderer) {
    //
    if(first < last) {
        int split = (first + (last - first)/2);     // Index to split list

        // Split left side
        merge_sort(vector, first, split, renderer);
        // Split right side
        merge_sort(vector, split + 1, last, renderer);

        // Merge lists
        merge(vector, first, split, last);
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

    merge_sort(vector, 0, vector.size() - 1, renderer);
}

/// ----------------------------------------------------------------------------
/// Set colors of bars in SDL window
/// Green ==> Sorted
/// Blue ==> Traversing
/// Red ==> Value to compare
/// White ==> Unsorted values
/// ----------------------------------------------------------------------------
template <class T>
void display(std::vector<T>& vec, SDL_Renderer* renderer, 
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
        SDL_RenderDrawLine(renderer, index, 99, index, i);
        // Increment our counter
        index++;

    }
}

#endif  /* genSDL_H_ */
