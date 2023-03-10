#include <stdio.h>
#include <stdlib.h>
typedef struct rb_node {
struct rb_node* parent;
struct rb_node* left;
struct rb_node* right;
int value;
} rb_node;

void init_rb (rb_node* header, int value){
    header->left = NULL;
    header->right = NULL;
    header->parent = NULL;
    header->value = value;
}

void insert_rb (rb_node* header, int value){
    rb_node * p_new_node = malloc(sizeof (rb_node));
    p_new_node->value = value;
    p_new_node->left = NULL;
    p_new_node->right = NULL;
    if (value > header->value){
        if (header->right == NULL){
            header->right = p_new_node;
            p_new_node->parent = header;
            
            printf("%d inserted right \n", value);

        }
        else {
            insert_rb(header->right, value);
        }
    }
    else {
        if (header->left == NULL){
            header->left = p_new_node;
            p_new_node->parent = header;
            printf("% inserted left \n", value);
        }
        else {
            insert_rb(header->left, value);
        }
    }
}

void print_tree(rb_node * header, int depth){
    //printf("%d (%d)",header->value, depth);
    printf("%d",header->value);
    if(header->left != NULL){
        printf("  ");
        print_tree(header->left, depth + 1);
    }
    if (header->right != NULL){
        printf("\n");
        for (int i = 0; i<=depth; i++){
            printf("   ");
        }
        print_tree(header->right, depth + 1);
    }
}

int main(){
    rb_node new_tree;
    rb_node * p_new_tree = &new_tree;
    init_rb(p_new_tree, 5);
    insert_rb(p_new_tree, 3);
    insert_rb(p_new_tree, 8);
    insert_rb(p_new_tree, 4);
    insert_rb(p_new_tree, 2);
    insert_rb(p_new_tree, 9);
    print_tree(p_new_tree, 0);
    printf("\n");
}
