// C++ Code Challenges, LinkedIn Learning

// Challenge #2: Sorting an Array
// Sort the elements in an array in ascending order.
// Implement the algorithm of your choice.
// Don't use STL vectors.
// Don't use a sorting function from a library.

#include <iostream>

void print_array(int arr[], int size_arr) {
    //int size_arr = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < size_arr; i++) {
        std::cout << arr[i] << " ";
    }
}

/* The patition method used in quick sort. */
int partition(int *arr, int index_low, int index_high){
    // In this case we're automatically taking the element at 'index_high' as the pivot.
    // This is a major improvement point in the future.
    // --> TODO Isn't this approach what's mentioned as possibly O(n^2) https://interviewing.io/sorting-interview-questions#quick-sort ?
    std::cout << "partition begins. index_low: " << index_low << " index_high: " << index_high  << std::endl;

    int index_pivot = index_high;
    int val_pivot = arr[index_pivot];
    int index_left = index_low;
    
    for (int index_right = index_low; index_right < index_high; index_right++){
        std::cout << "Loop in partition. index_left=" << index_left << " index_right=" << index_right << " Arr: ";
        print_array(arr, index_high + 1);
        std::cout << std::endl << std::flush;

        if (arr[index_right] < val_pivot){
            int val_left = arr[index_left];
            int val_right = arr[index_right];
            arr[index_right] = val_left;
            arr[index_left] = val_right;
            index_left++;
        }
    }
    // By this point, the array should be split to 2 groups; the one lower and higher than pivot value.
    int val_left_tobe_swapped = arr[index_left];
    arr[index_left] = val_pivot;
    arr[index_pivot] = val_left_tobe_swapped;
    return index_left;
}

bool quick_sort(int *arr, int index_low, int index_high){
    // When index_low passes index_high so that index_low is larger, sort is done.
    if (index_low < index_high){
        int index_pivot = partition(arr, index_low, index_high);
        std::cout << "After partition. index_low: " << index_low << " index_high: " << index_high << " index_pivot: " << index_pivot << " Arr: "; 
        print_array(arr, index_high);
        std::cout << std::endl;
        quick_sort(arr, index_low, index_pivot - 1);
        quick_sort(arr, index_pivot + 1, index_high);
    }
    std::cout << "Done with a quick_sort run. Array returned: ";
    print_array(arr, index_high);
    std::cout << std::endl << std::flush;
    return true;
}

bool merge_sort(int *arr, int index_low, int index_high){
    //TBD
}

// sort_array()
// Summary: This function receives an array of integers and sorts it in ascending order.
// Arguments:
//           arr: A pointer acting as the array to sort.
//           n: The size of the array.
// Returns: A boolean value: True on success, false otherwise.
bool sort_array(int *arr, int size_arr){
    return quick_sort(arr, 0, size_arr -1);
}

// Main function
int main(){
    // The following array will be treated as an array of length len. 
    //int array[] = {11, 2, 9, 1, 3, 5, 0, 6, 8, 10, 12, 7, 4};
    int array[] = {9, 2, 1, 3, 5, 0, 6, 8, 7, 4, 10, 11, 12, 13, 14};
    //const int len = 11; // Don't exceed the length of the array below!
    //const int len = 4;
    const int len = sizeof(array) / sizeof(array[0]);

    // Print the original array
    std::cout << "Original Array: [ ";
    print_array(array, len);
    //for (int i = 0; i < len; i++)
    //    std::cout << array[i] << " ";
    std::cout << "], Size of arr = " << len << std::endl << std::endl << std::flush;

    sort_array(array, len); // Sort the array

    // Print the sorted array
    std::cout << "  Sorted Array: [ ";
    print_array(array, len);
    std::cout << "]" << std::endl << std::endl << std::flush;

    return 0;
}