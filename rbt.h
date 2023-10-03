#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

enum Color { RED = 0, BLACK = 1};
enum Children { LEFT = 0, RIGHT = 1};

typedef struct rbt_node {
    struct rbt_node* parent;
    struct rbt_node* c[2]; // children, LEFT [0] RIGHT [1]
    int value;
    int color;
} rbt_node;

typedef struct rbt {
    struct rbt_node* root;
    struct rbt_node* nill;
} rbt;


rbt* init_rbt (){
    rbt * tree = malloc(sizeof(rbt));
    tree->nill = malloc(sizeof (rbt_node));
    tree->nill->c[LEFT] = tree->nill;
    tree->nill->c[RIGHT] = tree->nill;
    tree->nill->parent = tree->nill;
    tree->nill->value = INT_MIN;
    tree->nill->color = BLACK;
    tree->root = tree->nill;
    return tree;
}

void rotate(rbt* tree, rbt_node* n, int d){
    // d is RIGHT or LEFT
    // TODO test
    rbt_node* y = n->c[!d];
    n->c[!d] = y->c[d];
    if (y->c[d] != tree->nill){
        y->c[d]->parent = n;
    }
    y->parent = n->parent;
    if (n->parent == tree->nill){
        tree->root = y;
    } 
    else if (n == n->parent->c[d]){
        n->parent->c[d] = y;
    }
    else {
        n->parent->c[!d] = y;
    }
    y->c[d] = n;
    n->parent = y;
}

void walk_rbt (rbt_node* header){
    if (header != NULL){
        walk_rbt(header->c[LEFT]);
        printf("%d\n",header->value);
        walk_rbt(header->c[RIGHT]);
    }
}

void insert_fixup_rbt(rbt* tree, rbt_node* node){
    int d;
    while (node->parent->color == RED){
        if (node->parent == node->parent->parent->c[LEFT]){
            d = LEFT;
        }
        else {d = RIGHT;}
        rbt_node* y = node->parent->parent->c[!d]; // uncle
        if (y->color == RED){
            // case 1, uncle is red
            node->parent->color = BLACK;
            y->color = BLACK;
            node->parent->parent->color = RED;
            node = node->parent->parent;
        }
        else {
            if (node == node->parent->c[!d]){
                // case 2 node is a right child
                node = node->parent;
                rotate(tree, node, d);
            }
            // case 3 node is a left child
            node->parent->color = BLACK;
            node->parent->parent->color = RED;
            rotate(tree, node->parent->parent, !d);
        }
    }
    tree->root->color = BLACK;
}

void insert_rbt (rbt* tree, int value){
    //TODO test
    rbt_node * header = tree->root;
    rbt_node * p_new_node = malloc(sizeof(rbt_node));
    p_new_node->value = value;
    p_new_node->c[LEFT] = tree->nill;
    p_new_node->c[RIGHT] = tree->nill;
    p_new_node->color = RED;
    p_new_node->parent = tree->nill;

    rbt_node* x = header;
    rbt_node* y = tree->nill;
    while (x != tree->nill){
        y = x;
        if (value > x->value){
            x = x->c[RIGHT];
        }
        else {
            x = x->c[LEFT];
        }
    }
    p_new_node->parent = y;
    if(y == tree->nill){ // handle if tree is empty
        tree->root = p_new_node;
    }
    else if (value > y->value){
         y->c[RIGHT] = p_new_node;
    }
    else {
        y->c[LEFT] = p_new_node;
    }
    insert_fixup_rbt(tree,p_new_node);
}

rbt_node* search_rbt (rbt_node* header, int val){
    if (header == NULL || val == header->value){
        return header;
    }
    if (val < header->value){
        return search_rbt(header->c[LEFT], val);
    }
    else {
        return search_rbt(header->c[RIGHT], val);
    }
}

rbt_node* min_rbt (rbt_node* header){
    while (header->c[LEFT] != NULL){
        header = header->c[LEFT];
    }
    return header;
}

rbt_node* max_rbt (rbt_node* header){
    while (header->c[RIGHT] != NULL){
        header = header->c[RIGHT];
    }
    return header;
}

int transplant_rbt (rbt_node * replacee, rbt_node* replacer){
    // pg 296
    if(replacee->parent == NULL){
        replacer->parent = NULL;
    }
    else if (replacee == replacee->parent->c[LEFT]){
        replacee->parent->c[LEFT] = replacer;
    }
    else {
        replacee->parent->c[RIGHT] = replacer;
    }
    if (replacer != NULL){
        replacer->parent = replacee->parent;
    }
}

rbt_node* delete_rbt (rbt_node* header, rbt_node* to_delete){
    // three cases: 
    // no left child, we replace with right child
    if (to_delete->c[LEFT] == NULL){
        transplant_rbt(to_delete, to_delete->c[RIGHT]);
    }
    // no right child, we replace with left child
    else if (to_delete->c[RIGHT] == NULL){
        transplant_rbt(to_delete, to_delete->c[LEFT]);
    }
    // take the minimum of the subtree rooted by the right child and replace to_delete with it
    else {
        rbt_node* replacer = min_rbt(to_delete->c[RIGHT]);
        if (replacer->parent != to_delete){
            transplant_rbt(replacer, replacer->c[RIGHT]);
            replacer->c[RIGHT] = to_delete->c[RIGHT];
            replacer->c[RIGHT]->parent = replacer;
        }
        transplant_rbt(to_delete, replacer);
        replacer->c[LEFT] = to_delete->c[LEFT];
        replacer->c[LEFT]->parent = replacer;
        if(replacer->parent == NULL){
            header = replacer;     
        }
    }
    // return header in case there is a new root to the tree
    free(to_delete);
    return header;
}

rbt_node* successor_rbt(rbt_node* start){
    if(start->c[RIGHT] != NULL){
        return min_rbt(start->c[RIGHT]);
    }
    rbt_node* par = start->parent;
    while (par != NULL && start == par->c[RIGHT]){
        start = par;
        par = par->parent;
    }
    return par;
}

rbt_node* predecessor_rbt(rbt_node* start){
    if(start->c[LEFT] != NULL){
        return max_rbt(start->c[LEFT]);
    }
    rbt_node* par = start->parent;
    while (par != NULL && start == par->c[LEFT]){
        start = par;
        par = par->parent;
    }
    return par;
}

void print_tree(rbt* tree, rbt_node * header, int depth){
    printf("%d",header->value);
    if(header->c[LEFT] != tree->nill){
        printf("  ");
        print_tree(tree, header->c[LEFT], depth + 1);
    }
    if (header->c[RIGHT] != tree->nill){
        printf("\n");
        for (int i = 0; i<=depth; i++){
            printf("   ");
        }
        print_tree(tree, header->c[RIGHT], depth + 1);
    }
    if(header->parent == tree->nill){
        printf("\n");
    }
}
