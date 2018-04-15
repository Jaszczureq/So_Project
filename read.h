#ifndef READ_H__
#define READ_H__
#include "includes.h"

typedef struct node * NODE;

void readmyfile(char**, struct node * );
int getId();
int getHour();
int getMinuts();
char *getCommand();
int getInfo();

#endif