#include "bst.h"
#include "read.h"
#include "functions.h"

struct list
{
	char *cmd;
	struct list *next;
};

struct node *root;
struct node *current;
struct list *head;
struct list *curent;

//void doSomething(int);
//int doTime();
//int math(int, int);
//void parse(int);

int *main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("Złe argumenty");
		exit(1);
	}

	int i;
	char *params[] = {argv[1], argv[2]};

	root = NULL;
	root = insert(root, -1, -1, "root", -1);

	readmyfile(params, root);
	inorder(root);

	printf("\n");
	for (i = 1; i <= getCurrent_id(); i++)
	{
		doSomething(root, i);
	}
	int my_time = doTime();
	printf("CurrentId: %d\n", getCurrent_id());

	for (i = 1; i <= getCurrent_id(); i++)
	{
		current = getNode(root, i);
		if (my_time > math(getHour(current), getMinutes(current)))
			printf("Command outdated\n");
		else
			printf("Command is about to be executed\n");
	}
	parse(root, 2);
	return 0;
}
