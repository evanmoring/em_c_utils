#include<stdio.h>
#include<stdlib.h>
#include"doubly_linked_list.h"
#define M 10
#define DEPTH 5

typedef struct hashmap {
    int size;
    // pointer to array of pointers to array of pointers to map items.
    // this will turn into a linked list at some point
    em_dll_item * p_storage;
    int prime;
    int a;
    int b;
    int  (*p_hash_func)(int, struct hashmap*, int, int, int);
} hashmap;

int simple_hash(int input, hashmap* p_map, int dummy_a, int dummy_b, int dummy_c){
    int result = input % p_map->size;
    return result;
}

int universal_hash(int input, hashmap* p_map, int prime, int key_a, int key_b){
    // prime should be a prime greater than the size of the set of the universe of keys
    // key_b should be 0 - p
    // key_a should be 1 - p
    if (prime > key_a > 0 && prime > key_b >= 1){
        // ((ak+b) mod p) mod m)
        return  (((key_a * input) + key_b) % prime) % p_map->size;
        
    } else {
        printf("One of the keys is out of range");
    }
}

int test_universal(){
// p = 17 m = 6 h(3)(4)(8) = 5
    hashmap tmp_map;
    tmp_map.size = 6;
    hashmap * p_map = & tmp_map;
    int res =  universal_hash(8, p_map, 17, 3, 4);
    if (res != 5){
        printf("Universal hash is broken");
        return 1;
    }
    else { printf("Universal hash test passed");}
    
}

int assign_hash(int input, hashmap*  p_map){
    int result = p_map->p_hash_func(input, p_map, p_map->prime, p_map->a ,p_map->b);
    em_dll_item * p_header = &(p_map->p_storage[result]);
    em_dll_insert(p_header, 0, input);
}

hashmap * initialize_hashmap(hashmap * empty_map){
    em_dll_item * p_storage = (em_dll_item *)malloc(empty_map->size * sizeof(em_dll_item));  
    for (int i = 0; i < empty_map->size; i++){
        em_dll_item header;
        em_dll_item * p_header = &header;
        em_dll_initialize(p_header);
        p_storage[i] =  header;
    }
    empty_map->p_storage = p_storage;
    return empty_map;
}

int hm_get(hashmap* p_map, int key){
    // return 1 if key in hashmap, 0 if not
    int hash = p_map->p_hash_func(key,p_map,0,0,0);
    em_dll_item * p_header = &p_map->p_storage[hash];
    int result = 0;
    while(p_header->next != NULL){
        p_header = p_header->next;
        if (p_header->value == key){
            result = 1;
        }
    }
    return result;
}

int main(){
    //test_universal();
    hashmap test_map;
    hashmap * p_test_map = &test_map;
    p_test_map->p_hash_func = simple_hash;
    p_test_map->size = 5;
    initialize_hashmap(p_test_map);
    p_test_map->prime = 17;
    p_test_map->a = 3;
    p_test_map->b = 4;
    
    assign_hash(6, p_test_map);
    int asdf =  hm_get(p_test_map, 6);
    printf("hm get 6: %d\n", asdf);

    asdf =  hm_get(p_test_map, 5);
    printf("hm get 5: %d\n", asdf);

}
