#pragma once

#include <concepts>
#include <iostream>
#include <vector>


template <typename T, typename U>
concept Mul = requires(const T a,const U b)
{
    { a * b } -> std::convertible_to<T>;
};

template <typename T>
concept Summable = requires(T a,const T b)
{
    { a += b } -> std::same_as<T&>;
};
template <typename T>
class MyVector
{
public:
    MyVector() = default;

    MyVector(const std::vector<T>& v)
        : vec_{ v }
    {}
    // Multiplies all the element of the array by the scalar and return a new
    // MyVector
    template <typename U>
        requires Mul<T, U>
    MyVector<T> operator*(const U& scalar) const
    {
	    std::vector<T> out;
    out.reserve(vec_.size());
    for (const auto& e : vec_)
        out.push_back(e * scalar);
    return MyVector<T>{ out };
    }

    // Multiplies all the element of the array by the scalar in place
    template <typename U>
        requires Mul<T, U>
    MyVector<T>& operator*=(const U& scalar)
    {
	    for (auto& e : vec_)
    {
        if constexpr (requires { e *= scalar; })
            e *= scalar;
        else
            e = e * scalar;
    }
    return *this;
    }

    // Sums all the element in the vector to the init value, and returns the
    // result
    T reduce(T init) const requires Summable<T>
    {
        for (const auto& e : vec_)
            init += e;
        return init;
    }
    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const MyVector<U>& vec);

private:
    std::vector<T> vec_;
};

#include "vector.hxx"
