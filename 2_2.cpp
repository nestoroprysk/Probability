#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

static constexpr auto e = 0.000001;

int eq(double a, double b)
{
    return std::abs(a - b) < e ||
        std::abs(b - a) < e;
}

using Permutation = std::vector<int>;
using Predicate = std::function<bool(const Permutation&)>;

Permutation construct(int n)
{
    Permutation result;
    for (auto i = 0; i < n; ++i)
        result.push_back(i);
    return result;
}

double countSatisfactory(int n, Predicate p)
{
    if (n < 2)
        return 1;
    auto v = construct(n);
    auto satisfactory = 0;
    auto all = 0;
    do{
        if (p(v))
            ++satisfactory;
        ++all;
    }
    while (std::next_permutation(v.begin(), v.end()));
    return satisfactory * 1.0 / all;
}

double solve(int n)
{
    if (n < 2)
        return 1;
    return 1 / (n - 1.0);
}

const auto p = [](const Permutation& v){
    if (v.size() < 2)
        return false;
    const auto a = 0;
    const auto b = 1;
    const auto it = std::find(v.cbegin(), v.cend(), a);
    if (it == v.cend())
        throw std::logic_error("0 expected");
    if (it == v.cbegin()){
        return v[v.size() - 1] == b;
    }
    return *std::prev(it) == b;
};

using Test = std::function<int()>;

void check(Test a, Test b)
{
    const auto a_result = a();
    const auto b_result = b();
    if (a_result == b_result)
        std::cout << "[OK]" << std::endl;
    else{
        std::cout << "[ " << a_result << " != " << b_result << "]" << std::endl;
    }
}
int main()
{
    for (auto i = 2; i < 11; ++i)
        check([&]{return solve(i);}, [&]{return countSatisfactory(i, p);});
}
