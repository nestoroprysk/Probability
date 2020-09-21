#include <iostream>
#include <cmath>
#include <random>
#include <numeric>
#include <set>

// you live only for n days
// and you experience n worries during your lifetime
//
// what is the probability that you'll experience exectly 1 worry each day?
//
// permutations of worries / all possible worries per day distributions
//
// permutations of worries is fact(n)
//
// all possible worries per day distributions is n ^ n
// because each worry decides on which day to choose out of n days


int fact(const int i)
{
    if (i == 0)
    {
        return 1;
    }

    return i * fact(i - 1);
}

int main()
{
    auto n = 0;
    std::cout << "type n: ";
    std::cin >> n;
    if (n < 1)
    {
        std::cout << "n should be positive" << std::endl;
        return 1;
    }
    const auto number_of_experiments = 1000000;
    
    static std::random_device dev;
    static std::mt19937 rng(dev());
    static std::uniform_int_distribution<std::mt19937::result_type> dist6(0, n - 1);
    
    auto good = 0;
    for (auto i = 0; i < number_of_experiments; ++i)
    {
        std::set<int> s;
        for (auto j = 0; j < n; ++j)
        {
            s.emplace(dist6(rng));
        }
        
        if (s.size() == n)
        {
            ++good;
        }
    }

    std::cout << "experim: " << good / static_cast<double>(number_of_experiments) << std::endl;
    std::cout << "formula: " << fact(n) / std::pow(n, n) << std::endl;}
