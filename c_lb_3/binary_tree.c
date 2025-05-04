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

#define MAX_HEIGHT 1000
int left_profile[MAX_HEIGHT];
int right_profile[MAX_HEIGHT];

typedef struct {
    char** lines;
    int width;
    int height;
} TreeDrawing;

// Создаем пустое изображение
TreeDrawing* create_drawing(int width, int height) {
    TreeDrawing* td = malloc(sizeof(TreeDrawing));
    td->width = width;
    td->height = height;
    td->lines = malloc(height * sizeof(char*));
    for (int i = 0; i < height; i++) {
        td->lines[i] = malloc(width + 1);
        memset(td->lines[i], ' ', width);
        td->lines[i][width] = '\0';
    }
    return td;
}

// Освобождаем память
void free_drawing(TreeDrawing* td) {
    for (int i = 0; i < td->height; i++) {
        free(td->lines[i]);
    }
    free(td->lines);
    free(td);
}

// Рекурсивная функция для рисования дерева
void draw_tree_recursive(tree t, TreeDrawing* td, int x, int y) {
    if (tree_is_empty(t)) return;

    // Записываем значение узла
    char val[20];
    sprintf(val, "%.2f", tree_get_value(t));
    int len = strlen(val);
    for (int i = 0; i < len; i++) {
        td->lines[y][x + i] = val[i];
    }

    // Рисуем связи к детям
    if (!tree_is_empty(t->left)) {
        td->lines[y+1][x-1] = '/';
        draw_tree_recursive(t->left, td, x - 2, y + 2);
    }
    if (!tree_is_empty(t->right)) {
        td->lines[y+1][x+len] = '\\';
        draw_tree_recursive(t->right, td, x + len + 1, y + 2);
    }
}

// Основная функция для печати дерева
void print_tree(tree t) {
    if (tree_is_empty(t)) {
        printf("(empty tree)\n");
        return;
    }

    int depth = tree_depth(t, 0);
    int width = 1 << (depth + 1); // Ширина достаточная для дерева
    
    TreeDrawing* td = create_drawing(width, depth * 2 + 1);
    
    // Начинаем рисовать с корня вверху по центру
    int start_x = width / 2;
    draw_tree_recursive(t, td, start_x, 0);
    
    // Печатаем результат
    for (int i = 0; i < td->height; i++) {
        // Обрезаем лишние пробелы справа
        int end = td->width - 1;
        while (end >= 0 && td->lines[i][end] == ' ') end--;
        td->lines[i][end+1] = '\0';
        
        printf("%s\n", td->lines[i]);
    }
    
    free_drawing(td);
}

int main(){
    tree my_tree = tree_create_empty();
    my_tree = tree_add(my_tree, 25);
    my_tree = tree_add(my_tree, 14);
    my_tree = tree_add(my_tree, 35);
    my_tree = tree_add(my_tree, 16);
    my_tree = tree_add(my_tree, 33);

    print_tree(my_tree);
    tree_destroy_recursive(my_tree);
}
