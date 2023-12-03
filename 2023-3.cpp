#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_set>

static bool is_num(char c) {
    return c >= '0' && c <= '9';
}

static bool is_symbol(char c) {
    return c != '.' && !is_num(c);
}

int main() {
    std::string str; {
        std::ifstream f("input.txt");
        std::stringstream ss;
        ss << f.rdbuf();
        str = ss.str();
    }
    
    std::size_t width = 0;
    for(auto it = str.cbegin(); it != str.cend(); it++) {
        if(*it == '\n')
            break;
        width++;
    }
    std::size_t height = (str.length() + 1/*nl*/) / width - 1/*nl*/;
    
    auto idx = [&](int x, int y) -> int {
        if(x < 0 || x >= width)
            return -1;
        if(y < 0 || y >= height)
            return -1;
        return y * (width + 1/*nl*/) + x;
    };
    
    auto at = [&](int x, int y) -> char {
        int i = idx(x, y);
        if(i < 0)
            return 0;
        return str.at(i);
    };
    
    auto try_read_number = [&](int x, int y) -> std::size_t {
        static std::unordered_set<int> met_indices;
        
        if(!is_num(at(x,y)))
            return 0;
        
        int lx = x;
        while(is_num(at(lx-1,y)))
            lx--;
        
        int lx_idx = idx(lx,y);
        if(met_indices.contains(lx_idx))
            return 0;
        met_indices.insert(lx_idx);
        
        int rx = x;
        while(is_num(at(rx+1,y)))
            rx++;
        
        std::size_t num = 0;
        for(x = lx; x <= rx; x++) {
            num *= 10;
            num += at(x,y) - '0';
        }
        return num;
    };
    
    std::cout << "Size: (" << width << ", " << height << ')' << std::endl;
    
    std::size_t sum = 0;
    for(int x = 0; x < width; x++)
    for(int y = 0; y < height; y++) {
        char c = at(x, y);
        if(is_symbol(c))
        for(int ix = -1; ix <= 1; ix++)
        for(int iy = -1; iy <= 1; iy++) {
            if(ix == 0 && iy == 0)
                continue;
            sum += try_read_number(x + ix, y + iy);
        }
    }
    
    std::cout << "Sum: " << sum << std::endl;
}
