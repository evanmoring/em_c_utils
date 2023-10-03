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
    struct rbt_node* nil;
} rbt;


rbt* init_rbt (){
    rbt * tree = malloc(sizeof(rbt));
    tree->nil = malloc(sizeof (rbt_node));
    tree->nil->c[LEFT] = tree->nil;
    tree->nil->c[RIGHT] = tree->nil;
    tree->nil->parent = tree->nil;
    tree->nil->value = INT_MIN;
    tree->nil->color = BLACK;
    tree->root = tree->nil;
    return tree;
}

void rotate(rbt* tree, rbt_node* n, int d){
    // d is RIGHT or LEFT
    // TODO test
    rbt_node* y = n->c[!d];
    n->c[!d] = y->c[d];
    if (y->c[d] != tree->nil){
        y->c[d]->parent = n;
    }
    y->parent = n->parent;
    if (n->parent == tree->nil){
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
    p_new_node->c[LEFT] = tree->nil;
    p_new_node->c[RIGHT] = tree->nil;
    p_new_node->color = RED;
    p_new_node->parent = tree->nil;

    rbt_node* x = header;
    rbt_node* y = tree->nil;
    while (x != tree->nil){
        y = x;
        if (value > x->value){
            x = x->c[RIGHT];
        }
        else {
            x = x->c[LEFT];
        }
    }
    p_new_node->parent = y;
    if(y == tree->nil){ // handle if tree is empty
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

rbt_node* search_rbt (rbt* tree, rbt_node* header, int val){
    if (header == tree->nil || val == header->value){
        return header;
    }
    if (val < header->value){
        return search_rbt(tree, header->c[LEFT], val);
    }
    else {
        return search_rbt(tree, header->c[RIGHT], val);
    }
}

rbt_node* min_rbt (rbt* tree, rbt_node* header){
    while (header->c[LEFT] != tree->nil){
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

int transplant_rbt (rbt* tree, rbt_node * replacee, rbt_node* replacer){
    if(replacee->parent == tree->nil){
        tree->root = replacer;
    }
    else if (replacee == replacee->parent->c[LEFT]){
        replacee->parent->c[LEFT] = replacer;
    }
    else {
        replacee->parent->c[RIGHT] = replacer;
    }
    replacer->parent = replacee->parent;
}

static void delete_fixup_rbt (rbt* tree, rbt_node* x) {
    rbt_node* w;
    int dir;
    while (x != tree->root && x->color == BLACK){
        dir = RIGHT;
        if (x == x->parent->c[LEFT]){
            dir = LEFT;
        }
        w = x->parent->c[!dir];
        if (w->color == RED){
            w->color = BLACK;
            x->parent->color = RED;
            rotate(tree, x->parent, dir);
            w = x->parent->c[!dir];
        }
        if (w->c[dir]->color == BLACK && w->c[!dir]->color == BLACK){
            w->color = RED;
            x = x->parent;
        }
        else { 
            if (w->c[!dir]->color == BLACK){
                w->c[dir]->color = BLACK;
                w->color = RED;
                rotate(tree, w, !dir);
                w = x->parent->c[!dir];
            }
            w->color = x->parent->color;
            x->parent->color = BLACK;
            w->c[!dir]->color = BLACK;
            rotate(tree, x->parent, dir);
            x = tree->root;
        }

    }
    x->color = BLACK;
}

void delete_rbt (rbt* tree, int val){
    rbt_node* to_delete = search_rbt(tree, tree->root, val);
    rbt_node* x;
    rbt_node* y;
    y = to_delete;
    int y_orig_color = to_delete->color;

    if (to_delete->c[LEFT] == tree->nil){
        x = to_delete->c[RIGHT];
        transplant_rbt(tree, to_delete, to_delete->c[LEFT]);
    }
    else if (to_delete->c[RIGHT] == tree->nil){
        x = to_delete->c[LEFT];
        transplant_rbt(tree, to_delete, to_delete->c[RIGHT]);
    }
    else {
        y = min_rbt(tree, to_delete->c[RIGHT]);
        y_orig_color = y->color;
        x= y->c[RIGHT];
        if (y->parent == to_delete){
            x->parent = y;
        }
        else{
            transplant_rbt(tree,y,y->c[RIGHT]);
            y->c[RIGHT] = to_delete->c[RIGHT];
            y->c[RIGHT]->parent = y;
        }
        transplant_rbt(tree, to_delete, y);
        y->c[LEFT] = to_delete->c[LEFT];
        y->c[LEFT]->parent = y;
        y->color = to_delete->color;
    }
    if (y_orig_color == BLACK){
        delete_fixup_rbt(tree, x);
    }
    free(to_delete);
}

rbt_node* successor_rbt(rbt* tree, rbt_node* start){
    if(start->c[RIGHT] != tree->nil){
        return min_rbt(tree, start->c[RIGHT]);
    }
    rbt_node* par = start->parent;
    while (par != tree->nil && start == par->c[RIGHT]){
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
    if (!header->color){
        printf("\x1B[31m");
    }
    printf("%d",header->value);
    printf("\x1B[0m"); 
    if(header->c[LEFT] != tree->nil){
        printf("  ");
        print_tree(tree, header->c[LEFT], depth + 1);
    }
    if (header->c[RIGHT] != tree->nil){
        printf("\n");
        for (int i = 0; i<=depth; i++){
            printf("   ");
        }
        print_tree(tree, header->c[RIGHT], depth + 1);
    }
    if(header->parent == tree->nil){
        printf("\n");
    }
}
