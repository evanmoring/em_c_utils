#include <stdio.h>
#include <stdlib.h>

typedef struct em_ll_item{
    int value;
    struct em_ll_item* next;
} em_ll_item;

typedef struct {
    em_ll_item* next;
    int length;
} em_ll_header;

int em_ll_insert(em_ll_header* header, int index, int value){
    em_ll_item *new_item = malloc(sizeof *new_item);
    new_item->value = value;
    new_item->next = NULL;

    // handle insertion at 0
    if (index == 0) {
        new_item->next = header->next;
        header->next = new_item;
        return 1;
    }
    else if (header->next == NULL){
        printf("Index out of range: 0\n");
        return 0;
    }

    em_ll_item* last_item_p = header->next;
    for (int i = 1; i<index; i++){
        if (last_item_p->next == NULL) {
            printf("Index out of range: %d\n", i);
            return 0;
        }
        last_item_p = last_item_p->next;
    }
    new_item->next = last_item_p->next;
    last_item_p->next = new_item;
    header->length++;
    return 1;
}

int em_ll_remove(em_ll_header* header, int index){
    if (header->next == NULL){
        printf("index out of bound, list is empty");
        exit(0);
    }
    em_ll_item * p_to_remove;
    em_ll_item * item_before;

    p_to_remove = header->next;

    if (index == 0){
        header->next = header->next->next;
    }
    else{
        item_before = p_to_remove;
        for (int i = 1; i<index; i++){
            item_before = item_before->next;
        }
        p_to_remove = item_before->next;
        em_ll_item * p_element_after = p_to_remove->next;
        item_before->next = p_element_after;
    }
    free(p_to_remove);
    header->length --;
}

int em_ll_print(em_ll_header * ll_header){
    em_ll_item * p_reader = ll_header->next;
    while (! (p_reader->next == NULL)){
        printf("%d\n", p_reader->value);
        p_reader = p_reader->next;
    }
    printf("%d\n", p_reader->value);
}

int em_ll_get(em_ll_header * header, int index){
    em_ll_item* item = header->next;
    for (int i = 0; i<index; i++){
        if (item->next == NULL) {
            printf("Index out of range: %d\n", i);
            return 0;
        }
        item = item->next;
    }
    return item->value; 
}

int em_ll_set(em_ll_header * header, int index, int value){
    em_ll_item* item = header->next;
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

int main(){
    em_ll_header ll_header; 
    ll_header.next = NULL;
    ll_header.length = 0;
    for (int i = 0; i<5; i++){
        em_ll_insert(&ll_header, i, i);
    }
    em_ll_insert(&ll_header, 2, 8);
    em_ll_remove(&ll_header, 3);
    em_ll_print(&ll_header);
    em_ll_set(&ll_header, 2, 9);
    printf("get: %d\n",em_ll_get(&ll_header, 2));
}
