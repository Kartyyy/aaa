#pragma once

template <typename T>
bool Exist<T>::operator()(const T& value)
{
    return !seen_.insert(value).second;
}
