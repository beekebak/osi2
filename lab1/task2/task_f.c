#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>


void* mythread(void* arg) {
	printf("mythread [%d]: Hello from mythread!\n", gettid()); 
	return 0;
}

int main() {
	pthread_t tid;
	int err;
	void* ret_value;
	pthread_attr_t tattr;
	pthread_attr_init(&tattr);
	if (err) {
    	printf("main: pthread_init() failed: %s\n", strerror(err));
		return -1;
	}
	pthread_attr_setdetachstate(&tattr, PTHREAD_CREATE_DETACHED);
	if (err) {
    	printf("main: pthread_setdetachstate() failed: %s\n", strerror(err));
		return -1;
	}
	while(1) {
		err = pthread_create(&tid, &tattr, mythread, NULL);
		if (err) {
    		printf("main: pthread_create() failed: %s\n", strerror(err));
			return -1;
		}
	}
	return 0;
}
