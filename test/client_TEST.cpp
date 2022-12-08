#include "client.hpp"

#include <bln_net/udp_socket_MOCK.hpp>

#include <gtest/gtest.h>

namespace bln_net::udp::test {

struct client_test : public ::testing::Test
{
    socket_MOCK m_socket;
    client m_client{m_socket};
};

TEST_F(client_test, echo)
{
    EXPECT_CALL(m_socket, put_rv).Times(1);
    EXPECT_CALL(m_socket, wait()).Times(1);

    m_client.echo("hi");
}

} // namespace bln_net::udp::test
