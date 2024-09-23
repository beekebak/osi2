#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>


void* mythread(void* arg) {
	int* result = malloc(sizeof(int));
	*result = 42;
	return (void*)result; 
}

int main() {
	pthread_t tid;
	int err;
	int* ret_value;

	err = pthread_create(&tid, NULL, mythread, NULL);
	if (err) {
    	printf("main: pthread_create() failed: %s\n", strerror(err));
		return -1;
	}
	pthread_join(tid, (void**) &ret_value);
	printf("%d\n", *ret_value);
	free(ret_value);
	return 0;
}
