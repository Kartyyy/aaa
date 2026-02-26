#include "contact_details.hh"

static bool is_digits_only(const std::string& s)
{
    if (s.empty())
        return false;
    for (char c : s)
        if (c < '0' || c > '9')
            return false;
    return true;
}

static bool has_at_least_one_at(const std::string& s)
{
    for (char c : s)
        if (c == '@')
            return true;
    return false;
}

ContactDetails::ContactDetails(const std::string& telephone_number,
                               const std::string& personal_email)
  : number_{telephone_number}
  , email_{personal_email}
{
}

ContactDetails ContactDetails::makeDetails(const std::string& telephone_number,
                                          const std::string& personal_email)
{
    if (!is_digits_only(telephone_number) || !has_at_least_one_at(personal_email))
        throw std::invalid_argument("Invalid contact details");
    return ContactDetails{telephone_number, personal_email};
}

const std::string& ContactDetails::get_number() const
{
    return number_;
}

const std::string& ContactDetails::get_email() const
{
    return email_;
}

std::ostream& operator<<(std::ostream& os, const ContactDetails& d)
{
    os << d.number_ << ", " << d.email_ << '\n';
    return os;
}
