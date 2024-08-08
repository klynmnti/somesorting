#include <ctime>
#include <iostream>
using namespace std;

void Quicksort_midpoint(int numbers[], int lowInd, int highInd);
int Midpoint_partition(int numbers[], int lowInd, int highInd);
void Quicksort_medianOfThree(int numbers[], int lowInd, int highInd);
int Median_partition(int numbers[], int lowInd, int highInd);
void InsertionSort(int numbers[], int numbersSize);

const int CLOCKS_PER_MS = CLOCKS_PER_SEC/1000; //clock per milliseconds

int main() {
    /* Testing quicksort_midpoint */
    int numbers1[5] = {15, 2, 93, 56, 23};
    cout << endl << "Before quicksort_midpoint: expecting 15, 2, 93, 56, 23" << endl << "---- ";
    for (int i = 0; i < 5; i++) {
        cout << numbers1[i] << " ";
    }
    cout << endl;
    clock_t Start = clock();
    Quicksort_midpoint(numbers1, 0, 5);
    clock_t End = clock();
    int elapsedTime = (End - Start)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << endl << "After quicksort_midpoint: expecting 2, 15, 23, 56, 93" << endl << "---- ";
    for (int i = 0; i < 5; i++) {
        cout << numbers1[i] << " ";
    }
    cout << endl;
    cout << "Elapsed Time: " << elapsedTime << endl << "-----------------------" << endl;

    /* Testing quicksort_medianOfThree */
    int numbers2[5] = {45, 19, 67, 3, 88};
    cout << endl << "Before quicksort_medianOfThree: expecting 45, 19, 67, 3, 88" << endl << "---- ";
    for (int i = 0; i < 5; i++) {
        cout << numbers2[i] << " ";
    }
    cout << endl;
    Start = clock();
    Quicksort_medianOfThree(numbers2, 0, 5);
    End = clock();
    elapsedTime = (End - Start)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << endl << "After quicksort_medianOfThree: expecting 3, 19, 45, 67, 88" << endl << "---- ";
    for (int i = 0; i < 5; i++) {
        cout << numbers2[i] << " ";
    }
    cout << endl;
    cout << "Elapsed Time: " << elapsedTime << endl << "-----------------------" << endl;

    /* Testing insertionSort */
    int numbers3[5] = {12, 74, 99, 3, 25};
    cout << endl << "Before insertionSort: expecting 12, 74, 99, 3, 25" << endl << "---- ";
    for (int i = 0; i < 5; i++) {
        cout << numbers3[i] << " ";
    }
    cout << endl;
    Start = clock();
    InsertionSort(numbers3, 5);
    End = clock();
    elapsedTime = (End - Start)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << endl << "After insertionSort: expecting 3, 12, 25, 74, 99" << endl << "---- ";
    for (int i = 0; i < 5; i++) {
        cout << numbers3[i] << " ";
    }
    cout << endl;
    cout << "Elapsed Time: " << elapsedTime << endl << "-----------------------" << endl;
    
    return 0;
}

/* this function sorts the given array in the range from i to k using quicksort method. 
In this function, pivot is the midpoint element (numbers[(i+k)/2]). */
void Quicksort_midpoint(int numbers[], int lowInd, int highInd) {
    // Base case: If the partition size is 1 or zero elements, then the partition is already sorted
    if (lowInd >= highInd) { return; }
    // Partition the data within the array. 
    // Value lowEndIndex returned from partitioning is the index of the low partition's last element.
    int lowEndIndex = Midpoint_partition(numbers, lowInd, highInd);
    // Recursively sort low partition and high partition
    Quicksort_midpoint(numbers, lowInd, lowEndIndex);
    Quicksort_midpoint(numbers, lowEndIndex + 1, highInd);
}

int Midpoint_partition(int numbers[], int lowInd, int highInd) {
    int midpoint = lowInd + (highInd - lowInd) / 2;
    int pivot = numbers[midpoint];
    bool done = false;
    while (not done) {
        // Increment lowInd while numbers[lowInd] < pivot
        while (numbers[lowInd] < pivot) { lowInd++; }
        // Decrement highInd while pivot < numbers[highInd]
        while (pivot < numbers[highInd]) { highInd--; }
        // If zero or one element remain, then all numbers are partitioned
        if (lowInd >= highInd) { done = true; }
        else {
            // Swap numbers[lowInd] and numbers[highInd] 
            int temp = numbers[lowInd];
            numbers[lowInd] = numbers[highInd];
            numbers[highInd] = temp;
            lowInd++;
            highInd--;
        }
    }
    return highInd;
}

/* this function utilizes different pivot selection technique in quicksort algorithm. 
The pivot is the median of the following three values: leftmost (numbers[i]), 
midpoint (numbers[(i+k)/2]) and rightmost (numbers[k]). */
void Quicksort_medianOfThree(int numbers[], int lowInd, int highInd) {
    // Base case: If the partition size is 1 or zero elements, then the partition is already sorted
    if (lowInd >= highInd) { return; }
    // Partition the data within the array.
    // Value lowEndIndex returned from partitioning is the index of the low partition's last element.
    int lowEndIndex = Median_partition(numbers, lowInd, highInd);
    // Recursively sort low partition and high partition 
    Quicksort_midpoint(numbers, lowInd, lowEndIndex);
    Quicksort_midpoint(numbers, lowEndIndex + 1, highInd);
}

int Median_partition(int numbers[], int lowInd, int highInd) {
    int midpoint = lowInd + (highInd - lowInd) / 2;
    int pivot = max(min(numbers[lowInd],numbers[midpoint]), min(max(numbers[lowInd],numbers[midpoint]),numbers[highInd]));
    bool done = false;
    while (not done) {
        // Increment lowInd while numbers[lowInd] < pivot
        while (numbers[lowInd] < pivot) { lowInd++; }
        // Decrement highInd while pivot < numbers[highInd]
        while (pivot < numbers[highInd]) { highInd--; }
        // If zero or one element remain, then all numbers are partitioned
        if (lowInd >= highInd) { done = true; }
        else {
            // Swap numbers[lowInd] and numbers[highInd] 
            int temp = numbers[lowInd];
            numbers[lowInd] = numbers[highInd];
            numbers[highInd] = temp;
            lowInd++;
            highInd--;
        }
    }
    return highInd;
}

/* this function sorts the given array using InsertionSort method. */
void InsertionSort(int numbers[], int numbersSize) {
    int i, j, temp = 0;
    for (i = 1; i < numbersSize; i++) {
        j = i;
        // Insert numbers[i] into sorted part
        // stopping once numbers[i] in correct position
        while (j > 0 && numbers[j] < numbers[j-1]) {
            // Swap numbers[j] and numbers[j - 1]
            temp = numbers[j];
            numbers[j] = numbers[j-1];
            numbers[j-1] = temp;
            j--;
        }
    }
}