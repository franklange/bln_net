#include <bln_net/udp_socket.hpp>

#include <gmock/gmock.h>

namespace bln_net::udp {

struct socket_MOCK : public socket
{
    using u16 = std::uint16_t;
    using u32 = std::uint32_t;

    auto put(packet&& p) -> u32 { return put_rv(p); }

    MOCK_METHOD(u32, put_rv, (packet));
    MOCK_METHOD(u32, put, (const packet&), (override));

    MOCK_METHOD(std::optional<packet>, get, (), (override));

    MOCK_METHOD(packet, wait, (), (override));
    MOCK_METHOD(std::optional<packet>, wait, (const timeout&), (override));

    MOCK_METHOD(u16, port, (), (const, override));
};

} // namespace bln_net::udp
