#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ROW 0
#define COLUMN 1

typedef struct matrix {
    int axes;
    int* shape;
    int * matrix;
} matrix;

matrix * init_matrix (int axes, int* shape, int* values) {
    matrix* m = (matrix*) malloc(sizeof(matrix));
    m->axes = axes;
    m->shape = shape;
    
    int size = sizeof(int) * shape[ROW] * shape[COLUMN];
    m->matrix = (int*) malloc(size);
    memcpy(m->matrix, values, size);
    return m;
}

int get_m (matrix* m, int* indices){
    // TODO assert indices in range
    int index = 0;
    int factor = 1;
    int i;
    for (i = m->axes - 1; i >= 0; i--){
        index += indices[i] * factor;
        factor = factor * m->shape[i];
    }
    return m->matrix[index];
}

int set_m (matrix* m, int* indices, int value){
    // TODO assert indices in range
    int index = 0;
    int factor = 1;
    int i;
    for (i = m->axes - 1; i >= 0; i--){
        index += indices[i] * factor;
        factor = factor * m->shape[i];
    }
    m->matrix[index] = value;
}

void show_m(matrix* m){
    int i;
    int ii;
    int index = 0;
    for (ii = 0; ii < m->shape[ROW]; ii++){
        for (i = 0; i < m->shape[COLUMN]; i++){
            printf("%d ", m->matrix[index]);
            index ++;
        }
        printf("\n");
    }
}

matrix* mult_m(matrix* a, matrix* b){
    if (a->shape[COLUMN] != b->shape[ROW]){
        return NULL;
    }
    matrix* o;
    o->matrix = malloc(sizeof(int) * a->shape[ROW] * b->shape[COLUMN]);
    o->shape = malloc(sizeof(int) * 2);
    o->shape[ROW] = a->shape[ROW];
    o->shape[COLUMN] = b->shape[COLUMN];
    o->axes = 2;
    int a_col, a_row, b_col, b_row;
    for (a_row = 0; a_row < a->shape[ROW]; a_row++){
        for(b_col = 0; b_col < b->shape[COLUMN]; b_col++){
            int to_set = 0;
            for (a_col = 0; a_col < a->shape[COLUMN]; a_col++){
                int indices_a[2] = {a_row, a_col};
                int indices_b[2] = {a_col, b_col};
                int from_a = get_m(a, indices_a);
                int from_b = get_m(b, indices_b);
                to_set += from_a * from_b;
            }
            int o_indices[2] = {a_row, b_col};
            set_m(o, o_indices, to_set);       
        }
    }
    return o;
}
