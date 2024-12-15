#include <algorithm>
#include <array>
#include <cstdint>
#include <format>
#include <numeric>
#include <random>
#include <ranges>
#include <string>

class ILottery
{
public:
    virtual ~ILottery() = default;
    virtual std::string GetName() = 0;
    virtual std::string Generate() = 0;
};

class Lotto645 : public ILottery
{
public:
    Lotto645() = default;
    virtual ~Lotto645() = default;

    virtual std::string GetName() override { return name_; }
    virtual std::string Generate() override
    {
        std::string generated{};
        std::array<int32_t, 45> numbers;
        std::ranges::iota(numbers, 1);
        auto rng = std::default_random_engine{std::random_device{}()};

        for (size_t i = 0; i < gen_count_; ++i)
        {
            std::ranges::shuffle(numbers, rng);
            auto shuffled = numbers | std::views::take(kDraw_count);
            std::ranges::sort(shuffled);
            for (int32_t num : shuffled)
            {
                generated += std::format("{:2} ", num);
            }
            generated += '\n';
        }

        return generated;
    }

private:
    std::string name_{"Lotto 6/45"};
    int32_t gen_count_{5};
    const int32_t kDraw_count{6};
};

class AnnuityLottery720Plus : public ILottery
{
public:
    AnnuityLottery720Plus() = default;
    virtual ~AnnuityLottery720Plus() = default;

    virtual std::string GetName() override { return name_; }
    virtual std::string Generate() override
    {
        std::string generated{};
        auto rng = std::default_random_engine{std::random_device{}()};
        std::uniform_int_distribution dist(0, 9);

        for (size_t i = 0; i < kDraw_count; ++i)
        {
            generated += std::format("{} ", dist(rng));
        }
        generated += "\n";

        return generated;
    }

private:
    std::string name_{"Annuity Lottery 720+"};
    const int32_t kDraw_count{6};
};