project(bln_net_local_example)

# Client
set(CLIENT local_heartbeat_client)

add_executable(${CLIENT}
    client.cpp
)

set_target_properties(${CLIENT} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/example"
)

target_link_libraries(${CLIENT} PRIVATE
    bln_net
)

# Server
set(SERVER local_heartbeat_server)
add_executable(${SERVER}
    server.cpp
)

set_target_properties(${SERVER} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/example"
)

target_link_libraries(${SERVER} PRIVATE
    bln_net
)
