#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char x[6] = "gedit";
	char *p = &x[0];
	char *cmd = "ls";
	char *args[4];
	args[0] = x;
	args[1] = p;
	args[2] = &x;
	args[3] = &p;
	int i;
	printf("%lu\n", sizeof(args));
	for (i = 0; i < sizeof(args) / 8; i++)
	{
		printf("%s\n", args[i]);
	}

	char a[] = "hello";
	char *b = "world";
	p = &a[0];
	printf("%s, %s, %s\n", a, b, p);
}