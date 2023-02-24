#include "doubly_linked_list.h"
#include "singly_linked_list.h"

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

int main(){
    if (!test_dll()){ printf("test dll passed\n");}
    else{printf("test dll failed\n");}

    if (!test_sll()){ printf("test sll passed\n");}
    else{printf("test sll failed\n");}

}
