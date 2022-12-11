project(bln_net_udp_test)

set(ECHO_CLI_TARGET echo_client)
add_executable(${ECHO_CLI_TARGET} echo_client.cpp client.cpp)

set_target_properties(${ECHO_CLI_TARGET} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/tests"
)

target_link_libraries(${ECHO_CLI_TARGET} PRIVATE bln_net)


set(ECHO_SRV_TARGET echo_server)
add_executable(${ECHO_SRV_TARGET} echo_server.cpp server.cpp)

set_target_properties(${ECHO_SRV_TARGET} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/tests"
)

target_link_libraries(${ECHO_SRV_TARGET} PRIVATE
    bln_net
)


set(ECHO_TESTS echo_tests)
add_executable(${ECHO_TESTS} "")

set_target_properties(${ECHO_TESTS} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/tests"
)

target_sources(${ECHO_TESTS} PRIVATE
    client_TEST.cpp
    server_TEST.cpp
    client.hpp client.cpp
    server.hpp server.cpp
)

target_link_libraries(${ECHO_TESTS} PRIVATE
    bln_net
    GTest::gmock_main
)

gtest_discover_tests(${ECHO_TESTS})
