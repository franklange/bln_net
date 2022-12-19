#pragma once

#include <bln_net/local_packet.hpp>
#include <bln_net/types.hpp>

#include <cstdint>
#include <optional>

namespace bln_net::local {

struct socket
{
    using u32 = std::uint32_t;

    virtual ~socket() = default;

    virtual auto put(packet&&) -> u32 = 0;
    virtual auto put(const packet&) -> u32 = 0;

    virtual auto get() -> std::optional<packet> = 0;

    virtual auto wait() -> packet = 0;
    virtual auto wait(const timeout&) -> std::optional<packet> = 0;
    virtual auto measured_wait(const timeout&) -> std::optional<packet> = 0;

    virtual auto last_wait() const -> duration = 0;
};

} // namespace bln_net::local
