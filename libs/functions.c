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
