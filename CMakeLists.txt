cmake_minimum_required(VERSION 3.10)
project(bln_net)

find_package(Threads REQUIRED)
add_subdirectory(third_party/bln_queue)

option(BLN_NET_TESTS "Enable BLN Net Tests" OFF)


add_compile_options(-Wall -Wextra -pedantic)

add_library(${PROJECT_NAME} "")

set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

target_sources(${PROJECT_NAME} PRIVATE
    include/bln_net/types.hpp
    include/bln_net/utils.hpp

    include/bln_net/local_endpoint.hpp
    include/bln_net/local_packet.hpp
    include/bln_net/local_socket.hpp
    include/bln_net/local_socket_asio.hpp

    include/bln_net/udp_endpoint.hpp
    include/bln_net/udp_heartbeats.hpp
    include/bln_net/udp_packet.hpp
    include/bln_net/udp_socket.hpp
    include/bln_net/udp_socket_asio.hpp
    include/bln_net/udp_socket_hb_srv.hpp
    include/bln_net/udp_socket_hb_cli.hpp

    src/utils.cpp
    src/local_packet.cpp
    src/local_socket_asio.cpp
    src/udp_endpoint.cpp
    src/udp_heartbeats.cpp
    src/udp_packet.cpp
    src/udp_socket_asio.cpp    
    src/udp_socket_hb_cli.cpp
    src/udp_socket_hb_srv.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

target_link_libraries(${PROJECT_NAME} PUBLIC
    bln_queue
    Threads::Threads
)

if (BLN_NET_TESTS)
    add_subdirectory(test)
endif()

if (BLN_NET_EXAMPLES)
    add_subdirectory(example)
endif()