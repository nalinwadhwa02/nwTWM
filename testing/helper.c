#include <stdio.h>
#include <string.h>


char * spawn = "spawn";
char * window = "window";


char * [] split(char * p){
	char * ret [4];
	char * t = strtok(p, ":");
	int i=0;
	while(t!=NULL){
		ret[i++] = t;	
		t = strtok(NULL,":");
	}
	return ret;
}

