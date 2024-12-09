#include "thread_pool.hpp"

void* thread_func(void* arg){
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    proxy_server_t* server = static_cast<proxy_server_t*>(arg);
    server->start_server_loop();
    std::cout << "thread finished " << pthread_self() << "\n";
    return NULL;
}


thread_pool_t::thread_pool_t(size_t num_threads): num_threads(num_threads), next(0), 
        thread_ids(new pthread_t[num_threads]), proxy_servers(new proxy_server_t[num_threads]) {    
    for (size_t i = 0; i < num_threads; ++i){
        int res = pthread_create(thread_ids + i, NULL, thread_func, proxy_servers + i);
        if (res != 0){
            errno = res;
            perror("init thread_poll");
            abort();
        }
    }
}

thread_pool_t::~thread_pool_t(){
    for (size_t i = 0; i < num_threads; ++i){
        pthread_cancel(thread_ids[i]);
        pthread_join(thread_ids[i], NULL);
    }
    delete [] thread_ids;
    delete [] proxy_servers;
}


void thread_pool_t::add_new_connection(int fd){
    proxy_servers[next].add_client_socket(fd);
    next = (next + 1) % num_threads;
}