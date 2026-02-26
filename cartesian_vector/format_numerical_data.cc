#include "format_numerical_data.hh"

#include <ios>

std::ostream& FormatNumericalData::formatOs(std::ostream& os) const
{
    if (precision >= 0)
        os.precision(precision);

    if (scientific_notation)
        os << std::scientific;
    else
        os << std::defaultfloat;

    if (display_plus)
        os << std::showpos;
    else
        os << std::noshowpos;

    return os;
}
