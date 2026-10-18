#pragma once
#include <string>
#include <vector>
#include <tuple>
#include <cstdint>

//объявление функций
std::vector<std::string> split(const std::string &str, char d);

consteval std::tuple<int, int, int, int> generation_ip(std::uint32_t value)
{
    for (int i = 0; i < 10000; i++)
    {
        value ^= value << 13;
        value ^= value >> 17;
        value *= 0x45D9F3Bu;
        value ^= value >> 16;
    }
    std::tuple<int, int, int, int> result{
        static_cast<int>((value >> 24) & 255), static_cast<int>((value >> 16) & 255),
        static_cast<int>((value >> 8) & 255), static_cast<int>(value & 255)};
    return result;
}