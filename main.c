#include "bst.h"
#include "read.h"

struct list
{
	char *cmd;
	struct list *next;
};

struct node *root;
struct node *current;
struct list *head;
struct list *curent;

void doSomething();
int doTime();
int math(int, int);
void handler(int);
void parse(int);

int *main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("Złe argumenty");
		exit(1);
	}

	int i;
	char *params[] = {argv[1], argv[2]};
	signal(SIGALRM, handler);

	root = NULL;
	root = insert(root, -1, -1, "root", -1);

	readmyfile(params, root);
	inorder(root);

	printf("\n");
	for (i = 1; i <= getCurrent_id(); i++)
	{
		doSomething(i);
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
	parse(3);
	/*
	head = NULL;

	struct list *temp = head;
	while (temp != NULL)
	{
		printf("%s\n", temp->cmd);
		temp = temp->next;
	}
	*/
	return 0;
}

void doSomething(int i)
{
	current = getNode(root, i);
	if (current != NULL)
	{
		printf("%d, %d, %s, %d\n", getHour(current), getMinutes(current), getCommand(current), getInfo(current));
	}
}

int doTime()
{
	time_t now;
	struct tm ts;

	now = time(NULL);

	ts = *localtime(&now);

	printf("%d:%d\n", ts.tm_hour, ts.tm_min);
	int my_time = math(ts.tm_hour, ts.tm_min);

	return my_time;
}

int math(int h, int m)
{
	return h * 60 + m;
}

void handler(int signal)
{
	printf("Signal arrived");
	alarm(1);
}

void parse(int i)
{
	current = getNode(root, i);
	char *cmmd = getCommand(current);
	int len = strlen(getCommand(current));
	printf("%d, %s\n", len, cmmd);

	char a[len];
	strcpy(a, cmmd);

	int j, k = 1, l = 0;
	for (j = 0; j < len; j++)
	{
		if (a[j] == ' ')
			k++;
	}
	printf("Number of elements: %d\n", k);

	char *arr[k+1];
	char b[len + 1];
	char *c;

	k = 0;
	for (j = 0; j < len; j++)
	{
		if (a[j] != ' ')
		{
			b[k] = a[j];
			//printf("%c\n", b[k]);
			k++;
		}
		else
		{ /*
			b[k] = '\0';
			//arr[l] = b;
			printf("%d, test5, %s\n", l, b);
			c = malloc(sizeof(c) * (len + 1));
			c = &b[0];
			arr[l]=malloc(sizeof(arr[l])*(len+1));
			arr[l] = c;
			//strcpy(arr[l], b);
			printf("%s, %s\n", b, arr[l]);
			k = 0;
			l++;
			memset(b, 0, len);
			printf("test6\n");
			*/

			b[k] = '\0';

			c = malloc(sizeof(b));
			strcpy(c, b);
			arr[l] = c;

			printf("Aktualne l: %d, Zawartość b: %s, Zawartość c: %s, Zawartość arr: %s\n", l, b, c, arr[l]);

			k = 0;
			l++;
			memset(b, 0, len);
		}
	}
	b[k] = '\0';
	printf("test3\n");
	c = malloc(sizeof(b));
	strcpy(c, b);
	arr[l] = c;
	arr[l+1] = NULL;

	memset(b, 0, len);
	for (j = 0; j < sizeof(arr) / 8; j++)
		printf("%d, %s\n", sizeof(arr) / 8, arr[j]);
	free(c);

	execvp(arr[0], arr);
}
