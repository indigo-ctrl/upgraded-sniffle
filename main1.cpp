#include <string>
#include <sstream>

std::string compress_rle(const std::string& input) {
    if (input.empty()) return "";
    
    std::stringstream result;
    int count = 1;
    
    for (size_t i = 1; i <= input.length(); ++i) {
        if (i < input.length() && input[i] == input[i - 1]) {
            count++;
        } else {
            result << input[i - 1] << count;
            count = 1;
        }
    }
    
    return result.str();
}

std::string decompress_rle(const std::string& input) {
    std::stringstream result;
    
    for (size_t i = 0; i < input.length(); i += 2) {
        char c = input[i];
        int count = input[i + 1] - '0';  // Преобразуем символ цифры в число
        
        result << std::string(count, c);
    }
    
    return result.str();
}