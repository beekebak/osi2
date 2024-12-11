#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

void handle_sigint(int signum) {
    char* message = "Received signal";
    printf("%s %d\n", message, signum);
}

void* receive_sigint(void* arg) {
    sigset_t sigset;
    struct sigaction sa;

    sigfillset(&sigset);
    pthread_sigmask(SIG_BLOCK, &sigset, NULL);

    sigemptyset(&sigset);
    sigaddset(&sigset, SIGINT);
    pthread_sigmask(SIG_UNBLOCK, &sigset, NULL);

    sa.sa_handler = handle_sigint;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);

    pause();
}

void* receive_sigquit(void* arg) {
    sigset_t sigset;
    int sig;
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGQUIT);

    sigwait(&sigset, &sig);
    printf("%s %d\n", "sigwaited", sig);
}

int main() {
    pthread_t thread1, thread2, thread3;
    printf("mypid: %d\n", getpid());
    sigset_t sigset;

    sigfillset(&sigset);
    pthread_sigmask(SIG_BLOCK, &sigset, NULL);

    pthread_create(&thread2, NULL, receive_sigint, NULL);
    pthread_create(&thread3, NULL, receive_sigquit, NULL);

    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    return 0;
}
