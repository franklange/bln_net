project(bln_net_hb_example)

# Client
set(HB_CLI_TARGET hb_client)

add_executable(${HB_CLI_TARGET}
    client.cpp
)

set_target_properties(${HB_CLI_TARGET} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/example"
)

target_link_libraries(${HB_CLI_TARGET} PRIVATE
    bln_net
)

# Server
set(HB_SRV_TARGET hb_server)
add_executable(${HB_SRV_TARGET}
    server.cpp
)

set_target_properties(${HB_SRV_TARGET} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/example"
)

target_link_libraries(${HB_SRV_TARGET} PRIVATE
    bln_net
)
