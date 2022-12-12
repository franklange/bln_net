project(bln_net_udp_example)

find_package(GTest REQUIRED)
include(GoogleTest)

# Client
set(ECHO_CLI_TARGET echo_client)

add_executable(${ECHO_CLI_TARGET}
    client/echo_client.cpp
    client/client.cpp
)

set_target_properties(${ECHO_CLI_TARGET} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/example"
)

target_link_libraries(${ECHO_CLI_TARGET} PRIVATE
    bln_net
)

# Server
set(ECHO_SRV_TARGET echo_server)
add_executable(${ECHO_SRV_TARGET}
    server/echo_server.cpp
    server/server.cpp
)

set_target_properties(${ECHO_SRV_TARGET} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/example"
)

target_link_libraries(${ECHO_SRV_TARGET} PRIVATE
    bln_net
)

# Tests
set(ECHO_TESTS echo_tests)

add_executable(${ECHO_TESTS} "")

set_target_properties(${ECHO_TESTS} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/example"
)

target_sources(${ECHO_TESTS} PRIVATE
    client/client_TEST.cpp
    client/client.hpp client/client.cpp

    server/server_TEST.cpp
    server/server.hpp server/server.cpp
)

target_link_libraries(${ECHO_TESTS} PRIVATE
    bln_net
    GTest::gmock_main
)

gtest_discover_tests(${ECHO_TESTS})
