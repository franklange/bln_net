#include <bln_net/udp_heartbeats.hpp>

#include <algorithm>

namespace bln_net::udp {

void heartbeats::add(const endpoint& e)
{
    const spinlock l{m_mutex};

    if (m_heartbeats.contains(e))
        return;

    m_heartbeats[e] = 3u;
}

void heartbeats::beat(const endpoint& e)
{
    const spinlock l{m_mutex};

    if (!m_heartbeats.contains(e))
        return;

    auto& b = m_heartbeats[e];
    b = std::min(3u, (b + 1u));
}

void heartbeats::trim(const std::vector<endpoint>& es)
{
    const spinlock l{m_mutex};

    for (const auto& e : es)
        m_heartbeats.erase(e);
}

auto heartbeats::check() -> std::vector<endpoint>
{
    const spinlock l{m_mutex};

    std::vector<endpoint> res;

    for (auto& [e, b] : m_heartbeats)
        if ((--b) == 0) res.push_back(e);

    return res;
}

} // namespace bln_net::udp
