#include <stdio.h>
#include <stdlib.h>

struct Test {
    int num1;
    int  character;
}; 

struct Header {
    struct Item* next;
    int end_flag;
};

struct Item {
    int value;
    struct Item* next;
    int end_flag;
};

void add_element(struct Header* header, int value){
    struct Item *next = malloc(sizeof *next);
    next->value = value;
    if (header->end_flag){
        printf("header has end flag\n");
        next->end_flag = 1;
        header->end_flag = 0;
    }
    else {
       printf("header doesn't have end flag\n");
       next->next = header->next;
       next->end_flag = 0;
    }
    header->next = next;  
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

//    printf("first item location: %p\n", ll_header.next);
//    printf("first item value: %d\n", (*ll_header.next).value);
//    printf("first item end flag: %d\n", (*ll_header.next).end_flag);
//    printf("Working item value: %d\n", working_item.value);

    for (int i = 0; i<5; i++){
        add_element(&ll_header, i);
    }
    print_ll(&ll_header);

    printf("\n");
    remove_element(&ll_header, 2);
    print_ll(&ll_header);
}
