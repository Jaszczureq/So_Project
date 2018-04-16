#include "bst.h"
#include "read.h"

struct node *root;
struct node *current;

void doSomething();
int doTime();
int math(int, int);
void handler(int);

int *main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("Złe argumenty");
		exit(1);
	}

	int i;
	char* params[]={argv[1], argv[2]};
	signal(SIGALRM, handler);

	root = NULL;
	root = insert(root, -1, -1, "root", -1);

	inorder(root);
	readmyfile(params, root);
	inorder(root);

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
	int my_time=doTime();
	printf("CurrentId: %d\n",getCurrent_id());

	for(i=1;i<=getCurrent_id(); i++){
		current=getNode(root, i);
		if(my_time>math(getHour(current), getMinutes(current)))
			printf("Command outdated\n");
		else
			printf("Command is about to be executed\n");
	}

	alarm(1);
	return 0;
}

void doSomething(int hour, int minutes, char *command, int info){
	printf("%d, %d, %s, %d\n", hour, minutes, command, info);
}

int doTime(){
	time_t now;
	struct tm ts;

 	now=time(NULL);

	ts=*localtime(&now);

	printf("%d:%d\n", ts.tm_hour, ts.tm_min);
	int my_time=math(ts.tm_hour, ts.tm_min);

	return my_time;
}

int math(int h, int m){
	return h*60+m;
}

void handler(int signal){
	//printf("Signal: %d, Cmd: %s", signal, cmd);
	printf("Signal arrived");
	alarm(1);

}
