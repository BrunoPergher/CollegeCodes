/* C program for Merge Sort */
#include <stdio.h>
#include <stdlib.h>
 
// Merges 2 subarrays of array principal[].
// primeiro subarray é arr[l..m]
// segundo subarray é arr[m+1..r]
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
 
    /* criado arrays temporarios */
    int L[n1], R[n2];
 
    /* copiado o dado para os arrays temporarios L[] e R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
 
    /* Merge arrays temporarios de volta para o principal arr[l..r]*/
    i = 0; // index inicial do primeiro subarray
    j = 0; // index inicial do segundo subarray
    k = l; // index inicial do subarray merged 
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    /* Copiado o restante dos elementos de L[], se existir algo */
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    /* Copiado o restante dos elementos de R[], se existir algo  */
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 
/* l é o index da esquerda and r é o index da direita*/
void mergeSort(int arr[], int l, int r)
{
    if (l < r) {
        // evitar overflow
        // R é o tamanho do array
        // l começa zerado
        int m = l + (r - l) / 2;
 
        // ordena os dois arrays simultaneos
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        // logo só falta juntar os arrays
        merge(arr, l, m, r);
    }
}
 

void printArray(int A[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}
 
int main()
{
    int arr[] = {4, 10, 3, 5, 1};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
 
    printf("Array dado \n");
    printArray(arr, arr_size);
 
    mergeSort(arr, 0, arr_size - 1);
 
    printf("\nArray ordenado é \n");
    printArray(arr, arr_size);
    return 0;
}