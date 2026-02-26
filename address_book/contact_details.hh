#pragma once

#include <iostream>
#include <stdexcept>
#include <string>

struct ContactDetails
{
public:
    static ContactDetails makeDetails(const std::string& telephone_number,
                                      const std::string& personal_email);

    const std::string& get_number() const;
    const std::string& get_email() const;

    friend std::ostream& operator<<(std::ostream& os, const ContactDetails& d);

private:
    ContactDetails(const std::string& telephone_number,
                   const std::string& personal_email);

    std::string number_;
    std::string email_;
};
