#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string_view>
#include <unordered_set>

std::vector<std::string_view> split_string(std::string_view str, std::string_view delim) {
    std::vector<std::string_view> subs;
    for(std::size_t i = 0; i < str.length();) {
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

std::size_t char_to_num(char c) {
    return std::isdigit(c) ? c-'0' : 0;
}

int main() {
    std::size_t total_points = 0;
    std::ifstream file("input.txt");
    for(std::string line; std::getline(file, line);) {
        auto line_lr = split_string(line, ": ");
        auto nums_lr = split_string(line_lr.at(1), " | ");
        auto win_nums_str = nums_lr.at(0);
        auto have_nums_str = nums_lr.at(1);
        
        auto str_to_set = [&](std::string_view str) -> std::unordered_set<std::size_t> {
            std::unordered_set<std::size_t> set;
            for(auto it = str.cbegin(); it < str.cend(); it += 3)
                set.insert( char_to_num(*it)*10 + char_to_num(*(it+1)) );
            return set;
        };
        
        auto win_nums = str_to_set(win_nums_str);
        auto have_nums = str_to_set(have_nums_str);
        
        std::size_t points = 0;
        for(auto win_num : win_nums)
            if(have_nums.contains(win_num))
                points = (points == 0) ? (1) : (points * 2);
        total_points += points;
    }
    std::cout << "Total Points: " << total_points << std::endl;
}
