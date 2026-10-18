#include <gtest/gtest.h>

#include <algorithm>
#include <tuple>
#include <vector>

#include "../ip_utils.h"

//split 
TEST(Split, SplitsByDelimiter)
{
    EXPECT_EQ(split("", '.'), (std::vector<std::string>{""}));
    EXPECT_EQ(split("11.", '.'), (std::vector<std::string>{"11", ""}));
    EXPECT_EQ(split("11.22", '.'), (std::vector<std::string>{"11", "22"}));
}

//generation_ip считается при компиляции и всегда даёт один и тот же результат
TEST(Generation, ComputedAtCompileTime)
{
    constexpr std::tuple<int, int, int, int> a = generation_ip(267);
    EXPECT_EQ(a, generation_ip(267));
}

//сортировка кортежей
TEST(Sort, ReverseLexicographic)
{
    std::vector<std::tuple<int, int, int, int>> v{{1, 1, 1, 1}, {46, 70, 0, 1}, {1, 10, 0, 0}, {46, 2, 3, 4}};
    std::sort(v.begin(), v.end(), [](const auto &a, const auto &b) { return a > b; });
    const std::vector<std::tuple<int, int, int, int>> expected{{46, 70, 0, 1}, {46, 2, 3, 4}, {1, 10, 0, 0}, {1, 1, 1, 1}};
    EXPECT_EQ(v, expected);
}