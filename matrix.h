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
    show_m(o);
}

int main(){
    matrix* m = (matrix*) malloc(sizeof(matrix));
    // initialize matrix
    int example [2][3]= {{1,2,3},{4,5,6}};
    int* p_ex = (int*) malloc(sizeof(example));
    memcpy(p_ex, example, sizeof(int)*6);
    int shape[2] = {2,3};
    int* p_shape = shape;
    int axes = 2;
    matrix* ex_m = init_matrix(axes, p_shape, p_ex);

    int example_b [3][2] = {{7,8},{9,10},{11,12}};
    int* p_ex_b = (int*) malloc(sizeof(example));
    memcpy(p_ex_b, example_b, sizeof(example_b));
    int shape_b[2] = {3,2};
    int* p_shape_b = shape_b;
    matrix* ex_b = init_matrix(axes, p_shape_b, p_ex_b);

    int indexes[2] = {1,1};
    //set_m(ex_m, indexes, 9);
    //show_m(ex_m);
    // should be 58 64 139 154
    // TODO write test
    matrix* ex_c = mult_m(ex_m, ex_b);


    //int indices[2] = {0,2};
    //int* p_indices = indices;
    //show_m(ex_m);
}
