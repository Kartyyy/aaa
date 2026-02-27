#pragma once
#include "bimap.hh"
template <typename Lhs, typename Rhs>
bool Bimap<Lhs, Rhs>::insert(const Lhs& vl, const Rhs& vr)
{
    if (lhs_.contains(vl) || rhs_.contains(vr))
        return false;

    lhs_.emplace(vl, vr);
    rhs_.emplace(vr, vl);
    return true;
}

template <typename Lhs, typename Rhs>
bool Bimap<Lhs, Rhs>::insert(const Rhs& vr, const Lhs& vl)
{
    return insert(vl, vr);
}

template <typename Lhs, typename Rhs>
std::size_t Bimap<Lhs, Rhs>::erase(const Lhs& vl)
{
    auto it = lhs_.find(vl);
    if (it == lhs_.end())
        return 0;

    rhs_.erase(it->second);
    lhs_.erase(it);
    return 1;
}

template <typename Lhs, typename Rhs>
std::size_t Bimap<Lhs, Rhs>::erase(const Rhs& vr)
{
    auto it = rhs_.find(vr);
    if (it == rhs_.end())
        return 0;

    lhs_.erase(it->second);
    rhs_.erase(it);
    return 1;
}

template <typename Lhs, typename Rhs>
typename Bimap<Lhs, Rhs>::iteratorLhs
Bimap<Lhs, Rhs>::find(const Lhs& vl) const
{
    return lhs_.find(vl);
}

template <typename Lhs, typename Rhs>
typename Bimap<Lhs, Rhs>::iteratorRhs
Bimap<Lhs, Rhs>::find(const Rhs& vr) const
{
    return rhs_.find(vr);
}

template <typename Lhs, typename Rhs>
std::size_t Bimap<Lhs, Rhs>::size() const
{
    return lhs_.size();
}

template <typename Lhs, typename Rhs>
void Bimap<Lhs, Rhs>::clear()
{
    lhs_.clear();
    rhs_.clear();
}

template <typename Lhs, typename Rhs>
const typename Bimap<Lhs, Rhs>::mapLhs&
Bimap<Lhs, Rhs>::get_lhs() const
{
    return lhs_;
}

template <typename Lhs, typename Rhs>
const typename Bimap<Lhs, Rhs>::mapRhs&
Bimap<Lhs, Rhs>::get_rhs() const
{
    return rhs_;
}
