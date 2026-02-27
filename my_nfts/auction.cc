#include "auction.hh"

Auction::Auction(Person& organizer, NFT nft, uint initial_bid)
    : organizer_(organizer)
    , nft_(std::move(nft))
    , highest_bidder_(nullptr)
    , highest_bid_(initial_bid)
{
	if (!nft_)
        	throw 1;
}

Auction::~Auction()
{
    if (!nft_)
        return;

    if (highest_bidder_)
    {
        organizer_.add_money(highest_bid_);
        highest_bidder_->add_nft(std::move(nft_));
    }
    else
    {
        organizer_.add_nft(std::move(nft_));
    }
}

bool Auction::bid(Person& person, uint money)
{
	if (!nft_)
        return false;
    if (money <= highest_bid_)
        return false;

    if (highest_bidder_ == &person){
        int delta = money - highest_bid_;
    if (!person.remove_money(delta))
        return false;
    highest_bid_ = money;
    return true;}

    if (!person.remove_money(money))
    {
        return false;
    }

    if (highest_bidder_ && highest_bidder_ != &person)
        highest_bidder_->add_money(highest_bid_);

    highest_bidder_ = &person;
    highest_bid_ = money;
    return true;
}

const std::string& Auction::get_nft_name() const
{
    return *nft_;
}

uint Auction::get_highest_bid() const
{
    return highest_bid_;
}
