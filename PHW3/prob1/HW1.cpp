#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

class DisjointSet
{
private:
    std::vector<long long> parent;

public:
    DisjointSet(long long max_size) : parent(std::vector<long long>(max_size))
    {
        for (long long i = 0; i < max_size; ++i)
            parent[i] = i;
    }
    long long find(long long x)
    {
        if (parent[x] == x)
            return x;
        else
        {
            parent[x] = find(parent[x]);
            return parent[x];
        }
    }
    void set_union(long long x1, long long x2)
    {
        long long f1 = find(x1);
        long long f2 = find(x2);
        if (f1 != f2)
        {
            parent[f2] = f1;
        }
    }
};

int main()
{
    long long m, n, from, to, weight, answer(0);
    std::cin >> m >> n;
    std::vector<std::vector<long long>> v;
    DisjointSet set(n + 1);
    for (int i = 0; i < m; ++i)
    {
        std::cin >> from >> to >> weight;
        v.push_back({weight, from - 1, to});
    }
    std::sort(v.begin(), v.end());
    for (int i = m - 1; i >= 0; --i)
    {
        if (set.find(v[i][1]) != set.find(v[i][2]))
        {
            set.set_union(v[i][2], v[i][1]);
            answer += v[i][0];
        }
    }
    std::cout << answer << std::endl;
}