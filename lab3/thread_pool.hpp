#include <unistd.h>
#include <errno.h>
#include <iostream>
#include <vector>
#include "proxy_server.hpp"

class thread_pool_t{
  private:
    size_t num_threads;
    size_t next;
    std::vector<pthread_t*> thread_ids;
    std::vector<proxy_server_t*> proxy_servers;
  public:
    explicit thread_pool_t(size_t num_threads);    
    void add_new_connection(int fd);
    ~thread_pool_t();
};