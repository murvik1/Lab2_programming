#include "ip_utils.h"
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdint>

#include <fstream>
#include <tuple>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]



int main(int argc, char const *argv[])
{
    try
    {

        //лямбда для вывода ip
        auto print_ip = [](const auto& ip) {
            std::cout << std::get<0>(ip) << "." << std::get<1>(ip) << "."
            << std::get<2>(ip) << "." << std::get<3>(ip) << std::endl;
        };

        //3 Целевой IP
        constexpr std::tuple<int,int,int, int> target_ip=generation_ip(267);

        // Cчитывание, сортировка и вывод
        std::vector<std::tuple<int,int,int, int>> ip_pool;
        for(std::string line; std::getline(std::cin, line);)
        {
            if (!line.empty() && line.back() == '\r') line.pop_back(); 
            if (line.empty()) continue;                                // пустая строка
            std::vector<std::string> v = split(line, '\t');
            auto o = split(v.at(0), '.');
            ip_pool.push_back(std::tuple(std::stoi(o.at(0)),std::stoi(o.at(1)),
            std::stoi(o.at(2)),std::stoi(o.at(3))));
        }

        // TODO reverse lexicographically sort
        std::sort(ip_pool.begin(), ip_pool.end(),
        [](const auto& a, const auto& b) { return a > b; });


        //4 Считывание с файла
        std::vector<std::tuple<int,int,int,int>> file_pool;
        std::ifstream file("ip_filter.tsv");
        for (std::string line; std::getline(file, line); )
        {
            if (!line.empty() && line.back() == '\r') line.pop_back();
            if (line.empty()) continue;
            auto v = split(line, '\t');
            auto o = split(v.at(0), '.');
            file_pool.push_back(std::tuple(std::stoi(o.at(0)),std::stoi(o.at(1)),
            std::stoi(o.at(2)), std::stoi(o.at(3))));
        }

        // список с файла тоже в обратном лексикографическом порядке
        std::sort(file_pool.begin(), file_pool.end(),
        [](const auto& a, const auto& b) { return a > b; });

        //5 Вывод целевого IP и всех IP с файла

        std::cout << "target IP: ";
        print_ip(target_ip);


        for (const auto& ip : file_pool)
        {
            print_ip(ip);
        }

        //6 Поиск повтороного IP
        bool flag_to_find=false;
        for (const auto& ip : file_pool)
        {
            if (ip == target_ip){
                flag_to_find=true;
            }
        }
        print_ip(target_ip);
        if(flag_to_find){std::cout<<"найдено"<<std::endl;}
        else{std::cout<<"не найдено"<<std::endl;}


        // 7.1. Первый байт равен 1
        auto ip1 = [](const auto& ip) {
            return std::get<0>(ip) == 1;
        };
        for (const auto& ip : file_pool) {
            if (ip1(ip)){
                print_ip(ip);
            }
        }

        // 7.2. Первый байт 46, второй 70
        auto ip46_70 = [](const auto& ip) {
            return std::get<0>(ip) == 46 && std::get<1>(ip) == 70;
        };
        for (const auto& ip : file_pool) {
            if (ip46_70(ip)){
                print_ip(ip);
            }
        }

        // 7.3. Любой байт равен 46
        auto ip_any46 = [](const auto& ip) {
            return std::get<0>(ip) == 46 || std::get<1>(ip) == 46 ||
            std::get<2>(ip) == 46 || std::get<3>(ip) == 46;
        };
        for (const auto& ip : file_pool) {
            if (ip_any46(ip)){
                print_ip(ip);
            }
        }
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }


    return 0;
}