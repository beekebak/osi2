#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

int global = 0;

void *mythread(void *arg) {
	int local = 0;
	static int local_static = 0;
	const int local_const = 0;
	printf("mythread [%d %d %d %d]: Hello from mythread!\n", getpid(), getppid(), gettid(), pthread_self());
	global += 1;
	local += 1;
	printf("global %d, local %d\n", global, local);
	printf("global %d, local %d, local const %d, local static %d\n", &global, &local, &local_const, &local_static);
        return NULL;
}

int main() {
	pthread_t tid;
	int err;

	printf("main [%d %d %d]: Hello from main!\n", getpid(), getppid(), gettid());

        for(int i = 0; i < 5; i++) {
		err = pthread_create(&tid, NULL, mythread, NULL);
		if (err) {
	    	printf("main: pthread_create() failed: %s\n", strerror(err));
			return -1;
		} else {
		    	printf("main: pthread created with tid %d\n", tid);
		}
		pthread_detach(tid);
        }
	pthread_exit(NULL);
	return 0;
}

