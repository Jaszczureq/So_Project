#include "bst.h"

int current_id=0;

struct node
{
    int id;
    int hour;
    int minutes;
    char command[64];
    int info;
    struct node *left, *right;
};

struct node *newNode(int h, int m, char *a, int i)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->id=current_id;
    temp->hour = h;
    temp->minutes = m;
    //printf("String: %s", a);
    strcpy(temp->command, a);
    temp->info = i;
    temp->left = temp->right = NULL;
    current_id++;
    return temp;
}
void inorder(struct node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d, %d, %d, ", id, root->hour, root->minutes);
        printf("%s,", root->command);
        printf("%d\n", root->info);
        inorder(root->right);
    }
}

struct node *insert(struct node *node, int h, int m, char *a, int i)
{
    if (node == NULL)
        return newNode(h, m, a, i);
    int mytime = h * 60 + m;
    int temp = node->hour * 60 + node->minutes;
    if (mytime < temp)
        node->left = insert(node->left, h, m, a, i);
    else if (mytime >= temp)
        node->right = insert(node->right, h, m, a, i);

    return node;
}

int getId(){return id;}
int getHour(){return hour;}
int getMinuts(){return minutes;}
char *getCommand(){return command;}
int getInfo(){return info;}
