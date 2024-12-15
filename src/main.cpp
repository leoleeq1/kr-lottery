#include <cstdint>
#include <format>
#include <fstream>
#include <filesystem>
#include <memory>
#include <string>
#include <vector>

#include "lottery.hpp"

int main(int argc, char **argv)
{
    std::string pathString = argc > 1 ? argv[1] : "result.md";
    std::filesystem::path filepath = pathString;
    std::filesystem::create_directories(filepath.parent_path());

    std::vector<std::unique_ptr<ILottery>> lotteries;
    lotteries.emplace_back(std::make_unique<Lotto645>());
    lotteries.emplace_back(std::make_unique<AnnuityLottery720Plus>());

    std::ofstream ofs;
    ofs.open(filepath, std::ofstream::out | std::ofstream::trunc);
    for (auto &&lottery : lotteries)
    {
        ofs << std::format("# {}\n", lottery->GetName());
        ofs << std::format("{}\n", lottery->Generate());
    }

    return 0;
}