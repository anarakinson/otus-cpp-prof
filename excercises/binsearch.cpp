#include <iostream>

 
// An iterative binary search function.
int binarySearch(int arr[], int left, int right, int x) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
 
        // Check if x is present at mid
        if (arr[mid] == x)
            return mid;
 
        // If x greater, ignore left half
        if (arr[mid] < x)
            left = mid + 1;
 
        // If x is smaller, ignore right half
        else
            right = mid - 1;
    }
 

    return -1;
}
 
 
int main() {
    int arr[] = { 1, 2, 3, 4, 10, 40, 41, 42 };
    int x = 10;
    int size = sizeof(arr) / sizeof(arr[0]);
    
    int result = binarySearch(arr, 0, size - 1, x);

    if (result == -1) {
        std::cout << "Element is not present in array" << std::endl;
    }
    else {
        std::cout << "Element " << arr[result] << " is at index " << result << std::endl;
    }
    
    return 0;
}
