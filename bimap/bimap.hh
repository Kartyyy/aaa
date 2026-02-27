#pragma once

#include <map>

template <typename Lhs, typename Rhs>
class Bimap
{
    static_assert(!std::is_same_v<Lhs, Rhs>,
                  "Lhs and Rhs must be different types");
    using mapLhs = std::map<Lhs, Rhs>;
    using mapRhs = std::map<Rhs, Lhs>;
    using iteratorLhs = typename mapLhs::const_iterator;
    using iteratorRhs = typename mapRhs::const_iterator;

public:
    bool insert(const Lhs& vl, const Rhs& vr);
    bool insert(const Rhs& vr, const Lhs& vl);

    std::size_t erase(const Lhs& vl);
    std::size_t erase(const Rhs& vr);

    iteratorLhs find(const Lhs& vl) const;
    iteratorRhs find(const Rhs& vr) const;

    std::size_t size() const;
    void clear();

    const mapLhs& get_lhs() const;
    const mapRhs& get_rhs() const;

private:
    mapLhs lhs_;
    mapRhs rhs_;
};

#include "bimap.hxx"
