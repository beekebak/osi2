#include "selector_context.hpp"
#include <stdexcept>
#include <errno.h>
#include <string.h>
#include <unistd.h>

selector_context_t::selector_context_t(){
    ep_fd = epoll_create(EPOLL_SIZE);
    if (ep_fd == -1){
        perror("creating epoll");
        abort();
    }
    for(int i = 0; i < EPOLL_SIZE; i++){
        events[i].events = 0;
        events[i].data.fd = -1;
    }
}

selector_context_t::~selector_context_t(){
    close(ep_fd);
}

void selector_context_t::register_file_descriptor(int fd, uint32_t op) noexcept{
    struct epoll_event event;
    event.data.fd = fd;
    event.events = 0;
    if (op & READ){
       event.events |= EPOLLIN; 
    }
    if (op & WRITE){
        event.events |= EPOLLOUT;
    }
    epoll_ctl(ep_fd, EPOLL_CTL_ADD, fd, &event);
}

void selector_context_t::change_descriptor_mode(int fd, uint32_t op) noexcept{
    struct epoll_event event;
    event.data.fd = fd;
    event.events = 0;
    if (op & READ){
       event.events |= EPOLLIN; 
    }
    if (op & WRITE){
        event.events |= EPOLLOUT;
    }
    epoll_ctl(ep_fd, EPOLL_CTL_MOD, fd, &event);
}

void selector_context_t::unregister_file_descriptor(int fd) noexcept{
    epoll_ctl(ep_fd, EPOLL_CTL_DEL, fd, NULL);
}

int selector_context_t::do_select() noexcept{
    return epoll_wait(ep_fd, events, EPOLL_SIZE, -1);
}

void wait_context_t::notify() noexcept{
    selector_context->change_descriptor_mode(fd, WRITE);
}