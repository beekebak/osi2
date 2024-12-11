#include <stdio.h>
#include <stddef.h>
#include <sys/epoll.h>
#include <pthread.h>

#ifndef SELECTOR_CONTEXT_H
#define SELECTOR_CONTEXT_H
#define EPOLL_SIZE 1024
#define READ EPOLLIN
#define WRITE EPOLLOUT

class selector_context_t{
  private:
    int ep_fd;
    struct epoll_event events[EPOLL_SIZE];
    void update() noexcept;
  public:
    explicit selector_context_t();
    void register_file_descriptor(int fd, uint32_t op) noexcept;
    void change_descriptor_mode(int fd, uint32_t op) noexcept;
    void unregister_file_descriptor(int fd) noexcept;
    int do_select() noexcept;
    inline struct epoll_event& operator[](size_t i) {
        return events[i];
    };
    ~selector_context_t();
};

class wait_context_t{
  private:
    int fd;  
    selector_context_t* selector_context;
  public:
    wait_context_t(int fd, selector_context_t* sel_con): fd(fd), selector_context(sel_con) {} 
    int get_fd() const noexcept { return fd;}
    selector_context_t* get_sel_con() const noexcept { return selector_context;}
    void notify() noexcept;   
};

#endif