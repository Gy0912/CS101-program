#ifndef CS10123F_PA2_BST
#define CS10123F_PA2_BST

#include <vector>
#include <iostream>

const double alpha(0.75);

class node
{
public:
    node *left, *right;
    long long size;
    long long value;
    long long sum;
    node(long long x) : left(nullptr), right(nullptr), size(1), value(x), sum(x) {}
    bool torebuild()
    {
        if (left != nullptr && right != nullptr)
        {
            return left->size > size * alpha || right->size > size * alpha;
        }
        else if (left == nullptr && right != nullptr)
        {
            return right->size > size * alpha;
        }
        else if (left != nullptr && right == nullptr)
        {
            return left->size > size * alpha;
        }
        else
        {
            return false;
        }
    }
};
node *N = new node(1);
std::vector<node *> newnode;

void inorder(std::vector<node *> &a, node *N)
{
    if (N == nullptr)
    {
        return;
    }
    inorder(a, N->left);
    a.push_back(N);
    inorder(a, N->right);
}

node *build(long long l, long long r, std::vector<node *> &s)
{
    if (l > r)
    {
        return nullptr;
    }
    long long mid = (l + r) / 2;
    s[mid]->size = r - l + 1;
    s[mid]->sum = s[mid]->value;
    s[mid]->left = build(l, mid - 1, s);
    if (s[mid]->left != nullptr)
    {
        s[mid]->sum += s[mid]->left->sum;
    }
    s[mid]->right = build(mid + 1, r, s);
    if (s[mid]->right != nullptr)
    {
        s[mid]->sum += s[mid]->right->sum;
    }
    return s[mid];
}

node *rebuild(node *N)
{
    std::vector<node *> a;
    inorder(a, N);
    long long length = a.size() - 1;
    N = build(0, length, a);
    return N;
}

void insert(long long &x)
{
    node *parent = N;
    node *n = N;
    if (N->size == 0)
    {
        N->left = nullptr;
        N->right = nullptr;
        N->size = 1;
        N->sum = x;
        N->value = x;
        return;
    }
    while (n != nullptr)
    {
        ++n->size;
        n->sum += x;
        if (n->value >= x)
        {
            parent = n;
            n = n->left;
        }
        else
        {
            parent = n;
            n = n->right;
        }
    }
    if (parent != nullptr)
    {
        if (parent->value >= x)
        {
            parent->left = new node(x);
            newnode.push_back(parent->left);
        }
        else
        {
            parent->right = new node(x);
            newnode.push_back(parent->right);
        }
    }
    if (N != nullptr)
    {
        node *root = N;
        node *p = nullptr;
        while (true)
        {
            if (root->torebuild())
            {
                bool lr(1);
                if (p != nullptr && p->left == root)
                {
                    lr = 1;
                }
                else if (p != nullptr && p->right == root)
                {
                    lr = 0;
                }
                root = rebuild(root);
                if (p == nullptr)
                {
                    N = root;
                }
                else
                {
                    if (lr)
                    {
                        p->left = root;
                    }
                    else
                    {
                        p->right = root;
                    }
                }
                break;
            }
            if (root->value >= x)
            {
                p = root;
                root = root->left;
            }
            else
            {
                p = root;
                root = root->right;
            }
            if (root == nullptr)
            {
                break;
            }
        }
    }
}

void erase(long long &x)
{
    node *n = N;
    node *parent = N;
    --n->size;
    n->sum -= x;
    while (n->value != x)
    {
        if (x > n->value)
        {
            parent = n;
            n = n->right;
        }
        else if (x < n->value)
        {
            parent = n;
            n = n->left;
        }
        --n->size;
        n->sum -= x;
    }
    if (n->left == nullptr && n->right == nullptr)
    {
        if (parent->left == n)
        {
            parent->left = nullptr;
            // newnode.push_back(n);
        }
        else if (parent->right == n)
        {
            // newnode.push_back(n);
            parent->right = nullptr;
        }
        else if (n == N)
        {
            N->size = 0;
        }
    }
    else if (n->left != nullptr && n->right != nullptr)
    {
        node *tmp = n;
        node *p = n;
        tmp = n->right;
        while (tmp->left != nullptr)
        {
            p = tmp;
            tmp = tmp->left;
        }
        n->value = tmp->value;
        n = n->right;
        while (n != tmp)
        {
            n->sum -= tmp->value;
            --n->size;
            n = n->left;
        }
        if (tmp->right == nullptr)
        {
            if (p->left == tmp)
            {
                p->left = nullptr;
            }
            else
            {
                p->right = nullptr;
            }
        }
        else
        {
            if (p->left == tmp)
            {
                p->left = tmp->right;
            }
            else
            {
                p->right = tmp->right;
            }
        }
    }
    else if (n->left == nullptr && n->right != nullptr)
    {
        if (parent->left == n)
        {
            parent->left = n->right;
        }
        else if (parent->right == n)
        {
            parent->right = n->right;
        }
    }
    else if (n->left != nullptr && n->right == nullptr)
    {
        if (parent->left == n)
        {
            parent->left = n->left;
        }
        else if (parent->right == n)
        {
            parent->right = n->left;
        }
    }
}

long long find(node *N, long long &x)
{
    if (N->size != 0)
    {
        if (N->value == x)
        {
            return 1;
        }
        else if (N->value < x)
        {
            if (N->right == nullptr)
            {
                return 0;
            }
            return find(N->right, x);
        }
        else
        {
            if (N->left == nullptr)
            {
                return 0;
            }
            return find(N->left, x);
        }
    }
    else
    {
        return 0;
    }
    return 0;
}

long long findkth(node *N, long long x)
{
    if (N->left != nullptr)
    {
        if (N->left->size == x - 1)
        {
            return N->value;
        }
        else if (N->left->size >= x)
        {
            return findkth(N->left, x);
        }
        else
        {
            return findkth(N->right, x - 1 - N->left->size);
        }
    }
    else
    {
        if (x == 1)
        {
            return N->value;
        }
        else
        {
            return findkth(N->right, x - 1);
        }
    }
}

long long minsum(node *N, long long &x)
{
    long long temp;
    if (N->right != nullptr)
    {
        temp = x * (N->sum - N->right->sum) - N->right->sum;
    }
    else
    {
        temp = x * N->sum;
    }
    long long ans = x * N->sum;
    while (true)
    {
        if (temp >= 0)
        {
            if (temp < ans)
            {
                ans = temp;
            }
            if (N->left != nullptr)
            {
                temp -= N->value * (x + 1);
                N = N->left;
                if (N->right != nullptr)
                {
                    temp -= N->right->sum * (x + 1);
                }
            }
            else
            {
                break;
            }
        }
        else
        {
            if (N->right != nullptr)
            {
                N = N->right;
                temp += N->value * (x + 1);
                if (N->left != nullptr)
                {
                    temp += N->left->sum * (x + 1);
                }
            }
            else
            {
                break;
            }
        }
    }
    return ans;
}

// you can do data structure initialization in this function
void init(std::size_t n [[maybe_unused]])
{
    N->size = 0;
    N->left = nullptr;
    N->right = nullptr;
    N->sum = 0;
    N->value = 0;
    newnode.push_back(N);
}

// You can deconstruct your data structure in this function
void clear()
{
    for (auto i : newnode)
    {
        delete i;
    }
}

// opt==1 insert x
// opt==2 erase x
// opt==3 query x
// opt==4 query xth
// opt==5 query x*sum(s1...st) - sum(s_t+1...s_m)
long long SetOperation(std::size_t opt, long long x)
{
    switch (opt)
    {
    case 1:
        insert(x);
        break;
    case 2:
        erase(x);
        break;
    case 3:
        return find(N, x);
        break;
    case 4:
        return findkth(N, x);
        break;
    case 5:
        return minsum(N, x);
        break;
    }
    return 0;
}

#endif // CS10123F_PA2_BST