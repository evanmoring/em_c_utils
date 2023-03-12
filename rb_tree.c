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

void walk_rb (rb_node* header){
    if (header != NULL){
        walk_rb(header->left);
        printf("%d\n",header->value);
        walk_rb(header->right);
    }
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

rb_node* search_rb (rb_node* header, int val){
    if (header == NULL || val == header->value){
        return header;
    }
    if (val < header->value){
        return search_rb(header->left, val);
    }
    else {
        return search_rb(header->right, val);
    }
}

rb_node* min_rb (rb_node* header){
    while (header->left != NULL){
        header = header->left;
    }
    return header;
}

rb_node* max_rb (rb_node* header){
    while (header->right != NULL){
        header = header->right;
    }
    return header;
}

int transplant_rb (rb_node * replacee, rb_node* replacer){
    // pg 296
    if(replacee->parent == NULL){
        replacer->parent = NULL;
    }
    else if (replacee == replacee->parent->left){
        replacee->parent->left = replacer;
    }
    else {
        replacee->parent->right = replacer;
    }
    if (replacer != NULL){
        replacer->parent = replacee->parent;
    }
}

// TODO test
int delete_rb (rb_node* header, rb_node* to_delete){
    // three cases: 
    // no left child, we replace with right child
    if (to_delete->left == NULL){
        transplant_rb(to_delete, to_delete->right);
    }
    // no right child, we replace with left child
    else if (to_delete->right == NULL){
        transplant_rb(to_delete, to_delete->left);
    }
    // take the minimum of the subtree rooted by the right child and replace to_delete with it
    else {
        rb_node* replacer = min_rb(to_delete->right);
        if (replacer->parent != to_delete){
            transplant_rb(replacer, replacer->right);
            replacer->right = to_delete->right;
            replacer->right->parent = replacer;
        }
        transplant_rb(to_delete, replacer);
        replacer->left = to_delete->left;
        replacer->left->parent = replacer;
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
    if(header->parent == NULL){
        printf("\n");
    }
}

int test_search(){
    rb_node new_tree;
    rb_node * p_new_tree = &new_tree;
    init_rb(p_new_tree, 5);
    insert_rb(p_new_tree, 3);
    insert_rb(p_new_tree, 8);
    insert_rb(p_new_tree, 4);
    insert_rb(p_new_tree, 2);
    insert_rb(p_new_tree, 9);
    insert_rb(p_new_tree, 0);
    rb_node * searched = search_rb(p_new_tree, 5);
    if (searched != NULL){
        printf("searched: %d\n", searched->value);
    }
    else{
        printf("not in tree");
    }
    rb_node * min = min_rb(p_new_tree);
    printf("min: %d\n", min->value);
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
    insert_rb(p_new_tree, 0);
    print_tree(p_new_tree, 0);
    test_search();
//    walk_rb(p_new_tree);
//    printf("\n");

}
