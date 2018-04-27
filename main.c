
#include "libs/bst.h"
#include "libs/read.h"
#include "libs/functions.h"

volatile int flag = 0;
volatile int flag1 = 0;
volatile int flag2 = 0;

struct node * root;
struct node * current;

void handler(int signum);
void handler1(int signum);
void handler2(int signum);

void isFinished();

int main(int argc, char * argv[]) {
  if (argc != 3) {
    printf("Złe argumenty");
    exit(1);
  }

  int i;
  pid_t pid;

  for (i = 0; i < 5; i++) {
    if (i == 2)
      break;
    printf("Liczba: %d\n", i);
  }
  printf("\n");

  root = NULL;
  root = insert(root, -1, -1, "root", -1);
  //isFinished();

  printf("\n");
  for (i = 1; i <= getCurrent_id(); i++) {
    doSomething(root, i);
  }
  //printf("CurrentId: %d\n", getCurrent_id());

  pid = fork();

  if (pid) {
    printf("Demon initialized.\n");
    //waitpid(pid, NULL, 0);
  } else {
    int fp = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC);

    openlog("mylog", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);

    readmyfile(argv[1], root); // Data is in BST
    inorder(root); // Data's ids are sorted, ready to work on

    signal(SIGINT, handler);
    signal(SIGUSR1, handler1);
    signal(SIGUSR2, handler2);

    //switch (0);

    //dup2(fp, 2);

    //printf("Demon starts workin'\n");
    for (i = 1; i <= getCurrent_id(); i++) {
      //printf("Current i: %d, Current id: %d\n", i, getCurrent_id());
      int my_time = doTime();
      current = getNode(root, i);
      switch (getInfo(getNode(root, i))) {
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
      if (my_time > math(getHour(current), getMinutes(current)))
        printf("Command outdated\n");
      else {
        if (checkNode(current) == 1) {
          printf("\nCommand is about to be executed\n");
          printf("Went to sleep for: %d\n",
            (math(getHour(current), getMinutes(current)) - my_time) * 60);
          //sleep((math(getHour(current), getMinutes(current))-my_time)*60);
          sleep(100);
          printf("Status of flag: %d\n", flag);
          if (flag == 1) {
            kill(pid, SIGKILL);
            break;
            //exit(0);
          }
          printf("Test\n");
          parser(root, i);
        }

        //TODO clean up code, handle sigusr1,sigusr2, optionally add pipes, 
        //sigusr1 zrobic z goto
      }
    }
    //isFinished();
    close(fp);
  }
  printf("Process has ended. Press Enter to continue.\n");
  return 0;
}

void handler(int signum) {
  printf("Got the signal!\n");
  flag = 1;
  //exit(signum);
}
void handler1(int signum) {
  printf("Got the signal1!\n");
  printf("\n");
  flag1 = 1;
}
void handler2(int signum) {
  printf("Got the signal2!\n");
  printf("\n");
  flag2 = 1;
}

void isFinished() {
  int i;
  struct node * node;
  for (i = 0; i < getCurrent_id(); i++) {
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