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

bool findsInFirst()
{
    // 0 1 2 3 4 5 6 7 - finds
    // 8 9 - doesn't find
    return getDigit() < 8;
}

bool findsInSecond()
{
    // 0 1 2 3 4 5 6 7 - finds
    // 8 9 - doesn't find
    return getDigit() < 8;
}

bool fImpl(int m)
{
    // 0 1 2 3 - 0th region
    // 4 5 6 7 8 9 - 1st region
    const auto region_of_the_criminal = getDigit() > 3;
    if (region_of_the_criminal == 0){
        // m detectives sent to the 0th region
        for (auto i = 0; i < m; ++i)
            if (findsInFirst())
                return true;
    }
    else{
        // n (the rest of ten) to the 1st region
        const auto n = 10 - m;
        for (auto i = 0; i < n; ++i)
            if (findsInSecond())
                return true;
    }
    return false;
}

double f(int m)
{
    std::vector<bool> v;
    const auto number_of_experiments = 100000;
    for (auto i = 0; i < number_of_experiments; ++i)
        v.emplace_back(fImpl(m));
    return std::accumulate(v.begin(), v.end(), double(0.0)) / v.size(); 
}

int main()
{
    for (auto i = 0; i <= 10; ++i)
        std::cout << i << ". " << f(i) << std::endl;
}
