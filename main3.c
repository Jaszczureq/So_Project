
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

struct Params {
	int hour;
	int minutes;
	char command[64];
	int info;
};

int main (int argc, char* argv[]){

	struct Params param;
		
	char buffer[32];
	char word[64];		int j=0;
	char params[4];		int k=0;
	size_t offset=0;
	size_t bytes_read;
	
	if(argc!=3){
		printf("Złe argumenty\n");
		exit(1);
	}
	else{
		
		int i;
		int z; 
		
		int fd=open(argv[1], O_RDONLY);
		int fp=open(argv[2], O_WRONLY | O_CREAT);
		
		printf("word: %d, params: %d\n", sizeof(word), sizeof(params));
		
		do{
			i=0; j=0; k=0;
			bytes_read=read(fd,buffer,sizeof(buffer));
			for(i=0; i<bytes_read; i++){
				if(buffer[i]=='\n'){
					printf("\n");
					k=0;
				}
				else{
					//print
					if(buffer[i]!=':'){
						word[j]=buffer[i];
						j++;
					} else{
						char small[2];
						int num=0;
						switch(k){
							case 0:
								small[0]=word[0];
								small[1]=word[1];
								num=atoi(small);
								printf("Num= %d\n", num);
								break;
							case 1:
								small[0]=word[0];
								small[1]=word[1];
								num=atoi(small);
								printf("Num= %d\n", num);
								break;
							case 2:
								break;
							case 3:
								small[0]='0';
								small[1]=word[0];
								num=atoi(small);
								printf("Num= %d\n", num);
								break;
						}
						k++;
					}
				}
			for(z=0; z<sizeof (word); z++){
				printf("%c",word[z]); 
			}
			printf("\n");
			memset(word, 0, sizeof(word));
			}
		}while(bytes_read!=0);
		
		
		close(fd);
	}
}