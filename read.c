#include "read.h"
#include "bst.h"

struct node *root;

void readmyfile(char *input[], struct node *root)
{
    int fd = open(input[0], O_RDONLY);
    printf("File opened\n");
    int fp = open(input[1], O_WRONLY | O_CREAT);
    printf("Files opened\n");

    char buffer[1];
    char word[64];
    char num[2];
    int numer[3];
    int final_num;
    int i, j, k, z; //i for loop, j for small arr, k for large arr, z for switch
    size_t offset = 0;
    size_t bytes_read;
	j = 0;
	k = 0;
	z = 0;
    printf("Params initilized\n");

	//root = insert(root, 1, 1, "Hello", 1);

    do
    {
        i = 0;
        bytes_read = read(fd, buffer, sizeof(buffer));
        if (buffer[i] == '\n')
        {
            printf("");
        }
        else
        {
            switch (z)
            {
            case 0:
                if (buffer[i] != ':')
                {
                    num[j] = buffer[i];
                    j = 1;
                }
                else
                {
                    final_num = atoi(num);
                    numer[0] = final_num;
                    j = 0;
                    z = 1;
                }
                break;
            case 1:
                if (buffer[i] != ':')
                {
                    num[j] = buffer[i];
                    j = 1;
                }
                else
                {
                    final_num = atoi(num);
                    numer[1] = final_num;
                    j = 0;
                    z = 2;
                }
                break;
            case 2:
                if (buffer[i] != ':')
                {
                    word[k] = buffer[i];
                    k++;
                }
                else
                {
                    k = 0;
                    z = 3;
                }
                break;
            case 3:
                final_num = buffer[i] - '0';
                numer[2] = final_num;
                j = 0;
                z = 0;
                insert(root, numer[0], numer[1], word, numer[2]);

                memset(word, 0, sizeof(word));
                memset(numer, 0, sizeof(numer));
                break;
            }
        }
    } while (bytes_read > 0);
    close(fd);
    close(fp);
}