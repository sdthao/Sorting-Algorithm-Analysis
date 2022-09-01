/// @file: Sort.h
/// @author: Sao Thao 
/// @date: 2022-31-08
/// @note: This class implements the analysis of common sorting
/// algorithms such as bubble sort, insertion sort, slection sort
/// merge sort, and quick sort.

#ifndef SORT_H_
#define SORT_H_

#include <vector>

/// ----------------------------------------------------------------------------
///                             Sort Class
/// ----------------------------------------------------------------------------
class Sort {
public:
	// Bubble sort method
	static void bubble_sort(std::vector<int>& vector);
	// Selection sort method
	static void selection_sort(std::vector<int>& vector);
	// Insertion sort method
	static void insertion_sort(std::vector<int>& vector);
	// Merge sort method
	static void merge_sort(std::vector<int>& vector, int first, int last);
	// Quick sort method
	static void quick_sort(std::vector<int>& vector, int first, int last);

private:
	// Partition portion of quick sort
	static int partition(std::vector<int>& vector, int first, int last, int pivot);
	// Merging portion of merge sort
	static void merge(std::vector<int>& vector, int first, int split, int last);
};

// ----------------------------------------------------------------------------
// Sorts a vector using the bubble sort algorithm.
// @param [in] vector The vector to sort.
// ----------------------------------------------------------------------------
void Sort::bubble_sort(std::vector<int>& vector) {
    // Iterate through the vector.
    for (int current = 0; current < vector.size(); current++) {
        for (int iterator = current; iterator < vector.size(); iterator++) {
            // If the current element is greater than the iterating position.
            if (vector[current] > vector[iterator]) {
                std::swap(vector[iterator], vector[current]);
            }
        }
    }
}

// ----------------------------------------------------------------------------
// Sorts a vector using the selection sort algorithm.
// @param [in] vector The vector to sort.
// ----------------------------------------------------------------------------
void Sort::selection_sort(std::vector<int>& vector) {
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
        }
        // Swap contents
        std::swap(vector[selected], vector[index]);
    }
}

// ----------------------------------------------------------------------------
// Sorts a vector using the insertion sort algorithm.
// @param [in] vector The vector to sort.
// ----------------------------------------------------------------------------
void Sort::insertion_sort(std::vector<int>& vector) {
    int temp;   // Temp memory to hold smaller value.

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
            }
            // Move smaller value to the left.
            vector[index] = temp;
        }
    }
}

// ----------------------------------------------------------------------------
// Sorts a vector using the quick sort algorithm.
// @param [in] first The beginning of the range of elements to sort.
// @param [in] last The end of the range of elements to sort.
// ----------------------------------------------------------------------------
void Sort::quick_sort(std::vector<int>& vector, int first, int last) {
    if (first < last) {
        // Establish pivot
        int pivot = vector[last];

        // Position of partitioning
        int position = partition(vector, first, last, pivot);

        // Divide and sort left side from index of sorted portion.
        quick_sort(vector, first, position - 1);
        // Divide and sort right side from index of sorted portion.
        quick_sort(vector, position + 1, last);
    }
}

// ----------------------------------------------------------------------------
// Performs partitioning of quick sort.
// @param [in] first The beginning of the range of elements to sort.
// @param [in] last The end of the range of elements to sort.
// @param [in] pivot The pivot value
// @note Last index is always chosen as pivot.
// @returns the index to the left of pivot.
// ----------------------------------------------------------------------------
int Sort::partition(std::vector<int>& vector, int first, int last, int pivot) {
    int leftIndex = first;      // Left index of pivot
    int rightIndex = first;     // Right index of pivot

    // Process sub lists
    while (rightIndex <= last) {
        // Process values larger than pivot
        if (vector[rightIndex] > pivot) {
            rightIndex++;
        }
        else {
            // Process values less than pivot
            std::swap(vector[leftIndex], vector[rightIndex]);
            leftIndex++;
            rightIndex++;
        }
    }

    return leftIndex - 1;
}

// ----------------------------------------------------------------------------
// Sorts a vector using the merge sort algorithm.
// @param [in] first The beginning of the range of elements to sort.
// @param [in] last The end of the range of elements to sort.
// ----------------------------------------------------------------------------
void Sort::merge_sort(std::vector<int>& vector, int first, int last) {
    if (first < last) {
        int split = (first + (last - first) / 2);     // Index to split list

        // Split left side
        merge_sort(vector, first, split);
        // Split right side
        merge_sort(vector, split + 1, last);

        // Merge lists
        merge(vector, first, split, last);
    }
}

// ----------------------------------------------------------------------------
// Performs merging of merge sort.
// @param [in] first The beginning of the range of elements to sort.
// @param [in] split The middle index of the vector.
// @param [in] last The end of the range of elements to sort.
// ----------------------------------------------------------------------------
void Sort::merge(std::vector<int>& vector, int first, int split, int last) {
    int n1 = split - first + 1;     // Index of left side
    int n2 = last - split;          // Index of right side
    int Left[n1];                   // Left split list
    int Right[n2];                  // Right split list

    // Fill left list
    for (int i = 0; i < n1; i++) {
        Left[i] = vector[first + i];
    }
    // Fill right list
    for (int j = 0; j < n2; j++) {
        Right[j] = vector[split + 1 + j];
    }

    int leftIndex = 0;          // Left list index
    int rightIndex = 0;         // Right list index
    int vecIndex = first;       // Vector index

    while (leftIndex < n1 && rightIndex < n2) {
        // Sort vector with smaller value from left container.
        if (Left[leftIndex] <= Right[rightIndex]) {
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

#endif  /* SORT_H_ */
