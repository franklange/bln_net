project(bln_net_unix_test)

# Server
set(SRV_TARGET unix_server)
add_executable(${SRV_TARGET} server.cpp)

set_target_properties(${SRV_TARGET} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/tests"
)

target_link_libraries(${SRV_TARGET} PRIVATE bln_net)
target_compile_features(${SRV_TARGET} PUBLIC cxx_std_20)

# Client
set(CLI_TARGET unix_client)
add_executable(${CLI_TARGET} client.cpp)

set_target_properties(${CLI_TARGET} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/tests"
)

target_link_libraries(${CLI_TARGET} PRIVATE bln_net)
target_compile_features(${CLI_TARGET} PUBLIC cxx_std_20)
