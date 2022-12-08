#include "server.hpp"

#include <bln_net/udp_socket_MOCK.hpp>

#include <gtest/gtest.h>

namespace bln_net::udp::test {

struct server_test : public ::testing::Test
{
    bln_net::udp::socket_MOCK m_socket;
    server m_server{m_socket};
};

TEST_F(server_test, process)
{
    EXPECT_CALL(m_socket, wait()).Times(1);
    EXPECT_CALL(m_socket, put_rv).Times(1);

    m_server.process_request();
}

} // namespace bln_net::udp::test
