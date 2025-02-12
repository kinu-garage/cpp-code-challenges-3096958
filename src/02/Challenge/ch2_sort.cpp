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

int* merge(int * arr_merged, int *arr_a, int *arr_b){
    int index_mergedlist = 0;
    // Length of arr_b is always the same or smaller than arr_a.
    int size_b = sizeof(arr_b) / sizeof(arr_b[0]);
    for (int i=0; i < size_b; i++, index_mergedlist++){
        if (arr_a != nullptr && arr_b != nullptr){
            if (arr_a[i] < arr_b[i]){
                arr_merged[index_mergedlist] = arr_a[i];
            }
            else if (arr_b[i] < arr_a[i]){
                arr_merged[index_mergedlist] = arr_b[i];
            }
        }
        else{
            break;
        }
    }
    //TODO Had to consider if only either one of the lists is not yet empty but skipping that case here for now.
    return arr_merged;
}

/**
 * Split a list to 2 lists, then run recursively until the input list
 * is no longer splitable.  
 */
int* merge_sort(int *arr, int len){
    if (len==1){
        return arr;
    }
    int src_start_index = 0; // Index to start copying from
    int largest_index_a = len/2;
    int largest_index_b = largest_index_a;
    int arr_merged[len];
    
    if (len % 2 != 0){
        // When len is odd, 
        largest_index_a ++;
    }

    int array_1sthalf[largest_index_a];
    int array_2ndhalf[largest_index_a];

    std::cout << "largest_index_a: " << largest_index_a << " Address of array_1sthalf: " << static_cast<void*>(&array_1sthalf) << " array_2ndhalf: " << static_cast<void*>(&array_2ndhalf) << std::endl;

    // Populate array_1sthalf
    for (int i = 0; i < largest_index_a; i++){
        array_1sthalf[i] = arr[i];
    }
    // 2nd half list
    src_start_index = largest_index_a;
    std::cout << "Input arr len: " << len << " largest_index_a: " << largest_index_a << " For arr_a, src_start_index: " << src_start_index << std::endl;
    for (int i = 0; i < len - largest_index_a; i++){
        array_2ndhalf[i] = arr[src_start_index + i];
    }
    std::cout << "array_1sthalf: [";
    print_array(array_1sthalf, largest_index_a);
    std::cout << "] array_2ndhalf: [";
    print_array(array_2ndhalf, largest_index_b);
    std::cout << "]" << std::endl;

    int* array_1sthalf_sorted = merge_sort(array_1sthalf, largest_index_a);
    int* array_2ndhalf_sorted = merge_sort(array_2ndhalf, largest_index_a);
    int len_a = sizeof(array_1sthalf_sorted);
    int len_b = sizeof(array_2ndhalf_sorted);
    if (len_a != len_b){
        throw std::invalid_argument("For now both array must be the same length. Sorry.");
    }
    merge(arr_merged, array_1sthalf_sorted, array_2ndhalf_sorted);
    print_array(arr_merged, len);
    return arr_merged;
}

// sort_array()
// Summary: This function receives an array of integers and sorts it in ascending order.
// Arguments:
//           arr: A pointer acting as the array to sort.
//           n: The size of the array.
// Returns: A boolean value: True on success, false otherwise.
int* sort_array(int *arr, int size_arr){
    //return quick_sort(arr, 0, size_arr -1);
    return merge_sort(arr, size_arr);
}

// Main function
int main(){
    // The following array will be treated as an array of length len. 
    //int array[] = {11, 2, 9, 1, 3, 5, 0, 6, 8, 10, 12, 7, 4};
    int array[] = {9, 2, 1, 3, 5, 0, 4, 10, 11, 6, 8, 7};
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
    //std::cout << "**Final result** Sorted Array: [ ";
    //print_array(array, len);
    //std::cout << "]" << std::endl << std::endl << std::flush;

    return 0;
}