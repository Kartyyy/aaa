#include "merge_sort.hh"

void merge_sort(iterator_type begin, iterator_type end)
{
    const auto n = end - begin;
    if (n <= 1)
        return;

    const auto mid = begin + n / 2;

    merge_sort(begin, mid);
    merge_sort(mid, end);

    std::vector<int> tmp;
    tmp.resize(static_cast<std::size_t>(n));

    std::merge(begin, mid, mid, end, tmp.begin());
    std::copy(tmp.begin(), tmp.end(), begin);
}
