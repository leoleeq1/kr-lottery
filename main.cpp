#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "lottery.hpp"

int main()
{
    std::vector<std::unique_ptr<ILottery>> lotteries;
    lotteries.emplace_back(std::make_unique<Lotto645>());
    lotteries.emplace_back(std::make_unique<AnnuityLottery720Plus>());

    int32_t selected{-1};

    while (true)
    {
        for (size_t i = 0; i < lotteries.size(); ++i)
        {
            std::cout << i << ". " << lotteries[i]->GetName() << "\n";
        }
        std::cin >> selected;

        if (selected < 0 || selected >= lotteries.size())
            return -1;

        std::cout << "\n"
                  << lotteries[selected]->Generate() << "\n";
    }

    return 0;
}