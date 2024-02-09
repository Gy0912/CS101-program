#include <iostream>
#include <vector>
#include <algorithm>

class Buyer
{
private:
    long long price;
    int item;
    int number;

public:
    Buyer(long long v, int c, int n) : price(v), item(c), number(n) {}

    long long getprice() { return price; }

    int getitem() { return item; }

    int getnumber() { return number; }
};

int main()
{
    int m, n, c;
    long long v;
    std::cin >> n >> m;
    std::vector<Buyer> participants;
    for (int i = 0; i != n; ++i)
    {
        std::cin >> v >> c;
        Buyer tem(v, c, i + 1);
        participants.push_back(tem);
    }
    std::vector<std::vector<long long>> value(n + 1, std::vector<long long>(m + 1));
    std::vector<std::vector<long long>> revalue(n + 1, std::vector<long long>(m + 1));
    std::vector<std::vector<int>> pastpart(n + 1, std::vector<int>(m + 1));
    std::vector<Buyer> buyers;

    for (int i = 0; i != m + 1; ++i)
    {
        value[0][i] = 0;
    }
    for (int i = 1; i != n + 1; ++i)
    {
        for (int j = m; j != -1; --j)
        {
            value[i][j] = value[i - 1][j];
            if (participants[i - 1].getitem() <= j && value[i - 1][j - participants[i - 1].getitem()] + participants[i - 1].getprice() > value[i - 1][j])
            {
                value[i][j] = value[i - 1][j - participants[i - 1].getitem()] + participants[i - 1].getprice();
            }
        }
    }

    for (int i = 0; i != m + 1; ++i)
    {
        revalue[n][i] = 0;
    }
    for (int i = n; i != 0; --i)
    {
        for (int j = m; j != -1; --j)
        {
            revalue[i - 1][j] = revalue[i][j];
            pastpart[i - 1][j] = j;
            if (participants[i - 1].getitem() <= j && revalue[i][j - participants[i - 1].getitem()] + participants[i - 1].getprice() >= revalue[i][j])
            {
                revalue[i - 1][j] = revalue[i][j - participants[i - 1].getitem()] + participants[i - 1].getprice();
                pastpart[i - 1][j] = j - participants[i - 1].getitem();
            }
        }
    }

    for (int i = 1, j = m; i != n + 1; ++i)
    {
        if (pastpart[i - 1][j] != j)
        {
            buyers.push_back(participants[i - 1]);
            std::cout << participants[i - 1].getnumber() << ' ';
        }
        j = pastpart[i - 1][j];
    }
    std::cout << std::endl;

    for (std::size_t i = 0; i != buyers.size(); ++i)
    {
        long long price_i{0};
        for (int j = 0; j != m + 1; ++j)
        {
            if (value[buyers[i].getnumber() - 1][j] + revalue[buyers[i].getnumber()][m - j] > price_i)
                price_i = value[buyers[i].getnumber() - 1][j] + revalue[buyers[i].getnumber()][m - j];
        }
        std::cout << buyers[i].getprice() + price_i - value[n][m] << ' ';
    }
    std::cout << std::endl;
}