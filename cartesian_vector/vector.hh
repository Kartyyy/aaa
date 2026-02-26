#pragma once
#include <iostream>

#include "format_numerical_data.hh"

class Vector
{
public:
    Vector() = default;
    Vector(double x, double y);
    double get_x() const;
    double get_y() const;

    Vector& operator+=(const Vector& rhs);
    Vector& operator-=(const Vector& rhs);
    Vector& operator*=(double scalar);

    friend Vector operator+(const Vector& lhs, const Vector& rhs);
    friend Vector operator-(const Vector& lhs, const Vector& rhs);
    friend Vector operator*(const Vector& lhs, double scalar);
    friend Vector operator*(double scalar, const Vector& rhs);
    friend double operator*(const Vector& lhs, const Vector& rhs);
    friend std::ostream& operator<<(std::ostream& os, const Vector& vec);

private:
    double x_ = 0;
    double y_ = 0;
    static FormatNumericalData format_numerical_data_;
};
