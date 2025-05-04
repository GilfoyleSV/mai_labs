#pragma once

typedef struct treeNode treeNode;

struct treeNode{
    float value;
    treeNode* left;
    treeNode* right;
};

typedef treeNode* tree;

typedef struct{
    int level;
    int position;
} NodePos;
