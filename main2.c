#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

int main (int argc, char* argv[]){
	char small[2]={'2','3'};
	int num= atoi(small);
	printf("Num: %d", num);
	
	
}