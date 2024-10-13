#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>


void cleanup_handler(){
	printf("%s", "cleanup!\n");
	pthread_cleanup_push(cleanup_handler, NULL);	
	pthread_cleanup_pop(1);
}

void* mythread(void* arg) {
	pthread_cleanup_push(cleanup_handler, NULL);
	printf("%s", "mythread!");
	pthread_exit(0);
	pthread_cleanup_pop(1);
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

