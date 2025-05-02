#ifndef _LIST_H_
#define _LIST_H_

typedef struct elem elem;

struct elem {
    double val;
    elem* next;
};


typedef struct {
    elem* first;
    elem* last;
    int lst_size;
} list_dbl;

typedef struct {
    list_dbl* lst;
    elem* prev;
} iter_lst;

#endif
