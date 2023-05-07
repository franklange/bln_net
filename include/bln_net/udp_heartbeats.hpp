#pragma once

#include <bln_net/types.hpp>
#include <bln_net/udp_endpoint.hpp>

#include <cstdint>
#include <vector>
#include <unordered_map>

namespace bln_net::udp {

class heartbeats
{
    using u8 = std::uint16_t;
    using beats = std::unordered_map<endpoint, u8>;

public:
    void add (const endpoint&);
    void beat(const endpoint&);
    void trim(const std::vector<endpoint>&);

    auto check() -> std::vector<endpoint>;

private:
    mutex m_mutex;
    beats m_heartbeats;
};

} // namespace bln_net
