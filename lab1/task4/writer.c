#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>


void* mythread(void* arg) {
        while(1){
		printf("hello world\n");
	}
}

int main() {
        pthread_t tid;
        int err;

        err = pthread_create(&tid, NULL, mythread, NULL);
        if (err) {
        printf("main: pthread_create() failed: %s\n", strerror(err));
                return -1;
        }
	pthread_cancel(tid);
        pthread_join(tid, NULL);
        return 0;
}

