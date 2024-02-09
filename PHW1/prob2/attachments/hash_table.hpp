#ifndef CS10123F_PA1_HASHTABLE
#define CS10123F_PA1_HASHTABLE

#include <cstdint>
#include <cstdio>
#include <exception>
#include <iostream>
#include <string>
#include <vector>
#include "hash_types.hpp"

template <>
struct std::hash<Website>
{
  static const uint32_t base = 1009u; // 1009 is a prime number.
  uint32_t operator()(const Website &S) const noexcept
  {
    // ------------------------START YOUR CODE----------------
    uint32_t y = 0;
    for (auto c : S.name)
    {
      y = base * y + c;
    }
    return y;
    // 也可以 % 0xFFFFFFFF
    // ------------------------END OF YOUR CODE----------------
  }
};

template <class Key = Website, class T = IPv4> // template for key type class
                                               // Key and value type class T
class HashTable
{
private:
  enum entrystate
  {
    Unused,
    Used,
    Erased
  };
  const size_t Mod = 1000037u; // 1000037 is a prime number
  std::vector<T> Table;        // main table stores value
  std::vector<Key> Stored_Key; // used for storing original key
  std::vector<entrystate>
      State;                    // keeps the state of every table entry : {Unused, Used or Erased};
  std::vector<size_t> Used_pos; // hint: used for function clear()

public:
  static const std::size_t npos = -1;
  HashTable() : Table(Mod), Stored_Key(Mod), State(Mod, entrystate::Unused) {}

  const T &operator[](const Key &x) const
  {
    std::size_t pos = find(x);
    if (pos == npos)
      throw std::invalid_argument("Key does not exist");
    return Table[pos];
  }

  // ------------------------START YOUR CODE----------------

  std::size_t Search(const Key &x) const
  {
    std::size_t Start = std::hash<Key>{}(x) % Mod;
    std::size_t length = Table.size();
    std::size_t i = 0;
    while (State[Start] == entrystate::Used || State[Start] == entrystate::Erased)
    {
      if (Stored_Key[Start] == x)
      {
        return Start;
      }
      ++i;
      Start = (Start + i * i) % length;
    }
    i = 0;
    while (State[Start] == entrystate::Used || State[Start] == entrystate::Erased || State[Start] == entrystate::Unused)
    {
      if (State[Start] == entrystate::Erased || State[Start] == entrystate::Unused)
      {
        return Start;
      }
      ++i;
      Start = (Start + i * i) % length;
    }
    return 0;
  }

  std::size_t find(const Key &x) const
  {
    std::size_t Start = std::hash<Key>{}(x) % Mod;
    std::size_t length = Table.size();
    std::size_t i = 0;
    while (State[Start] == entrystate::Used || State[Start] == entrystate::Erased)
    {
      if (Stored_Key[Start] == x && State[Start] == entrystate::Used)
      {
        return Start;
      }
      ++i;
      Start = (Start + i * i) % length;
    }
    return npos;
  }

  void insert(const Key &x, const T &value)
  {
    std::size_t pos;
    pos = Search(x);
    Stored_Key[pos] = x;
    Table[pos] = value;
    State[pos] = entrystate::Used;
    Used_pos.push_back(pos);
  }

  bool erase(const Key &x)
  {
    std::size_t pos;
    pos = find(x);
    if (pos != npos)
    {
      State[pos] = entrystate::Erased;
      return 1;
    }
    return 0;
  }

  void clear()
  {
    for (std::size_t &temp : Used_pos)
    {
      State[temp] = entrystate::Unused;
    }
    Used_pos.clear();
  }
};

#endif // CS10123F_PA1_HASHTABLE