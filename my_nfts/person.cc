#include "person.hh"

#include <algorithm>

Person::Person(const std::string& name, uint money)
    : name_(name)
    , money_(money)
{}

std::vector<std::string> Person::enumerate_nfts() const
{
    std::vector<std::string> res;
    res.reserve(nfts_.size());
    for (const auto& nft : nfts_)
    {
        if (nft)
            res.push_back(*nft);
    }
    return res;
}

void Person::add_nft(NFT nft)
{
    if (nft)
        nfts_.push_back(std::move(nft));
}

NFT Person::remove_nft(const std::string& name)
{
    for (auto it = nfts_.begin(); it != nfts_.end(); ++it)
    {
        if (*it && **it == name)
        {
            NFT out = std::move(*it);
            nfts_.erase(it);
            return out;
        }
    }
    return create_empty_nft();
}

void Person::add_money(uint money)
{
    money_ += money;
}

bool Person::remove_money(uint money)
{
    if (money_ < money)
        return false;
    money_ -= money;
    return true;
}

uint Person::get_money() const
{
    return money_;
}

const std::string& Person::get_name() const
{
    return name_;
}

std::ostream& operator<<(std::ostream& os, const Person& p)
{
    os << "Name: " << p.get_name() << '\n';
    os << "Money: " << p.get_money() << '\n';
    os << "NFTs:";

    for (const auto& name : p.enumerate_nfts())
        os << ' ' << name;

    os << '\n';
    return os;
}
