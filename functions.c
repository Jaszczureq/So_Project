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

    printf("%d:%d\n", ts.tm_hour, ts.tm_min);
    int my_time = math(ts.tm_hour, ts.tm_min);

    return my_time;
}

int math(int h, int m)
{
    return h * 60 + m;
}

void parse(struct node *root, int i)
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

    char *arr[k + 1];
    char b[len + 1];
    char *c;

    k = 0;
    for (j = 0; j < len; j++)
    {
        if (a[j] != ' ')
        {
            b[k] = a[j];
            k++;
        }
        else
        {
            b[k] = '\0';

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
    arr[l + 1] = NULL;

    memset(b, 0, len);
    for (j = 0; j < sizeof(arr) / 8; j++)
        printf("%d, %s\n", sizeof(arr) / 8, arr[j]);
    free(c);

    execvp(arr[0], arr);
}
