#pragma once

#include <memory>
#include <string>

inline NFT create_empty_nft()
{
    return NFT{};
}

inline NFT create_nft(const std::string& name)
{
    return std::make_unique<std::string>(name);
}
