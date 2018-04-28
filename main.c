#include "libs/bst.h"
#include "libs/read.h"
#include "libs/functions.h"

volatile int flag = 0;
volatile int flag1 = 0;
volatile int flag2 = 0;

struct node *root;
struct node *current;

void handler(int signum);
void handler1(int signum);
void handler2(int signum);

void isFinished();

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("Złe argumenty");
		exit(1);
	}

	openlog("mylog", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
	syslog(LOG_NOTICE, "Program started by User %d", getuid());
	closelog();

	int i;
	pid_t pid;

	root = NULL;
	root = insert(root, -1, -1, "root", -1);
	setRoot(root);

	pid = fork();
	printf("Current pid: %d\n", pid);

	if (pid)
	{
		printf("Demon initialized.\n");
	}
	else
	{
		int fp = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC);

		openlog("mylog", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);

		readmyfile(argv[1], root); // Data is in BST
		inorder(root);			   // Data's ids are sorted, ready to work on
		syslog(LOG_INFO, "File is read, data inside BST");

		doSomething(root, i);

		signal(SIGINT, handler);
		signal(SIGUSR1, handler1);
		signal(SIGUSR2, handler2);
		syslog(LOG_INFO, "Signals initialized");

		for (i = 1; i <= getCurrent_id(); i++)
		{
			printf("Current id is: %d\n", getCurrent_id());
			doSomething(root, i);
			int my_time = doTime();
			current = getNode(root, i);
			switch (getInfo(getNode(root, i)))
			{
			case 0:
				dup2(fp, 1);
				break;
			case 1:
				dup2(fp, 2);
				break;
			case 2:
				dup2(fp, 1);
				dup2(fp, 2);
				break;
			}

			if (my_time <= math(getHour(current), getMinutes(current)))
				if (checkNode(current) == 1)
				{
					// printf("Went to sleep for: %d\n",
					// 	   (math(getHour(current), getMinutes(current)) - my_time) * 60);
					sleep((math(getHour(current), getMinutes(current)) - my_time) * 60);

					printf("Status of flags: %d, %d, %d\n", flag, flag1, flag2);
					if (flag2 == 1)
					{
						flag2 = 0;
						syslog(LOG_INFO, "SIGUSR2 occurred");
						struct node *temp;
						int j;
						for (j = i; j <= getCurrent_id(); j++)
						{
							temp = getNode(root, j);
							if (getFinished(temp) == 0)
								syslog(LOG_INFO, "%d:%d:%s:%d", getHour(temp),
									   getMinutes(temp), getCommand(temp), getInfo(temp));
						}
						my_time = doTime();
						sleep((math(getHour(current), getMinutes(current)) - my_time) * 60);
					}
					if (flag1 == 1)
					{
						syslog(LOG_INFO, "SIGUSR! occurred");
						i = -2;
						printf("I value after SIGUSR1: %d\n", i);
					}
					if (flag == 1)
					{
						flag = 0;
						syslog(LOG_INFO, "Interrupt occurred");
						kill(pid, SIGKILL);
						break;
					}
					parser(root, i);
					printf("Return by null node succesful\n");
					doSomething(root, i);

					if (flag1 == 1)
					{
						printf("Inside second phase of SIGUSR1\n");
						flag1 = 0;
						empty(root);
						root = NULL;
						root = insert(root, -1, -1, "root", -1);
						setRoot(root);
						doSomething(root, i);
						readmyfile(argv[1], root); // Data is in BST
						inorder(root);			   // Data's ids are sorted, ready to work on
						syslog(LOG_INFO, "File is read, data inside BST");
						i=1;
					}
					doSomething(root, i);
					printf("Outside second phase os SIGUSR1\n");
				}

			//TODO optionally add pipes,
		}

		close(fp);
		sleep(3);
	}
	printf("Process has ended. Press Enter to continue.\n");

	openlog("mylog", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
	syslog(LOG_NOTICE, "Program ended with exit code: 0\n");
	closelog();

	return 0;
}

void handler(int signum)
{
	printf("Got the signal!\n");
	flag = 1;
}
void handler1(int signum)
{
	printf("Got the signal1!\n");
	printf("\n");
	flag1 = 1;
}
void handler2(int signum)
{
	printf("Got the signal2!\n");
	printf("\n");
	flag2 = 1;
}

void isFinished()
{
	int i;
	struct node *node;
	for (i = 0; i < getCurrent_id(); i++)
	{
		printf("Task number %d is ", i);
		node = getNode(root, i);
		if (getFinished(node) == 0)
			printf("unfinished, %d\n", getFinished(node));
		else if (getFinished(node) == 1)
			printf("finished, %d\n", getFinished(node));
		else
			printf("error\n");
	}
}