#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>
#include <unordered_map>
#include <tuple>

using size_t = std::size_t;

std::vector<std::string_view> split_string(std::string_view str, std::string_view delim) {
    std::vector<std::string_view> subs;
    for(size_t i = 0; i < str.length();) {
        auto delim_pos = str.find(delim, i);
        if(delim_pos == std::string::npos)
            delim_pos = str.length();
        subs.emplace_back(
            str.cbegin() + i,
            str.cbegin() + delim_pos
        );
        i = delim_pos + delim.length();
    }
    return subs;
}

std::vector<size_t> str_to_nums(std::string_view str) {
    std::vector<size_t> nums;
    for(std::string_view num_str : split_string(str, " "))
        nums.emplace_back(std::stoull(std::string(num_str)));
    return nums;
};

int main() {
    std::string str; {
        std::ifstream file("input.txt");
        std::stringstream ss;
        ss << file.rdbuf();
        str = ss.str();
    }
    auto sections = split_string(str, "\n\n");
    auto seeds = str_to_nums(split_string(sections.at(0), ": ").at(1));
    
    using MapLines = std::vector<std::vector<size_t>>;
    std::unordered_map<std::string, MapLines> maps;
    for(size_t i = 1; i < sections.size(); i++) {
        auto map = split_string(sections.at(i), "\n");
        auto map_name = split_string(map.at(0), " ").at(0);
        MapLines map_lines;
        for(size_t j = 1; j < map.size(); j++)
            map_lines.emplace_back(str_to_nums(map.at(j)));
        maps.emplace(map_name, map_lines);
    }
    
    auto src_to_desc = [](size_t v, const MapLines& lines) -> size_t {
        for(auto line : lines) {
            auto it = line.cbegin();
            size_t desc_start = *it;
            std::advance(it, 1);
            size_t src_start = *it;
            std::advance(it, 1);
            size_t len = *it;
            if(v >= src_start && v < src_start + len)
                return desc_start + (v - src_start);
        }
        return v;
    };
    
    int min_loc = -1;
    for(auto seed : seeds) {
        size_t soil  = src_to_desc(seed,  maps.at("seed-to-soil"));
        size_t fert  = src_to_desc(soil,  maps.at("soil-to-fertilizer"));
        size_t water = src_to_desc(fert,  maps.at("fertilizer-to-water"));
        size_t light = src_to_desc(water, maps.at("water-to-light"));
        size_t temp  = src_to_desc(light, maps.at("light-to-temperature"));
        size_t hum   = src_to_desc(temp,  maps.at("temperature-to-humidity"));
        size_t loc   = src_to_desc(hum,   maps.at("humidity-to-location"));
        if(min_loc < 0 || loc < min_loc)
            min_loc = loc;
    }
    
    std::cout << "Lowest location: " << min_loc << std::endl;
}
