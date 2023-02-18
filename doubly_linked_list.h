#include <stdio.h>
#include <stdlib.h>

typedef struct em_dll_item{
    int value;
    struct em_dll_item* next;
    struct em_dll_item* previous;
    int header_flag;
} em_dll_item;

void em_dll_initialize(em_dll_item* header){
    header->header_flag = 1;
    header->next = NULL;
}

int em_dll_insert(em_dll_item* header, int index, int value){
    em_dll_item *new_item = malloc(sizeof *new_item);
    new_item->value = value;
    new_item->next = NULL;
    new_item->header_flag = 0;
    em_dll_item* last_item_p = header;
    for (int i = 0; i<index; i++){
        if (last_item_p->next == NULL) {
            printf("Index out of range: %d\n", i);
            return 0;
        }
        last_item_p = last_item_p->next;
    }
    new_item->next = last_item_p->next;
    new_item->previous = last_item_p;
    last_item_p->next = new_item;
    return 1;
}

int em_dll_remove(em_dll_item* header, int index){
    em_dll_item * p_to_remove;
    em_dll_item * item_before;

    p_to_remove = header;

    item_before = p_to_remove;
    for (int i = 0; i<index; i++){
        item_before = item_before->next;
    }
    p_to_remove = item_before->next;
    em_dll_item * p_element_after = p_to_remove->next;
    item_before->next = p_element_after;
    p_element_after->previous = item_before;
    free(p_to_remove);
}

int em_dll_print(em_dll_item * dll_header){
    em_dll_item * p_reader = dll_header->next;
    while (! (p_reader->next == NULL)){
        printf("%d\n", p_reader->value);
        p_reader = p_reader->next;
    }
    printf("%d\n", p_reader->value);
}

int em_dll_get(em_dll_item * header, int index){
    em_dll_item* item = header->next;
    for (int i = 0; i<index; i++){
        if (item->next == NULL) {
            printf("Index out of range: %d\n", i);
            return 0;
        }
        item = item->next;
    }
    return item->value; 
}

int em_dll_set(em_dll_item* header, int index, int value){
    em_dll_item* item = header->next;
    for (int i = 0; i<index; i++){
        if (item->next == NULL) {
            printf("Index out of range: %d\n", i);
            exit(1);
            return 0;
        }
        item = item->next;
    }
    item->value = value; 
}
