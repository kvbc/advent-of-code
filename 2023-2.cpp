#include <iostream>
#include <string>
#include <fstream>
#include <utility>
#include <string_view>
#include <vector>

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

int main() {
    std::size_t sum = 0;
    std::ifstream file("input.txt");
    for(std::string line; std::getline(file, line);) {
        auto line_lr = split_string(line, ": ");
        auto game = line_lr.at(0);
        auto sets = line_lr.at(1);
        
        std::size_t game_id = std::stoull(split_string(game, " ").at(1).data());
        
        for(std::string_view set : split_string(sets, "; "))
        for(std::string_view subset : split_string(set, ", ")) {
            auto subset_lr = split_string(subset, " ");
            std::size_t count = std::stoull(subset_lr.at(0).data());
            std::string_view color = subset_lr.at(1);
                 if(color == "red"  ){ if(count > 12) goto next; }
            else if(color == "green"){ if(count > 13) goto next; }
            else if(color == "blue" ){ if(count > 14) goto next; }
        }
        
        sum += game_id;
        
    next:
        continue;
    }
    std::cout << "Sum: " << sum << std::endl;
}
