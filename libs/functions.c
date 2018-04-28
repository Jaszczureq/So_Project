
#include "functions.h"
#include "bst.h"

void doSomething(struct node *root, int i)
{

	for (i = 1; i <= getCurrent_id(); i++)
	{
		struct node *current;
		current = getNode(root, i);
		if (current != NULL)
		{
			printf("%d, %d, %d, %s, %d\n", getId(current), getHour(current), getMinutes(current), getCommand(current), getInfo(current));
		}
		else
		{
			printf("Node number: %d is NULL\n", i);
		}
	}
}

int doTime()
{
	time_t now;
	struct tm ts;

	now = time(NULL);
	ts = *localtime(&now);
	int my_time = math(ts.tm_hour, ts.tm_min);

	return my_time;
}

int math(int h, int m)
{
	return h * 60 + m;
}

void parser(struct node *root, int i)
{
	struct node *current;
	current = getNode(root, i);
	if (current == NULL)
	{
		printf("Current node is null\n");
		return;
	}
	char *cmmd = getCommand(current);
	int len = strlen(getCommand(current));
	char a[len];
	int j, k = 1, l = 0;
	strcpy(a, cmmd);

	for (j = 0; j < len; j++)
	{
		if (a[j] == ' ')
			k++;
	}

	char *arr[k + 1];
	pid_t pid;

	char *pch;
	int tok_id = 0;
	pch = strtok(cmmd, " ");
	while (pch != NULL)
	{
		arr[tok_id] = pch;
		tok_id++;
		pch = strtok(NULL, " ");
	}
	arr[tok_id] = NULL;

	// printf("\nWykonywana komenda: ");
	// for (i = 0; i < sizeof(arr) / 8; i++)
	// {
	// 	printf("%s ", arr[i]);
	// }
	// printf("\n");

	for (i = 0; i < k; i++)
	{
		if ((int)arr[i][0] == 124)
		{
			l = i;
		}
	}
	setFinished(current);

	if (l != 0)
	{
		int p[2];
		if (pipe(p) == -1)
		{
			perror("Pipe Failed");
			exit(1);
		}

		char *temp1[l + 1];
		char *temp2[k - l];

		for (i = 0; i < k + 1; i++)
		{
			if (i < l)
				temp1[i] = arr[i];
			else if (i == l)
				temp1[i] = (char *)NULL;
			else if (i > l)
			{
				temp2[i - l - 1] = arr[i];
			}
		}
		for (i = 0; i < l + 1; i++)
		{
		}
		for (i = 0; i < k - l; i++)
		{
		}

		if (fork())
		{

			close(STDOUT_FILENO);
			dup(p[1]);
			close(p[0]);
			close(p[1]);

			execvp(temp1[0], temp1);
			kill(pid, SIGKILL);
		}
		if (fork())
		{

			close(STDIN_FILENO);
			dup(p[0]);
			close(p[1]);
			close(p[0]);

			execvp(temp2[0], temp2);
			kill(pid, SIGKILL);
		}
		close(p[0]);
		close(p[1]);
	}
	else
	{
		if (fork())
		{
			setFinished(current);
			if (k == 1)
			{
			}
			else
				execvp(arr[0], arr);
			kill(pid, SIGKILL);
		}
	}
}
int checkNode(struct node *root)
{
	openlog("mylog", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
	int sum = 0;
	if (getHour(root) >= 0 && getHour(root) < 24)
		sum++;
	if (getMinutes(root) >= 0 && getMinutes(root) < 60)
		sum++;
	if (getInfo(root) >= 0 && getInfo(root) < 3)
		sum++;
	if (sum == 3)
	{
		syslog(LOG_INFO, "Node data is correct");
		closelog();
		return 1; // Input correct
	}
	else
	{
		syslog(LOG_ERR, "Node data is incorrect");
		fprintf(stderr, "Node data is incorrect\n");
		closelog();
		return 0; // Input incorrect
	}
}