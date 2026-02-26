#include "vector.hh"

#include "state_saver.hh"

FormatNumericalData Vector::format_numerical_data_{
    "[ ",
    " ]",
    12,
    true,  // scientific_notation
    true   // display_plus
};

Vector::Vector(double x, double y)
    : x_{x}
    , y_{y}
{
}

double Vector::get_x() const
{
    return x_;
}

double Vector::get_y() const
{
    return y_;
}

Vector& Vector::operator+=(const Vector& rhs)
{
    x_ += rhs.x_;
    y_ += rhs.y_;
    return *this;
}

Vector& Vector::operator-=(const Vector& rhs)
{
    x_ -= rhs.x_;
    y_ -= rhs.y_;
    return *this;
}

Vector& Vector::operator*=(double scalar)
{
    x_ *= scalar;
    y_ *= scalar;
    return *this;
}

Vector operator+(const Vector& lhs, const Vector& rhs)
{
    Vector res = lhs;
    res += rhs;
    return res;
}

Vector operator-(const Vector& lhs, const Vector& rhs)
{
    Vector res = lhs;
    res -= rhs;
    return res;
}

Vector operator*(const Vector& lhs, double scalar)
{
    Vector res = lhs;
    res *= scalar;
    return res;
}

Vector operator*(double scalar, const Vector& rhs)
{
    return rhs * scalar;
}

double operator*(const Vector& lhs, const Vector& rhs)
{
    return lhs.x_ * rhs.x_ + lhs.y_ * rhs.y_;
}

std::ostream& operator<<(std::ostream& os, const Vector& vec)
{
    StateSaver saver(os);
    Vector::format_numerical_data_.formatOs(os);

    os << Vector::format_numerical_data_.prefix
       << vec.x_ << " , " << vec.y_
       << Vector::format_numerical_data_.suffix;

    return os;
}
