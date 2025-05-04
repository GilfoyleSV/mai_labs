#include <stdio.h>
#include "binary_tree.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

tree tree_create_empty(){
    return NULL;
}

bool tree_is_empty(tree t){
    return t == NULL;
}

float tree_get_value(tree t){
    return t->value;
}

tree tree_get_left(tree t){
    return t->left;
}

tree tree_get_right(tree t){
    return t->right;
}

tree tree_build(float val, tree t_left, tree t_right){
    tree new_tree = malloc(sizeof(treeNode));
    if (new_tree == NULL){
        return NULL;
    }
    new_tree->value = val;
    new_tree->left = t_left;
    new_tree->right = t_right;
    return new_tree;
}

void tree_destroy(tree t){
    if (!tree_is_empty(t)){
        free(t);
    }
}

void tree_destroy_recursive(tree t){
    if (tree_is_empty(t)){
        return;
    }
    tree_destroy_recursive(t->left);
    tree_destroy_recursive(t->right);

    tree_destroy(t);
}

tree tree_add(tree t, float value){
    if (tree_is_empty(t)){
        return tree_build(value, tree_create_empty(), tree_create_empty());
    }

    if (value < tree_get_value(t)){
        tree left_tree = tree_add(t->left, value);
        tree new_tree = tree_build(tree_get_value(t), left_tree, t->right);
        tree_destroy(t);
        return new_tree;
    } else if (value > tree_get_value(t)) {
        tree right_tree = tree_add(t->right, value);
        tree new_tree = tree_build(tree_get_value(t), t->left, right_tree);
        tree_destroy(t);
        return new_tree;

    }
    return t;
}

tree tree_remove_node(tree t, float val) {
    if (tree_is_empty(t)){
        return t;
    }
    if (val < tree_get_value(t)) {
        tree left = tree_remove_node(tree_get_left(t), val);
        tree res = tree_build(tree_get_value(t), left, tree_get_right(t));
        
        tree_destroy(t);
        
        return res;
    } else if (val > tree_get_value(t)) {
        tree right = tree_remove_node(tree_get_right(t), val);
        tree res = tree_build(tree_get_value(t), tree_get_left(t), right);
        
        tree_destroy(t);
        
        return res;
    }    
    if (tree_is_empty(tree_get_left(t))) {
        tree res = tree_get_right(t);
        tree_destroy(t);
        
        return res;
    } else if (tree_is_empty(tree_get_right(t))) {
        tree res = tree_get_left(t);
        tree_is_empty(t);
        
        return res;
    }
    
    tree max_left_tree = tree_get_left(t);

    while (!tree_is_empty(tree_get_right(max_left_tree)))
        max_left_tree = tree_get_right(max_left_tree);
    
    double max_left_value = tree_get_value(max_left_tree);
    
    tree left = tree_remove_node(tree_get_left(t), max_left_value);
    tree res = tree_build(max_left_value, left, tree_get_right(t));
    
    tree_destroy(t);

    return res;
}

int tree_depth(tree t, int depth) {
    if (tree_is_empty(t)) {
        return depth;
    }
    int res1 = tree_depth(t->left, depth + 1);
    int res2 = tree_depth(t->right, depth + 1);
    return (res1 >= res2) ? res1 : res2;
}

int tree_width(tree t, int width){
    if (width == 0){
        if (t != NULL){
            return 1;
        }
        return 0;
    }

    return tree_width(t->left, width - 1) + tree_width(t->right, width - 1);
}

void tree_print_indent(tree t, int depth) {
    if (tree_is_empty(t)) {
        return;
    }

    // Печатаем отступы
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }

    // Печатаем значение узла
    printf("%.2f\n", t->value);

    tree_print_indent(t->left, depth + 1);
    tree_print_indent(t->right, depth + 1);
}

int main(){
    tree my_tree = tree_create_empty();
    my_tree = tree_add(my_tree, 25);
    my_tree = tree_add(my_tree, 14);
    my_tree = tree_add(my_tree, 35);
    my_tree = tree_add(my_tree, 16);
    my_tree = tree_add(my_tree, 33);
    my_tree = tree_add(my_tree, 345);
    my_tree = tree_add(my_tree, 23);
    my_tree = tree_add(my_tree, 1);

    tree_print_indent(my_tree, 0);
    tree_destroy_recursive(my_tree);
}
