#include <iostream>
#include <string>
#include <fstream>

int main() {
    std::size_t sum = 0;
    std::ifstream file("input.txt");
    for(std::string line; std::getline(file, line);) {
        auto pos1 = line.find_first_of("123456789");
        auto pos2 = line.find_last_of("123456789");
        if(pos1 != std::string::npos)
            sum += (line.at(pos1) - '0') * 10 + (line.at(pos2) - '0');
    }
    std::cout << "Sum: " << sum << std::endl;
}
