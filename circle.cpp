#include <iostream>
#include <cmath>
#include <random>
#include <numeric>
#include <unordered_set>

int getDigit()
{
    static std::random_device dev;
    static std::mt19937 rng(dev());
    static std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 9);
    return dist6(rng);
}

int fImplA(const int n, const int at = 1)
{
    if (at == 1) {
        return 1 + fImplA(n, at + 1);
    }
    if (at == n) {
        return 0;
    }
    const auto left = getDigit() % 2 == 0;
    return 1 + fImplA(n, at + (left ? -1 : +1));
}

// 1 -> 2 -> 3 -> ... -> n -> 1
int fImplB(const int n, const int at, std::unordered_set<int>& s)
{
    s.emplace(at);
    if (s.size() == n) {
        return 0;
    }
    const auto left = getDigit() % 2 == 0;
    if (left) {
        // 1 -> n
        if (at == 1) {
            return 1 + fImplB(n, n, s);
        }
        return 1 + fImplB(n, at - 1, s);
    }
    else {
        // n -> 1
        if (at == n) {
            return 1 + fImplB(n, 1, s);
        }
        return 1 + fImplB(n, at + 1, s);
    }
}

double f(const int n)
{
    const auto nb_experiments = 100000;
    std::vector<int> v;
    for (auto i = 0; i < nb_experiments; ++i){
        std::unordered_set<int> s;
        v.emplace_back(fImplB(n, 1, s));
        // v.emplace_back(fImplA(n));
    }
    return std::accumulate(v.begin(), v.end(), double(0)) / nb_experiments; 
}

int main()
{
    const auto n = 11;
    std::cout << f(n) << std::endl;
}