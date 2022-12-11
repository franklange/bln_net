project(bln_net_test)

find_package(GTest REQUIRED)
include(GoogleTest)

add_subdirectory(udp)
add_subdirectory(unix)