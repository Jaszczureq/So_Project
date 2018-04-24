#include "libs/bst.h"
#include "libs/read.h"

struct node *root;
struct node *current;

void doSomething(int);
int doTime();
int math(int, int);
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
    pid_t pid;

    root = NULL;
    root = insert(root, -1, -1, "root", -1);

    readmyfile(params, root);
    inorder(root);

    printf("\n");
    for (i = 1; i <= getCurrent_id(); i++)
    {
        doSomething(i);
    }
    printf("CurrentId: %d\n", getCurrent_id());

    for (i = 1; i <= getCurrent_id(); i++)
    {
        int my_time = doTime();
        current = getNode(root, i);
        if (my_time > math(getHour(current), getMinutes(current)))
            printf("Command outdated\n");
        else
        {
            printf("Command is about to be executed\n");
            printf("Went to sleep for: %d\n", (math(getHour(current), getMinutes(current)) - my_time) * 60);
            pid = fork();
            if (pid == (pid_t)0)
            {
                parse(i);
                sleep(1);
            }
            else if (pid < (pid_t)0)
            {
                printf("Error, Fork failed.\n");
            }
            else
            {
                printf("Proces zakończony\n\n");
            }
            sleep(1);
            //sleep((math(getHour(current), getMinutes(current))-my_time)*60);
        }
    }
    //parse(1);
    return 0;
}

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

void parse(int i)
{
    struct node *current;
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
    char b[len-1];
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
        {
            //b[k] = '\0';

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
    arr[l + 1] = 0;

    printf("%s%s%s\n", arr[0], arr[1], arr[2]);
    int m, n;
    printf("Printowanie po elemencie\n");

    for (m = 0; m < 2; m++)
    {
        for (n = 0; n <= strlen(arr[m]); n++)
        {
            printf("%d ", arr[m][n]);
        }
        printf("\n");
    }

    arr[0] = "ls\0";
    arr[1] = "-l";
    arr[2] = 0;
    printf("%s%s%s\n", arr[0], arr[1], arr[2]);

    printf("Printowanie po elemencie v2\n");

    for (m = 0; m < 2; m++)
    {
        for (n = 0; n < strlen(arr[m]); n++)
        {
            printf("%d ", arr[m][n]);
        }
        printf("\n");
    }

    for (j = 0; j < sizeof(arr) / 8; j++)
        printf("%d, %s\n", sizeof(arr) / 8, arr[j]);
    memset(b, 0, len);
    free(c);
    execvp(arr[0], arr);
}
