#pragma once

#include <ostream>
#include <string>

struct FormatNumericalData
{
    //! string to be printed before the data
    std::string prefix;
    //! string to be printed after the data
    std::string suffix;
    //! gives the minimum number of digits to appear (after the radix if
    //! scientific_notation is enabled)
    int precision = -1;
    //! define if scientific notation is enabled
    bool scientific_notation = false;
    //! define if a sign + should be placed before a number
    bool display_plus = false;

    //! format the given stream according to class attributes
    std::ostream& formatOs(std::ostream& os) const;
};
