#ifndef BST_H__
#define BST_H__
#include "includes.h"

struct node *newNode(int, int, char *, int);

void inorder(struct node *);

void outprint(struct node *);

struct node *insert(struct node *, int, int, char *, int);

#endif