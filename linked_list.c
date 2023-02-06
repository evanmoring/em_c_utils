#include <stdio.h>
#include <stdlib.h>

struct Header {
    struct Item* next;
    int end_flag;
};

struct Item {
    int value;
    struct Item* next;
    int end_flag;
};

int add_element(struct Header* header, int value, int index){
    struct Item *new_item = malloc(sizeof *new_item);
    new_item->value = value;

    // handle insertion at 0
    if (index == 0) {
        if (header->end_flag) {
            new_item->end_flag = 1;
            header->end_flag = 0;
        }
        else {
            new_item->next = header->next;
            new_item->end_flag = 0;
        }
        header->next = new_item;
        return 1;
    }
    else if (header->end_flag){
        printf("Index out of range: 0\n");
        return 0;
    }

    struct Item* last_item_p = header->next;
    for (int i = 1; i<index; i++){
        if (last_item_p->end_flag) {
            printf("Index out of range: %d\n", i);
            return 0;
        }
        last_item_p = last_item_p->next;
    }
    if (last_item_p->end_flag){
        last_item_p->end_flag = 0;
        new_item->end_flag = 1;
    }
    else{
        new_item->next = last_item_p->next;
    }
    last_item_p->next = new_item;
    return 1;
}

int remove_element(struct Header* header, int index){
    if (header->end_flag){
        printf("index out of bound, list is empty");
        exit(0);
    }
    struct Item * p_to_remove;
    struct Item * item_before;

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
        if (p_to_remove->end_flag){
            item_before->end_flag = 1;
        }
        struct Item * p_element_after = p_to_remove->next;
        printf("%p\n", p_element_after);
        item_before->next = p_element_after;
    }
    free(p_to_remove);
}

int print_ll(struct Header * ll_header){
    struct Item * p_reader = ll_header->next;
    while (!p_reader->end_flag){
        printf("%d\n", p_reader->value);
        p_reader = p_reader->next;
    }
    printf("%d\n", p_reader->value);
}

int main(){
    struct Header ll_header; 
    ll_header.end_flag = 1; 
    struct Item working_item = *(ll_header.next);
    for (int i = 0; i<5; i++){
        add_element(&ll_header, i, i);
    }
    add_element(&ll_header, 8, 2);
    remove_element(&ll_header, 3);
    print_ll(&ll_header);
}
