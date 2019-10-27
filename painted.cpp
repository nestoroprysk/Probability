#include <iostream>

int f(int n, char p)
{
    if (n == 1)
        return 1;
    if (p == 'w')
        return f(n - 1, 'b') + f(n - 1, 'w');
    else
        return f(n - 1, 'w');
}

int f(int n)
{
    return f(n, 'b') + f(n, 'w');
}

int main()
{
    for (auto i = 1; i < 15; ++i)
        std::cout << f(i) << std::endl;
}

