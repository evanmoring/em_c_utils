#include <stdio.h>
#include <stdlib.h>
#define SIZE 8
int array[SIZE] = {2,8,7,1,3,5,6,4};
//int array[SIZE] = {2,3};

void print_array(int start, int end){
    for (int i = start; i < end; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
}

int partition(int* A, int pivot, int r){
    int x = A[r];
    int i = pivot - 1;
    int temp;
    for (int j = pivot; j < r; j++){
        if (A[j] <= x){
            i++;
            temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    }
    temp = A[i+1];
    A[i+1] = A[r];
    A[r] = temp;
    return i+1;
}
void quicksort(int* A, int pivot, int end){
    if (pivot < end){
        int new_pivot = partition(A, pivot, end);
        quicksort(A, pivot, new_pivot - 1);
        quicksort(A, new_pivot + 1, end);
    }
}

int main(){
    quicksort(array, 0, SIZE - 1);
    printf("FINAL\n");
    print_array(0, SIZE);
}



