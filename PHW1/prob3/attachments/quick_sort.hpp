#include <iostream>
#include <vector>

auto random_choice(auto begin, auto end)
{
  // This is only a possible implementation of random_choice.
  // You can use this for your convenience or design a better one.
  std::size_t length = end - begin;
  std::size_t idx = std::rand() % length;
  return begin + idx;
}

void quick_sort(std::random_access_iterator auto begin,
                std::random_access_iterator auto end, auto compare)
{
  // TODO: IMPLEMENT THIS.
  if (begin == end - 1 || begin == end)
  {
    return;
  }
  else if (begin == end - 2)
  {
    if (compare(*(end - 1), *begin))
    {
      std::swap(*begin, *(end - 1));
    }
    return;
  }
  else
  {
    std::size_t count_b{0};
    std::size_t count_e{0};
    auto pivot = random_choice(begin, end);
    std::swap(*pivot, *(end - 1));
    while (begin < end - 2)
    {
      while (compare(*(begin), *(end + count_e - 1)) && begin != end - 1)
      {
        ++begin;
        ++count_b;
      }
      while (!compare(*(end - 2), *(end + count_e - 1)) && end - 2 > begin)
      {
        --end;
        ++count_e;
      }
      if (begin < end - 2)
      {
        std::swap(*(begin), *(end - 2));
      }
    }
    std::swap(*(begin), *(end + count_e - 1));
    quick_sort(begin - count_b, begin, compare);
    quick_sort(begin + 1, end + count_e, compare);
  }
}

void quick_sort(std::random_access_iterator auto begin,
                std::random_access_iterator auto end)
{
  quick_sort(begin, end, std::less<>{});
}
