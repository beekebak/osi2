#include <unistd.h>
#include <errno.h>
#include <iostream>
#include "proxy_server.hpp"


class thread_pool_t{
    size_t num_threads;
    size_t next;

    pthread_t* thread_ids;

    proxy_server_t* proxy_servers;




public:
    explicit thread_pool_t(size_t num_threads);    

    void add_new_connection(int fd);


    ~thread_pool_t();
};