#pragma once

#include <bln_net/udp_packet.hpp>

#include <cstdint>
#include <optional>

namespace bln_net::udp {

struct socket
{
    using u16 = std::uint16_t;

    virtual ~socket() = default;

    virtual auto put(packet) -> u16 = 0;

    virtual auto get() -> std::optional<packet> = 0;

    virtual auto wait() -> packet = 0;
    virtual auto wait(const timeout&) -> std::optional<packet> = 0;

    virtual auto port() const -> u16 = 0;
};

} // namespace bln_net::udp
