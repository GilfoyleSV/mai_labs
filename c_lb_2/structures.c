#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <stdbool.h>

list_dbl* list_create(){
    list_dbl* res = malloc(sizeof(list_dbl));
    if (res == NULL){
        return NULL;
    }
    res->first = NULL;
    res->last = NULL;
    res->lst_size = 0;
    return res;
}

void list_destroy(list_dbl* lst){
    if (lst == NULL){
        return;
    }

    elem* current = lst->first;
    while (current != NULL){
        elem* next = current->next;
        free(current);
        current = next;
    }
    free(lst);
}

int list_size(list_dbl* lst){
    return lst->lst_size;
}

bool list_is_empty(list_dbl* lst){
    return lst->first == NULL;
}

iter_lst iter_begin(list_dbl* lst){
    return (iter_lst){.lst = lst, .prev = NULL};
} 

iter_lst iter_end(list_dbl* lst){
    return (iter_lst){.lst=lst, .prev=lst->last};
}

iter_lst iter_next(iter_lst iter){
    if (iter.lst == NULL || iter.lst->first == NULL){
        return iter;
    }
    if (iter.prev == NULL){
        iter.prev = iter.lst->first;
    } else if (iter.prev->next != NULL){
        iter.prev = iter.prev->next;
    }
    return iter;
}

double iter_get(iter_lst iter){
    if (iter.lst == NULL || iter.lst->first == NULL){
        exit(EXIT_FAILURE);
    } 
    if (iter.prev == NULL){
        return iter.lst->first->val;
    } 
    if (iter.prev->next == NULL){
        exit(EXIT_FAILURE);
    }
    return iter.prev->next->val;
}

void iter_set(iter_lst iter, double value){
    if (iter.lst == NULL || iter.lst->first == NULL){
        exit(EXIT_FAILURE);
    } 
    if (iter.prev == NULL){
        iter.lst->first->val = value;
    } else if (iter.prev->next != NULL) {
        iter.prev->next->val = value;
    } else {
        printf("Warning: iterator out of bounds\n");
    }
}

iter_lst iter_insert(iter_lst iter, double value){
    elem* new_node = malloc(sizeof(elem));
    if (new_node == NULL){
        exit(EXIT_FAILURE);
    } 
    new_node->val = value;

    if (iter.prev == NULL){
        new_node->next = iter.lst->first;
        iter.lst->first = new_node;
        if (iter.lst->last == NULL){
            iter.lst->last = new_node;
        }
    } else {
        new_node->next = iter.prev->next;
        iter.prev->next = new_node;
        if (new_node->next == NULL){
            iter.lst->last = new_node;
        }
    }
    iter.lst->lst_size += 1;
    return iter;
}

void ldbl_iter_remove(iter_lst iter) {
    if (iter.lst == NULL || iter.lst->first == NULL) {
        printf("Warning: Attempted to remove from an empty list!\n");
        return;
    }

    if (iter.prev == NULL) {
        elem* e = iter.lst->first;
        if (e == NULL) return;
        iter.lst->first = e->next;
        if (iter.lst->first == NULL) {
            iter.lst->last = NULL;
        }
        free(e);
    } else {
        elem* e = iter.prev->next;
        if (e == NULL) {
            printf("Warning: Attempted to remove NULL element in ldbl_iter_remove!\n");
            return;
        }
        iter.prev->next = e->next;
        if (e->next == NULL) iter.lst->last = iter.prev;
        free(e);
    }
    iter.lst->lst_size -= 1;
}

bool iter_equal(iter_lst a, iter_lst b){
    return (a.lst == b.lst) && (a.prev == b.prev);
}

list_dbl* sorting(list_dbl* lst){
    list_dbl* sort_lst = list_create();
    iter_lst iter_unsort_lst = iter_begin(lst);
    iter_lst iter_sort_lst = iter_begin(sort_lst);
    while (!iter_equal(iter_unsort_lst, iter_end(lst))){
        double current_element = iter_get(iter_unsort_lst);
        while (!iter_equal(iter_sort_lst, iter_end(sort_lst))){
            if (current_element >= iter_get(iter_sort_lst)){
                iter_sort_lst = iter_next(iter_sort_lst);
            } else {
                break;
            }
        }
        iter_sort_lst = iter_insert(iter_sort_lst, current_element);
        iter_sort_lst = iter_begin(sort_lst);
        iter_unsort_lst = iter_next(iter_unsort_lst);
    }
    return sort_lst;
}

int main(){
    list_dbl* my_list = list_create();
    iter_lst it = iter_begin(my_list);
    double i;
    while (scanf("%lf", &i) == 1){
        it = iter_insert(it, i);
    }
    it = iter_begin(my_list);
    printf("-----------------------------\n");
    while (!iter_equal(it, iter_end(my_list))){
        printf("%lf\n", iter_get(it));
        it = iter_next(it);
    }
    list_dbl* sorting_lst = sorting(my_list);
    it = iter_begin(sorting_lst);
    printf("-----------------------------\n");
    while (!iter_equal(it, iter_end(sorting_lst))){
        printf("%lf\n", iter_get(it));
        it = iter_next(it);
    }
}
