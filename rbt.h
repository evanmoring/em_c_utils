#include <stdio.h>
#include <stdlib.h>

enum Color { RED = 0, BLACK = 1};

typedef struct rbt_node {
    struct rbt_node* parent;
    struct rbt_node* left;
    struct rbt_node* right;
    int value;
    int color;
} rbt_node;

typedef struct rbt {
    struct rbt_node* root;
    struct rbt_node* null;
} rbt;


rbt_node* init_rbt (int value){
    rbt_node * header = malloc(sizeof (rbt_node));
    header->left = NULL;
    header->right = NULL;
    header->parent = NULL;
    header->value = value;
    header->color = BLACK;
    return header;
}

void left_rotate(rbt_node* n){
    // TODO test
    rbt_node* y = n->right;
    n->right = y->left;
    if (y->left != NULL){
        y->left->parent = n;
    }
    y->parent = n->parent;
    if (n->parent == NULL){
        y->parent = NULL;
    } 
    else if (n == n->parent->left){
        n->parent->left = y;
    }
    else {
        n->parent->right = y;
    }
    y->left = n;
    n->parent = y;
}

void right_rotate(rbt_node* n){
    // TODO test
    rbt_node* y = n->left;
    n->right = y->right;
    if (y->right != NULL){
        y->right->parent = n;
    }
    y->parent = n->parent;
    if (n->parent == NULL){
        y->parent = NULL;
    } 
    else if (n == n->parent->right){
        n->parent->right = y;
    }
    else {
        n->parent->left = y;
    }
    y->right = n;
    n->parent = y;
}

void walk_rbt (rbt_node* header){
    if (header != NULL){
        walk_rbt(header->left);
        printf("%d\n",header->value);
        walk_rbt(header->right);
    }
}

void insert_fixup_rbt(rbt_node* header, rbt_node* node){
    while (node->parent->color == RED){
        if (node->parent == node->parent->parent->left){
            rbt_node* y = node->parent->parent->right; // uncle
            if (y->color == RED){
                // case 1, uncle is red
                node->parent->color = BLACK;
                y->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            }
            else if (node == node->parent->right){
                // case 2 node is a right child
                node = node->parent;
                left_rotate(node);
            }
            else {
                // case 3 node is a left child
                node->parent->color = BLACK;
                node->parent->parent = RED;
                right_rotate(node->parent->parent);
            }
        }
        else{
            // TODO same for reverse
        }
    }
}


void insert_rbt (rbt_node* header, int value){
    //TODO test
    rbt_node * p_new_node = malloc(sizeof (rbt_node));
    p_new_node->value = value;
    p_new_node->left = NULL;
    p_new_node->right = NULL;
    p_new_node->color = RED;
    p_new_node->parent = NULL;
    rbt_node* x = header;
    rbt_node* y = NULL;
    while (x != NULL){
        if (value > x->value){
            y = x;
            x = x->right;
        }
        else {
            y = x;
            x = x->left;
        }
    }
    if(y == NULL){ // handle if tree is empty
        header = p_new_node;
    }
    else {
        if (value > y->value){
            y->right = p_new_node;
        }
        else {
            y->left = p_new_node;
        }
        p_new_node->parent = y;
    }
    insert_fixup_rbt(header,p_new_node);
}

rbt_node* search_rbt (rbt_node* header, int val){
    if (header == NULL || val == header->value){
        return header;
    }
    if (val < header->value){
        return search_rbt(header->left, val);
    }
    else {
        return search_rbt(header->right, val);
    }
}

rbt_node* min_rbt (rbt_node* header){
    while (header->left != NULL){
        header = header->left;
    }
    return header;
}

rbt_node* max_rbt (rbt_node* header){
    while (header->right != NULL){
        header = header->right;
    }
    return header;
}

int transplant_rbt (rbt_node * replacee, rbt_node* replacer){
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

rbt_node* delete_rbt (rbt_node* header, rbt_node* to_delete){
    // three cases: 
    // no left child, we replace with right child
    if (to_delete->left == NULL){
        transplant_rbt(to_delete, to_delete->right);
    }
    // no right child, we replace with left child
    else if (to_delete->right == NULL){
        transplant_rbt(to_delete, to_delete->left);
    }
    // take the minimum of the subtree rooted by the right child and replace to_delete with it
    else {
        rbt_node* replacer = min_rbt(to_delete->right);
        if (replacer->parent != to_delete){
            transplant_rbt(replacer, replacer->right);
            replacer->right = to_delete->right;
            replacer->right->parent = replacer;
        }
        transplant_rbt(to_delete, replacer);
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

rbt_node* successor_rbt(rbt_node* start){
    if(start->right != NULL){
        return min_rbt(start->right);
    }
    rbt_node* par = start->parent;
    while (par != NULL && start == par->right){
        start = par;
        par = par->parent;
    }
    return par;
}

rbt_node* predecessor_rbt(rbt_node* start){
    if(start->left != NULL){
        return max_rbt(start->left);
    }
    rbt_node* par = start->parent;
    while (par != NULL && start == par->left){
        start = par;
        par = par->parent;
    }
    return par;
}

void print_tree(rbt_node * header, int depth){
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
