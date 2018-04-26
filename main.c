#include "libs/bst.h"
#include "libs/read.h"
#include "libs/functions.h"

struct node *root;
struct node *current;
/*
void doSomething(int);
int doTime();
int math(int, int);
void parser(int);
*/
int *main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Złe argumenty");
        exit(1);
    }

    int i;
    char *params[] = {argv[1], argv[2]};
    pid_t pid;

    root = NULL;
    root = insert(root, -1, -1, "root", -1);

    readmyfile(params, root);
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
    }
    else
    {
        printf("Demon starts workin'\n");
        for (i = 1; i <= getCurrent_id(); i++)
        {
            int my_time = doTime();
            current = getNode(root, i);
            if (my_time > math(getHour(current), getMinutes(current)))
                printf("Command outdated\n");
            else
            {
                printf("\nCommand is about to be executed\n");
                printf("Went to sleep for: %d\n",
                       (math(getHour(current), getMinutes(current)) - my_time) * 60);
                //sleep((math(getHour(current), getMinutes(current))-my_time)*60);
            }
        }
        
        sleep(10);
        parser(root, 4);
    }

    sleep(1);
    return 0;
}
/*
void doSomething(int i)
{
    struct node *current;
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

    //printf("%d:%d\n", ts.tm_hour, ts.tm_min);
    int my_time = math(ts.tm_hour, ts.tm_min);

    return my_time;
}

int math(int h, int m)
{
    return h * 60 + m;
}

void parser(int i)
{
    struct node *current;
    current = getNode(root, i);
    char *cmmd = getCommand(current);
    int len = strlen(getCommand(current));
    printf("command: %d, %s\n", len, cmmd);

    char a[len];
    int j, k = 1;
    char *arr[k + 1];
    strcpy(a, cmmd);

    for (j = 0; j < len; j++)
    {
        if (a[j] == ' ')
            k++;
    }
    printf("Number of elements: %d\n", k);

    char *pch;
    printf("Splitting string \"%s\" into tokens:\n", cmmd);

    int tok_id = 0;
    pch = strtok(cmmd, " ");
    while (pch != NULL)
    {
        printf("token: %s\n", pch);
        arr[tok_id] = pch;
        tok_id++;
        pch = strtok(NULL, " ");
    }
    arr[tok_id] = NULL;

    printf("Printowanie po elemencie v\n");
    printf("%s %s %s\n", arr[0], arr[1], arr[2]);

    int m, n;

    printf("Printowanie po elemencie v\n");
    printf("%s%s%s\n", arr[0], arr[1], arr[2]);

    for (m = 0; m < 2; m++)
    {
        for (n = 0; n <= strlen(arr[m]); n++)
        {
            printf("%d ", arr[m][n]);
        }
        printf("\n");
    }

    printf("Printowanie po elemencie v2\n");
    printf("%s%s%s\n", arr[0], arr[1], arr[2]);

    for (m = 0; m < 2; m++)
    {
        size_t leng = strlen(arr[m]);
        char *newBuf = (char *)malloc(len);
        memcpy(newBuf, arr[m], len);
    }

    for (m = 0; m < 2; m++)
    {
        for (n = 0; n <= strlen(arr[m]); n++)
        {
            printf("%d ", arr[m][n]);
        }
        printf("\n");
    }

    printf("Printowanie po elemenciev3\n");
    printf("%s%s%s\n", arr[0], arr[1], arr[2]);

    for (m = 0; m < 2; m++)
    {
        for (n = 0; n <= strlen(arr[m]); n++)
        {
            printf("%d ", arr[m][n]);
        }
        printf("\n");
    }

    for (j = 0; j < sizeof(arr) / 8; j++)
        printf("%d, %s\n", sizeof(arr) / 8, arr[j]);

    execvp(arr[0], arr);
}
*/