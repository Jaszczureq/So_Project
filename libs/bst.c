
#include "bst.h"

int current_id = -1;

struct node
{
  int id;
  int hour;
  int minutes;
  char command[64];
  int info;
  int finished;
  int root;
  struct node *left, *right;
};

struct node *newNode(int h, int m, char *a, int i)
{
  struct node *temp = (struct node *)malloc(sizeof(struct node));
  temp->id = 0;
  temp->hour = h;
  temp->minutes = m;
  memset(temp->command, 0, 64);
  strcpy(temp->command, a);
  temp->info = i;
  temp->left = NULL;
  temp->right = NULL;
  temp->finished = 0;
  temp->root = 0;
  return temp;
}
void inorder(struct node *root)
{
  if (root != NULL)
  {
    inorder(root->left);
    if (root->id == 0)
    {
      current_id++;
      if (root->root == 1)
      {
      }
      else
      {
        root->id = current_id;
      }
    }
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

void empty(struct node *node)
{
  current_id = -1;
  struct node *left = node->left;
  struct node *right = node->right;
  free(node);
  if (left)
    empty(left);
  if (right)
    empty(right);
}

struct node *getNode(struct node *root, int id)
{
  if (root == NULL)
  {
    return NULL;
  }
  struct node *cursor = root;
  while (cursor != NULL)
  {
    if (id < cursor->id)
      cursor = cursor->left;
    else if (id > cursor->id)
      cursor = cursor->right;
    else
      return cursor;
  }
  return cursor;
}

int getId(struct node *node)
{
  return node->id;
}
int getHour(struct node *node)
{
  return node->hour;
}
int getMinutes(struct node *node)
{
  return node->minutes;
}
char *getCommand(struct node *node)
{
  return node->command;
}
int getInfo(struct node *node)
{
  return node->info;
}
int getFinished(struct node *node)
{
  return node->finished;
}
void setFinished(struct node *node)
{
  node->finished = 1;
}
int getCurrent_id()
{
  return current_id;
}