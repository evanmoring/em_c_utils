#include <stdio.h>
#include <math.h>
#define SIZE 10

int parent(int i){
    return i>>1;
}

int left(int i){
    if (i == 0){
        return 1;
    }
    return i<<1;
}

int right(int i){
    if (i == 0){
        return 2;
    }
    i = i<<1;
    i++;
    return i;
}
int array[SIZE] = {6,1,7,6,1,7,4,2,7,6};


void print_heap(int* A) {
    int height = 1;
    for(int i = 0; i < SIZE; i++){
        printf("%d ", A[i]);
        int row_max = (1 << height) -2;
        if (i >= row_max) {
            printf("\n");
            height ++;
       }
    }
}

int max_heapify(int* A, int index) {
    int l = left(index);
    int r = right(index);
    int largest;
    if (l <= SIZE && A[l] > A[index]) {
        largest = l;
    } 
    else {
        largest = index;
    }
    if (r <= SIZE && A[r] > A[largest]) {
        largest = r;
    }
    if (largest != index){
        int temp = A[index];
        A[index] = A[largest];
        A[largest] = temp;
        max_heapify(A, largest);
    } 
}

void build_max_heap(int* A){
    int half = SIZE >> 1;
    for (int i = SIZE; i >= 0; i--){
        max_heapify(A, i);
    }
}

int main(){
    build_max_heap(array);
    print_heap(array);
    
}


