#include "../slist.hpp"

#include <iostream>

std::ostream &operator<<(std::ostream &ostr, const Slist<int> &list)
{
  for (const int i : list)
    ostr << ' ' << i;
  return ostr;
}

int main()
{
  Slist<int> list1 = {3, 2, 1};
  Slist<int> list2 = {6, 4, 3};

  // list1.sort(std::greater<>{});
  // list2.sort();
  // std::cout << "list1: " << list1 << '\n';
  // std::cout << "list2: " << list2 << '\n';

  list1.merge(list2, std::greater<>{});
  std::cout << "merged:" << list1 << '\n';

  // list1.merge(list1); // This should do nothing.
  // std::cout << list1 << '\n';
}