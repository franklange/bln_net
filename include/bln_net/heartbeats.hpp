#pragma once

#include <bln_net/types.hpp>
#include <bln_net/udp_endpoint.hpp>

#include <cstdint>
#include <vector>
#include <unordered_map>

namespace bln_net {

template <typename E>
class heartbeats
{
    using count = std::uint16_t;
    using beats = std::unordered_map<E, count>;

public:
    void add (const E&);
    void beat(const E&);
    void trim(const std::vector<E>&);

    auto check() -> std::vector<E>;

private:
    mutex m_mutex;
    beats m_heartbeats;
};

template <typename E>
void heartbeats<E>::add(const E& e)
{
    const spinlock l{m_mutex};

    if (m_heartbeats.contains(e))
        return;

    m_heartbeats[e] = 3u;
}

template <typename E>
void heartbeats<E>::beat(const E& e)
{
    const spinlock l{m_mutex};

    if (!m_heartbeats.contains(e))
        return;

    auto& b = m_heartbeats[e];
    b = std::min(3u, (b + 1u));
}

template <typename E>
void heartbeats<E>::trim(const std::vector<E>& es)
{
    const spinlock l{m_mutex};

    for (const auto& e : es)
        m_heartbeats.erase(e);
}

template <typename E>
auto heartbeats<E>::check() -> std::vector<E>
{
    const spinlock l{m_mutex};

    std::vector<E> res;

    for (auto& [e, b] : m_heartbeats)
        if ((--b) == 0) res.push_back(e);

    return res;
}

} // namespace bln_net
