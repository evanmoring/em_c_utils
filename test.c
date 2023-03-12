#include "singly_linked_list.h"
#include "doubly_linked_list.h"
#include "hashmap.h"
#include "bst.h"

int test_dll(){
    em_dll_item dll_h;
    em_dll_item * dll_header = &dll_h; 
    em_dll_initialize(dll_header);
    for (int i = 0; i<5; i++){
        em_dll_insert(dll_header, i, i);
    }
    if (em_dll_get(dll_header, 2) != 2){return 1;}
    em_dll_insert(dll_header, 2, 8);
    em_dll_remove(dll_header, 3);
    if (em_dll_get(dll_header, 2) != 8){return 1;}
    em_dll_set(dll_header, 2, 9);
    if (em_dll_get(dll_header, 3) != 3){return 1;}
    if(*em_dll_index_of(dll_header, 9) != 2){return 1;}
    if(em_dll_index_of(dll_header, 10) != NULL){return 1;}
    return 0;
}

int test_sll(){
    em_sll_header sll_header; 
    sll_header.next = NULL;
    sll_header.length = 0;
    for (int i = 0; i<5; i++){
        em_sll_insert(&sll_header, i, i);
    }
    em_sll_insert(&sll_header, 2, 8);
    if (em_sll_get(&sll_header, 2) != 8){return 1;}
    em_sll_remove(&sll_header, 3);
    if (em_sll_get(&sll_header, 3) != 3){return 1;}
    return 0;
}

int test_hashmap(){
    hashmap test_map;
    hashmap * p_test_map = &test_map;
    hm_initialize(p_test_map, 5, 17, 3, 4, universal_hash);
    
    hm_insert(6, p_test_map);
    if(test_universal_hash()){printf("test_universal_hash failed\n"); return 1;}
    if(! hm_get(p_test_map, 6)){printf("hm_insert test failed\n");return 1;}
    if(hm_get(p_test_map, 5)){printf("hm_get missing key test failed\n");return 1;}
    return 0;
}

int test_bst(){
    bst_node * p_new_tree = init_bst(5);
    insert_bst(p_new_tree, 3);
    insert_bst(p_new_tree, 8);
    insert_bst(p_new_tree, 4);
    insert_bst(p_new_tree, 2);
    insert_bst(p_new_tree, 9);
    insert_bst(p_new_tree, 0);
    bst_node * searched = search_bst(p_new_tree, 5);
    bst_node * s = successor_bst(searched);
    if(s->value != 8){printf("bst successor test failed\n"); return 1;}
    bst_node * p = predecessor_bst(searched);
    if(p->value != 4){printf("bst predecessor test failed\n"); return 1;}
    if (searched->value !=  5){printf("bst search test failed\n");return 1;}
    p_new_tree = delete_bst(p_new_tree, searched);
    searched = search_bst(p_new_tree, 5);
    if (searched != NULL){ printf("bst delete test failed\n");return 1;}
}

int main(){
    if (!test_dll()){ printf("test dll passed\n");}
    else{printf("test dll failed\n");}

    if (!test_sll()){ printf("test sll passed\n");}
    else{printf("test sll failed\n");}

    if (!test_hashmap()){ printf("test hashmap passed\n");}
    else{printf("test hashmap failed\n");}

    if (!test_bst()){ printf("test bst passed\n");}
    else{printf("test bst failed\n");}
}
