#pragma once

#include <bln_net/local_packet.hpp>
#include <bln_net/types.hpp>

#include <cstdint>
#include <optional>

namespace bln_net::local {

struct socket
{
    using u16 = std::uint16_t;

    virtual ~socket() = default;

    virtual auto put(packet) -> u16 = 0;

    virtual auto get() -> std::optional<packet> = 0;

    virtual auto wait() -> packet = 0;
    virtual auto wait(const timeout&) -> std::optional<packet> = 0;
};

} // namespace bln_net::local
