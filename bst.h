#include <stdio.h>
#include <stdlib.h>
typedef struct bst_node {
struct bst_node* parent;
struct bst_node* left;
struct bst_node* right;
int value;
} bst_node;

bst_node* init_bst (int value){
    bst_node * header = malloc(sizeof (bst_node));
    header->left = NULL;
    header->right = NULL;
    header->parent = NULL;
    header->value = value;
    return header;
}

void walk_bst (bst_node* header){
    if (header != NULL){
        walk_bst(header->left);
        printf("%d\n",header->value);
        walk_bst(header->right);
    }
}

void insert_bst (bst_node* header, int value){
    bst_node * p_new_node = malloc(sizeof (bst_node));
    p_new_node->value = value;
    p_new_node->left = NULL;
    p_new_node->right = NULL;
    if (value > header->value){
        if (header->right == NULL){
            header->right = p_new_node;
            p_new_node->parent = header;
        }
        else {
            insert_bst(header->right, value);
        }
    }
    else {
        if (header->left == NULL){
            header->left = p_new_node;
            p_new_node->parent = header;
        }
        else {
            insert_bst(header->left, value);
        }
    }
}

bst_node* search_bst (bst_node* header, int val){
    if (header == NULL || val == header->value){
        return header;
    }
    if (val < header->value){
        return search_bst(header->left, val);
    }
    else {
        return search_bst(header->right, val);
    }
}

bst_node* min_bst (bst_node* header){
    while (header->left != NULL){
        header = header->left;
    }
    return header;
}

bst_node* max_bst (bst_node* header){
    while (header->right != NULL){
        header = header->right;
    }
    return header;
}

int transplant_bst (bst_node * replacee, bst_node* replacer){
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

bst_node* delete_bst (bst_node* header, bst_node* to_delete){
    // three cases: 
    // no left child, we replace with right child
    if (to_delete->left == NULL){
        transplant_bst(to_delete, to_delete->right);
    }
    // no right child, we replace with left child
    else if (to_delete->right == NULL){
        transplant_bst(to_delete, to_delete->left);
    }
    // take the minimum of the subtree rooted by the right child and replace to_delete with it
    else {
        bst_node* replacer = min_bst(to_delete->right);
        if (replacer->parent != to_delete){
            transplant_bst(replacer, replacer->right);
            replacer->right = to_delete->right;
            replacer->right->parent = replacer;
        }
        transplant_bst(to_delete, replacer);
        replacer->left = to_delete->left;
        replacer->left->parent = replacer;
        if(replacer->parent == NULL){
            header = replacer;     
        }
    }
    // return header in case there is a new root to the tree
    free(to_delete);
    return header;
}

bst_node* successor_bst(bst_node* start){
    if(start->right != NULL){
        return min_bst(start->right);
    }
    bst_node* par = start->parent;
    while (par != NULL && start == par->right){
        start = par;
        par = par->parent;
    }
    return par;
}

bst_node* predecessor_bst(bst_node* start){
    if(start->left != NULL){
        return max_bst(start->left);
    }
    bst_node* par = start->parent;
    while (par != NULL && start == par->left){
        start = par;
        par = par->parent;
    }
    return par;
}

void print_tree(bst_node * header, int depth){
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
