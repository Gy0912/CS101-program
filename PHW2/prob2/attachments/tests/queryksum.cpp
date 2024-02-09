#include "../bst.hpp"
#include <cassert>

int main()
{
    std::size_t n = 16;
    init(n);

    // for (int i = 1; i <= 500; ++i)
    // {
    //     SetOperation(1, 2);
    //     SetOperation(1, 3);
    //     SetOperation(1, 4);
    //     SetOperation(1, i);
    // }
    // for (int i = 1; i <= 500; i += 2)
    // {
    //     /* SetOperation(2, 3);
    //     SetOperation(2, 2); */
    //     SetOperation(2, i);
    // }
    // for (int i = 1; i <= 500; ++i)
    // {
    //     std::cout << SetOperation(3, 2) << " ";
    // }

    // SetOperation(1, 2);
    // SetOperation(1, 1);
    // SetOperation(1, 3);
    // SetOperation(1, 3);
    // SetOperation(1, 3);
    // SetOperation(1, 3);
    // SetOperation(1, 3);

    SetOperation(1, 1);
    SetOperation(1, 2);
    SetOperation(1, 5);
    SetOperation(1, 6);
    SetOperation(1, 3);
    SetOperation(1, 4);
    SetOperation(1, 7);

    assert(SetOperation(5, 1) == 2);
    assert(SetOperation(5, 2) == 2);
    assert(SetOperation(5, 3) == 12);
    assert(SetOperation(5, 4) == 2);

    SetOperation(2, 1);
    SetOperation(2, 5);
    assert(SetOperation(5, 1) == 8);
    assert(SetOperation(5, 2) == 5);
    assert(SetOperation(5, 10) == 0);
    printf("Accepted!");

    // long long answer;
    // answer = SetOperation(5, 2);
    // std::cout << answer;
}