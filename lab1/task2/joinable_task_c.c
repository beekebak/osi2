#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>


void* mythread(void* arg) {
	char* result = malloc(sizeof(char) * 13); 
	strcpy(result, "hello world");
	return result; 
}

int main() {
	pthread_t tid;
	int err;
	void* ret_value;

	err = pthread_create(&tid, NULL, mythread, NULL);
	if (err) {
    	printf("main: pthread_create() failed: %s\n", strerror(err));
		return -1;
	}
	pthread_join(tid, &ret_value);
	printf("%s\n", (char*)ret_value);
	free((char*)ret_value);
	return 0;
}
