#include <iostream>
#include <map>
#include <vector>
#include <pthread.h>
#include <memory>
#include "selector_context.hpp"

#ifndef STORAGE_H
#define STORAGE_H


class item_t{
  private:
    std::string data;
    bool started;
    bool completed;
    pthread_rwlock_t rw_lock;
    int pin_count;
    std::vector<wait_context_t> waiting_clients;
  public:
    explicit item_t();
    void pin();
    void un_pin(int fd); // removes fd from waiting_clients if fd > -1;
    int get_pin_count() const noexcept {return pin_count;}
    void put_data(const std::string& s) noexcept;

    /* return from 0 up to limit if download still in progres
        return -1 if offset == data.lenght && completed
    */
    int get_data(std::string& dst, size_t offset, size_t limit, const wait_context_t& wait_context) noexcept; 
    void set_completed(bool val) noexcept;
    bool is_compleated() const noexcept {return completed;}
    bool set_started(bool val) noexcept;
    bool is_started() const noexcept {return started;}
    ~item_t();
};


class storage_t{
  private:
    std::map<std::string, std::shared_ptr<item_t>> hash_map; // key format: <host><url>
    pthread_mutex_t lock;
  public:
    explicit storage_t();
    std::pair<std::string, std::shared_ptr<item_t>> get_item(const std::string& key) noexcept;
    bool try_remove_if_unused(std::pair<std::string, std::shared_ptr<item_t>>& pair); //return true on removal
    void remove_item(const std::string& key) noexcept;
    ~storage_t();
};

extern storage_t* storage;
void init_global_storage();

#endif