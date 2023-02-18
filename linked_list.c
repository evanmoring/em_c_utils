#include <stdio.h>
#include <stdlib.h>

typedef struct em_sll_item{
    int value;
    struct em_sll_item* next;
} em_sll_item;

typedef struct {
    em_sll_item* next;
    int length;
} em_sll_header;

int em_sll_insert(em_sll_header* header, int index, int value){
    em_sll_item *new_item = malloc(sizeof *new_item);
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

    em_sll_item* last_item_p = header->next;
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

int em_sll_remove(em_sll_header* header, int index){
    if (header->next == NULL){
        printf("index out of bound, list is empty");
        exit(0);
    }
    em_sll_item * p_to_remove;
    em_sll_item * item_before;

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
        em_sll_item * p_element_after = p_to_remove->next;
        item_before->next = p_element_after;
    }
    free(p_to_remove);
    header->length --;
}

int em_sll_print(em_sll_header * sll_header){
    em_sll_item * p_reader = sll_header->next;
    while (! (p_reader->next == NULL)){
        printf("%d\n", p_reader->value);
        p_reader = p_reader->next;
    }
    printf("%d\n", p_reader->value);
}

int em_sll_get(em_sll_header * header, int index){
    em_sll_item* item = header->next;
    for (int i = 0; i<index; i++){
        if (item->next == NULL) {
            printf("Index out of range: %d\n", i);
            return 0;
        }
        item = item->next;
    }
    return item->value; 
}

int em_sll_set(em_sll_header * header, int index, int value){
    em_sll_item* item = header->next;
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
    em_sll_header sll_header; 
    sll_header.next = NULL;
    sll_header.length = 0;
    for (int i = 0; i<5; i++){
        em_sll_insert(&sll_header, i, i);
    }
    em_sll_insert(&sll_header, 2, 8);
    em_sll_remove(&sll_header, 3);
    em_sll_print(&sll_header);
    em_sll_set(&sll_header, 2, 9);
    printf("get: %d\n",em_sll_get(&sll_header, 2));
}
