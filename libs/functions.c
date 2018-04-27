#include "functions.h"
#include "bst.h"

void doSomething(struct node *root, int i)
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
    char *cmmd = getCommand(current);
    int len = strlen(getCommand(current));

    char a[len];
    int j, k = 1;
    char *arr[k + 1];
    strcpy(a, cmmd);
    pid_t pid;

    for (j = 0; j < len; j++)
    {
        if (a[j] == ' ')
            k++;
    }

    char *pch;
    int tok_id = 0;
    pch = strtok(cmmd, " ");
    while (pch != NULL)
    {
        //printf("token: %s\n", pch);
        arr[tok_id] = pch;
        tok_id++;
        pch = strtok(NULL, " ");
    }
    arr[tok_id] = NULL;

    int m;

    for (m = 0; m < 2; m++)
    {
        size_t leng = strlen(arr[m]);
        char *newBuf = (char *)malloc(len);
        memcpy(newBuf, arr[m], len);
    }

    printf("\nWykonywana komenda: ");
    for (i = 0; i < sizeof(arr) / 8; i++)
    {
        printf("%s ", arr[i]);
    }
    printf("\n");
    
    pid = fork();
    if (pid)
    {
        //printf("Parent parser process\n");
    }
    else
    {
        execvp(arr[0], arr);
        kill(pid, SIGKILL);
    }
    
    //execvp(arr[0], arr);
}

void handler(int signum)
{
    printf("\n");
    setFlag(1);
    //exit(signum);
}

int checkNode(struct node *root){
    int sum=0;
    if(getHour(root)>=0 && getHour(root)<24)
        sum++;
    if(getMinutes(root)>=0 && getMinutes(root)<60)
        sum++;
    if(getInfo(root)>=0 && getInfo(root)<3)
        sum++;
    if(sum==3)
        return 1; // Input correct
    else   
        return 0; // Input incorrect
}
