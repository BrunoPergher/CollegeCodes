#include <stdio.h>

void swap(int *a, int *b) {

  int temp = *a;

  *a = *b;

  *b = temp;

}

// To amontoar a subtree rooted with node i
// which is an index in arr[].
// n is size of heap
void heapify(int arr[], int n, int i) {

  // Find largest among root, left child and right child

    // Initialize largest as root
  int largest = i;

  // left = 2*i + 1
  int left = 2 * i + 1;

  // right = 2*i + 2
  int right = 2 * i + 2;

  // If left child is larger than root
  if (left < n && arr[left] > arr[largest])

    largest = left;

  // If right child is larger than largest
    // so far
  if (right < n && arr[right] > arr[largest])

    largest = right;

  // Swap and continue heapifying if root is not largest
  // If largest is not root
  if (largest != i) {

    swap(&arr[i], &arr[largest]);

    // Recursively heapify the affected
    // sub-tree
    heapify(arr, n, largest);

  }

}

// Main function to do heap sort
void heapSort(int arr[], int n) {

  // Build max heap
  for (int i = n / 2 - 1; i >= 0; i--)

    heapify(arr, n, i);

  // Heap sort
  for (int i = n - 1; i >= 0; i--) {

    swap(&arr[0], &arr[i]);

    // Heapify root element to get highest element at root again
    heapify(arr, i, 0);

  }

}

// A utility function to print array of size n
void printArray(int arr[], int n)
{
  for (int i = 0; i < n; i++)
    printf("%d ", arr[i]);
  printf("\n");

}

// Driver code

int main()
{
  int arr[] = {4, 10, 3, 5, 1};
  int n = sizeof(arr) / sizeof(arr[0]);
  heapSort(arr, n);
  printf("Array Ordenado \n");
  printArray(arr, n);

}