#include <iostream>
#include <cmath>
#include <random>
#include <numeric>

int getDigit()
{
    static std::random_device dev;
    static std::mt19937 rng(dev());
    static std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 10);
    return dist6(rng);
}

bool fImpl(int n)
{
    const auto withinTheRegion = getDigit() < 4; // 3 out of 10
    const auto shoot = withinTheRegion && getDigit() < 3; // 2 out of 10
    return shoot || (n > 1 && fImpl(n - 1));
}

double f(int n)
{
    std::vector<bool> v;
    const auto number_of_experiments = 100000;
    for (auto i = 0; i < number_of_experiments; ++i)
        v.emplace_back(fImpl(n));
    return std::accumulate(v.begin(), v.end(), double(0.0)) / v.size(); 
}

int main()
{
    std::cout << f(2) << std::endl;
    std::cout << f(10) << std::endl;
}
