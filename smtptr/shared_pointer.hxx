#pragma once

#include <type_traits>
#include <utility>

template <typename T>
SharedPointer<T>::SharedPointer(element_type* p)
    : data_(p)
    , count_(nullptr)
{
    if (data_)
        count_ = new long(1);
}

template <typename T>
SharedPointer<T>::~SharedPointer()
{
    if (!data_)
        return;

    --(*count_);
    if (*count_ == 0)
    {
        delete data_;
        delete count_;
    }

    data_ = nullptr;
    count_ = nullptr;
}

template <typename T>
SharedPointer<T>::SharedPointer(const SharedPointer<element_type>& other)
    : data_(other.data_)
    , count_(other.count_)
{
    if (data_)
        ++(*count_);
}

template <typename T>
void SharedPointer<T>::reset(element_type* p)
{
    if (p == data_)
        return;

    if (data_)
    {
        --(*count_);
        if (*count_ == 0)
        {
            delete data_;
            delete count_;
        }
    }

    data_ = p;
    count_ = nullptr;
    if (data_)
        count_ = new long(1);
}

template <typename T>
SharedPointer<typename SharedPointer<T>::element_type>&
SharedPointer<T>::operator=(const SharedPointer<element_type>& other)
{
    if (this == &other)
        return *this;

    if (data_)
    {
        --(*count_);
        if (*count_ == 0)
        {
            delete data_;
            delete count_;
        }
    }

    data_ = other.data_;
    count_ = other.count_;

    if (data_)
        ++(*count_);

    return *this;
}

template <typename T>
typename SharedPointer<T>::element_type& SharedPointer<T>::operator*() const
{
    return *data_;
}

template <typename T>
typename SharedPointer<T>::element_type* SharedPointer<T>::operator->() const
{
    return data_;
}

template <typename T>
typename SharedPointer<T>::element_type* SharedPointer<T>::get() const
{
    return data_;
}

template <typename T>
long SharedPointer<T>::use_count() const
{
    return data_ ? *count_ : 0;
}

template <typename T>
template <typename U>
bool SharedPointer<T>::operator==(const SharedPointer<U>& rhs) const
{
    return static_cast<const void*>(data_) == static_cast<const void*>(rhs.get());
}

template <typename T>
template <typename U>
bool SharedPointer<T>::operator!=(const SharedPointer<U>& rhs) const
{
    return !(*this == rhs);
}

template <typename T>
bool SharedPointer<T>::operator==(const element_type* p) const
{
    return data_ == p;
}

template <typename T>
bool SharedPointer<T>::operator!=(const element_type* p) const
{
    return data_ != p;
}

template <typename T>
SharedPointer<typename SharedPointer<T>::element_type>&
SharedPointer<T>::operator=(SharedPointer&& other) noexcept
{
    if (this == &other)
        return *this;

    if (data_)
    {
        --(*count_);
        if (*count_ == 0)
        {
            delete data_;
            delete count_;
        }
    }

    data_ = other.data_;
    count_ = other.count_;

    other.data_ = nullptr;
    other.count_ = nullptr;

    return *this;
}

template <typename T>
SharedPointer<T>::SharedPointer(SharedPointer&& other)
    : data_(other.data_)
    , count_(other.count_)
{
    other.data_ = nullptr;
    other.count_ = nullptr;
}

template <typename T>
SharedPointer<T>::operator bool() const
{
    return data_ != nullptr;
}

template <typename T>
template <typename U>
bool SharedPointer<T>::is_a() const
{
    if (!data_)
        return false;

    if constexpr (std::is_same_v<U, element_type>)
        return true;
    else if constexpr (std::is_polymorphic_v<element_type>)
        return dynamic_cast<U*>(data_) != nullptr;
    else
        return false;
}
