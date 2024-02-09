#ifndef HUFFMAN_CALCULATOR_HPP
#define HUFFMAN_CALCULATOR_HPP

#include <tuple>
#include <vector>
#include <algorithm>

void insert(std::vector<std::pair<size_t, size_t>> &temp, const std::pair<size_t, size_t> &a)
{
  temp.push_back(a);
  if (temp.size() > 1)
  {
    for (size_t l = temp.size(); l > 0; l /= 2)
    {
      if (temp[l - 1] < temp[l / 2 - 1])
      {
        swap(temp[l - 1], temp[l / 2 - 1]);
      }
      else
      {
        break;
      }
    }
  }
}

void erase(std::vector<std::pair<size_t, size_t>> &temp)
{
  temp.front() = temp.back();
  temp.pop_back();
  size_t l = 1;
  while (l < temp.size() / 2 + 1)
  {
    if ((2 * l == temp.size()) && ((temp[temp.size() - 1] < temp[l - 1])))
    {
      swap(temp[l - 1], temp[temp.size() - 1]);
      break;
    }
    else if ((2 * l < temp.size()) && ((temp[2 * l - 1] < temp[l - 1]) || (temp[2 * l] < temp[l - 1])))
    {
      if ((temp[2 * l - 1] < temp[2 * l]))
      {
        swap(temp[l - 1], temp[2 * l - 1]);
        l *= 2;
      }
      else
      {
        swap(temp[l - 1], temp[2 * l]);
        l = 2 * l + 1;
      }
    }
    else
    {
      break;
    }
  }
}

size_t get_huffman_length(const std::vector<std::pair<size_t, size_t>> &data)
{
  // TODO: Implement this.
  size_t length = data.size();
  std::vector<std::pair<size_t, size_t>> temp(data);
  size_t answer(0);
  std::sort(temp.begin(), temp.end());
  while (length != 0)
  {
    if (temp[0].second > 1)
    {
      answer += temp[0].first * 2 * (temp[0].second / 2);
      std::pair<size_t, size_t> tem(temp[0].first * 2, temp[0].second / 2);
      insert(temp, tem);
      ++length;
      if (temp[0].second % 2 == 0)
      {
        erase(temp);
        --length;
      }
      else
      {
        temp[0].second = 1;
      }
    }
    else
    {
      if (length == 1)
      {
        if (answer == 0)
        {
          answer += temp[0].first;
        }
        break;
      }
      else
      {
        answer += temp[0].first;
        std::pair<size_t, size_t> tem(temp[0]);
        erase(temp);
        answer += temp[0].first;
        tem.first += temp[0].first;
        temp[0].second -= 1;
        insert(temp, tem);
        if (temp[0].second == 0)
        {
          erase(temp);
          --length;
        }
      }
    }
  }
  return answer;
}
#endif // HUFFMAN_CALCULATOR_HPP