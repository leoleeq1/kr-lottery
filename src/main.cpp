#include <chrono>
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
    if (filepath.has_parent_path())
    {
        std::filesystem::create_directories(filepath.parent_path());
    }

    std::vector<std::unique_ptr<ILottery>> lotteries;
    lotteries.emplace_back(std::make_unique<Lotto645>());
    lotteries.emplace_back(std::make_unique<AnnuityLottery720Plus>());

    std::ofstream ofs;
    ofs.open(filepath, std::ofstream::out | std::ofstream::trunc);
    {
        // const std::chrono::year_month_day ymd{std::chrono::floor<std::chrono::days>(std::chrono::system_clock::now())};
        // ofs << std::format("---\ntitle: Weekly Numbuers{}\n---\n\n", ymd);
        ofs << "---\ntitle: Weekly Numbers {{ date | date('dddd, MMMM YYYY - Wo') }}\n---\n\n";
    }

    for (auto &&lottery : lotteries)
    {
        ofs << std::format("# {}\n", lottery->GetName());
        ofs << std::format("{}\n", lottery->Generate());
    }

    return 0;
}