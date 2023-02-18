#include<stdio.h>
#include<stdlib.h>

#define M 10
#define DEPTH 5
int * map [M];
int * p_test [5];
int test[5];
struct map_item {
    int key;
    void * data;
};

struct map {
    int size;
    // pointer to array of pointers to array of pointers to map items.
    // this will turn into a linked list at some point
    struct map_item *** p_storage;
    int  (*p_hash_func)(int, struct map*, int, int, int);
};

int simple_hash(int input, struct map* p_map, int dummy_a, int dummy_b, int dummy_c){
    int result = input % p_map->size;
    return result;
}

int universal_hash(int input, struct map* p_map, int prime, int key_a, int key_b){
// prime should be a prime greater than the size of the set of the universe of keys
// key_b should be 0 - p
// key_a should be 1 - p
    if (prime > key_a > 0 && prime > key_b >= 1){
//        ((ak+b) mod p) mod m)
       return  (((key_a * input) + key_b) % prime) % p_map->size;
        
    } else {
        printf("One of the keys is out of range");
    }
}

int test_universal(){
// p = 17 m = 6 h(3)(4)(8) = 5
    struct map tmp_map;
    tmp_map.size = 6;
    struct map * p_map = & tmp_map;
    int res =  universal_hash(8, p_map, 17, 3, 4);
    if (res != 5){
        printf("Universal hash is broken")
        return 1;
    }
    else { printf("Universal hash test passed");}
    
}

int assign_hash(int input, struct map*  p_map){
    int result = p_map->p_hash_func(input,p_map,0,0,0);
    for (int i = 0; i < DEPTH; i++){
        if (p_map->p_storage[result][i] == NULL){
            struct map_item * new_mi;
            new_mi->key = input;
            new_mi->data = NULL;
            printf ("%d %d\n", result, i);
            p_map->p_storage[result][i] = new_mi;
            return 1;
        }
    }
    return 0;
}

struct map * initialize_hashmap(struct map * empty_map){
    struct map_item *** p_storage = (struct map_item***)malloc(empty_map->size * sizeof(struct map_item***));  
    for (int i = 0; i < empty_map->size; i++){
        struct map_item** p_mi = (struct map_item**)malloc(5 * sizeof(struct map_item**));
        for (int j = 0; j<DEPTH;j++){
            p_mi[j] = NULL;

        }
        p_storage[i] =  p_mi;
    }
    empty_map->p_storage = p_storage;
    return empty_map;
}

int main(){
    test_universal();
    return 0;
    struct map test_map;
    struct map * p_test_map = &test_map;
    p_test_map->p_hash_func = simple_hash;
    p_test_map->size = 5;
    initialize_hashmap(p_test_map);
    int r = assign_hash(6, p_test_map);
    int val = p_test_map->p_storage[1][0]->key;
    printf("%d\n", val);

}
