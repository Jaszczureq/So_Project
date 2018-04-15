#include "bst.h"
#include "read.h"

struct node *root;

void pca(char *arr, int rozmiar)
{
	int i;
	printf("%s\n", arr);
}

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

	root = insert(root, 0, 0, argv[1], 1);

	inorder(root);

	readmyfile(params, root);

	inorder(root);
}
