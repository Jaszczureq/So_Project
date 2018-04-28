#ifndef BST_H__
#define BST_H__
#include "includes.h"

struct node *newNode(int, int, char *, int);

void inorder(struct node *);

void outprint(struct node *);

struct node *insert(struct node *, int, int, char *, int);

void *falsenode(struct node *, int, int, char *, int);

void empty(struct node *);

struct node *getNode(struct node *, int);

int getId(struct node *);
int getHour(struct node *);
int getMinutes(struct node *);
char *getCommand(struct node *);
int getInfo(struct node *);
int getFinished(struct node *);
void setFinished(struct node *);
void setRoot(struct node *);
int getCurrent_id();

#endif