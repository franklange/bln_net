#include <bln_net/local_socket.hpp>

#include <gmock/gmock.h>

namespace bln_net::local {

struct socket_MOCK : public socket
{
    using u16 = std::uint16_t;

    MOCK_METHOD(u16, put, (packet), (override));
    
    MOCK_METHOD(std::optional<packet>, get, (), (override));

    MOCK_METHOD(packet, wait, (), (override));
    MOCK_METHOD(std::optional<packet>, wait, (const timeout&), (override));
};

} // namespace bln_net::udp
