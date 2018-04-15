#include "bst.h"
#include "read.h"

struct node *root;
struct node *current;

void doSomething();

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("Złe argumenty");
		exit(1);
	}
	char* params[]={argv[1],argv[2]};
    printf("%s, %s\n", params[0],params[1]);

	root = NULL;

	root = insert(root, -1, -1, "root", -1);

	inorder(root);

	readmyfile(params, root);

	inorder(root);


	int i;
	printf("\n");
	for(i=1; i<=getCurrent_id(); i++){
		current=getNode(root, i);
		if(current!=NULL){
			printf("%d, %d, %d, %s, %d\n", i, getHour(current), getMinutes(current)
			, getCommand(current), getInfo(current));
			
			doSomething(getHour(current), getMinutes(current)
			, getCommand(current), getInfo(current));
		}
	}
}

void doSomething(int hour, int minutes, char *command, int info){
	printf("%d, %d, %s, %d\n", hour, minutes, command, info);
}
