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
    temp->hour = h;
    temp->minutes = m;
    strcpy(temp->command, a);
    temp->info = i;
    temp->left = temp->right = NULL;
    return temp;
}
void inorder(struct node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        if(root->id==NULL){
            root->id=current_id;
            current_id++;
        }
        printf("%d, %d, %d, ", root->id, root->hour, root->minutes);
        printf("%s, ", root->command);
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

struct node *getNode(struct node *root, int id){
    if(root==NULL){
        return NULL;
    }
    struct node* cursor=root;
    while(cursor!=NULL){
        if(id<cursor->id)
            cursor=cursor->left;
        else if(id>cursor->id)
            cursor=cursor->right;
        else   
            return cursor;
    }
    return cursor;

}

int getId(struct node *node){return node->id;}
int getHour(struct node *node){return node->hour;}
int getMinutes(struct node *node){return node->minutes;}
char *getCommand(struct node *node){return node->command;}
int getInfo(struct node *node){return node->info;}
int getCurrent_id(){return current_id;}