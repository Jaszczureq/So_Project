#ifndef FUNCTIONS_H__
#define FUNCTIONS_H__
#include "includes.h"

typedef struct node * NODE;

void doSomething(struct node *, int );

int doTime();

int math(int, int);

void parser(struct node *, int );

void handler(int);

int checkNode(struct node *);

#endif