#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>


void* mythread(void* arg) {
	return (void*)42; 
}

int main() {
	pthread_t tid;
	int err;
	int ret_value;

	err = pthread_create(&tid, NULL, mythread, NULL);
	if (err) {
    	printf("main: pthread_create() failed: %s\n", strerror(err));
		return -1;
	}
	pthread_join(tid, (void**) &ret_value);
	printf("%d\n", ret_value);
	return 0;
}
