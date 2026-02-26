#include "address_book.hh"

#include <iterator>


bool AddressBook::add(const std::string& full_name, const std::string& email,
                      const std::string& number)
{
    if (full_name.empty())
        return false;

    try
    {
        auto d = ContactDetails::makeDetails(number, email);
        book_.insert({full_name, d});
        return true;
    }
    catch (const std::invalid_argument&)
    {
        return false;
    }
}

std::vector<ContactDetails> AddressBook::find(const std::string& full_name)
{
    std::vector<ContactDetails> res;
    auto range = book_.equal_range(full_name);
    for (auto it = range.first; it != range.second; ++it)
        res.push_back(it->second);
    return res;
}

std::size_t AddressBook::count(const std::string& full_name)
{
    return book_.count(full_name);
}

bool AddressBook::remove(const std::string& full_name, std::size_t index)
{
    auto range = book_.equal_range(full_name);
    auto it = range.first;

    for (std::size_t i = 0; i < index && it != range.second; ++i)
        ++it;

    if (it == range.second)
        return false;

    book_.erase(it);
    return true;
}

void AddressBook::remove_all(const std::string& full_name)
{
    book_.erase(full_name);
}

std::ostream& operator<<(std::ostream& os, const AddressBook& b)
{
    os << b.book_.size() << " contact(s) in the address book." << '\n';
    for (const auto& kv : b.book_)
    {
        os << "- " << kv.first << ": " << kv.second.get_number() << ", "
           << kv.second.get_email() << '\n';
    }
    return os;
}

