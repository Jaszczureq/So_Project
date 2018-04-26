#include "libs/bst.h"
#include "libs/read.h"
#include "libs/functions.h"

struct node *root;
struct node *current;

volatile int flag = 0;

void setFlag(int x) { flag = 1; }

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Złe argumenty");
        exit(1);
    }

    int i;
    pid_t pid;

    signal(SIGINT, handler);

    root = NULL;
    root = insert(root, -1, -1, "root", -1);

    readmyfile(argv[1], root);
    inorder(root);

    printf("\n");
    for (i = 1; i <= getCurrent_id(); i++)
    {
        doSomething(root, i);
    }
    printf("CurrentId: %d\n", getCurrent_id());

    pid = fork();

    if (pid)
    {
        printf("Init demon\n");
        //waitpid(pid, NULL, 0);
    }
    else
    {
        int fp = open(argv[2], O_WRONLY | O_CREAT);

        //switch (0);

        dup2(fp, 2);

        printf("Demon starts workin'\n");
        for (i = 1; i <= getCurrent_id(); i++)
        {
            printf("Current i: %d, Current id: %d\n", i, getCurrent_id());
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
            if (my_time > math(getHour(current), getMinutes(current)))
                printf("Command outdated\n");
            else
            {
                printf("\nCommand is about to be executed\n");
                printf("Went to sleep for: %d\n",
                       (math(getHour(current), getMinutes(current)) - my_time) * 60);
                //sleep((math(getHour(current), getMinutes(current))-my_time)*60);
                sleep(2);
                if (flag == 1)
                {
                    kill(pid, SIGKILL);
                    exit(0);
                }
                parser(root, i);
            }
        }

        close(fp);
    }
    return 0;
}