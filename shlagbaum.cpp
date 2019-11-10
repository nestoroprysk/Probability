#include <iostream>
#include <cmath>
#include <random>
#include <numeric>
#include <vector>

int getDigit()
{
    static std::random_device dev;
    static std::mt19937 rng(dev());
    static std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 9);
    return dist6(rng);
}

int run(const int n, const double p)
{
    for (auto i = 0; i < n; ++i)
        if (getDigit() > 7)
            return i;
    return n;
}

double ev(const int n, const double p)
{
    const auto nb_trials = 1000000;
    std::vector<int> v;
    for (auto _ = 0; _ < nb_trials; ++_)
        v.emplace_back(run(n, p));
    return std::accumulate(v.begin(), v.end(), double(0.0)) / v.size(); 
}

int main()
{
    std::cout << ev(5, 0.8) << std::endl;
}