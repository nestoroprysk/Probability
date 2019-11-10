#include <iostream>
#include <cmath>
#include <random>
#include <numeric>

int getDigit()
{
    static std::random_device dev;
    static std::mt19937 rng(dev());
    static std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 9);
    return dist6(rng);
}

int fImpl()
{
    auto nb_girls = 0;
    while (true){
        const auto is_girl = getDigit() % 2 == 0;
        if (is_girl)
            ++nb_girls;
        else
            break;
    }
    return nb_girls;
}

double f(const int n)
{
    std::vector<int> v;
    for (auto i = 0; i < n; ++i)
        v.emplace_back(fImpl());
    return std::accumulate(v.begin(), v.end(), int(0)); 
}

int main()
{
    const auto n = 1000000;
    std::cout << f(n) / double(n) << std::endl;
}