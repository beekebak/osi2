#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct {
	int val;
	char* str;
} Data;


void* mythread(void* arg) {
	Data* data = (Data*) arg;
	printf("%s, %d\n", data->str, data->val); 
	return 0;
}

int main() {
	pthread_t tid;
	int err;
	Data* data = malloc(sizeof(Data));
	data->val = 42;
	data->str = "hello";

	err = pthread_create(&tid, NULL, mythread, (void*) data);
	if (err) {
   	printf("main: pthread_create() failed: %s\n", strerror(err));
		return -1;
	}
	pthread_join(tid, NULL);
	free(data);
	return 0;
}
