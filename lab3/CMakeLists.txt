PROJECT(http_proxy LANGUAGES CXX)
CMAKE_MINIMUM_REQUIRED (VERSION 3.12-3.18)
SET(CMAKE_CXX_FLAGS "-O3 -Wall -Werror -std=c++17")


add_compile_options(-Wall -Wextra -pedantic -Werror )
add_link_options(-lpthread)
ADD_EXECUTABLE(proxy main.cpp proxy_server.cpp selector_context.cpp storage.cpp thread_pool.cpp)