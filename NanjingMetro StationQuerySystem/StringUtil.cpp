#include "stdafx.h"
#include"StringUtil.h"
#include<iostream>
#include <iomanip>
#include <sstream>
#include <string>

#include <cctype>

bool StringUtil::starts_with_digit_or_S(const std::string& str)
{
    if (str.empty()) return false;
    return str[0] == '0' || str[0] == '1' || str[0] == '2' || str[0] == '3' || str[0] == '4' || str[0] == '5' || str[0] == '6' || str[0] == '7' || str[0] == '8' || str[0] == '9' || str[0] == 'S';
}

std::string charToHex(unsigned char c) {
    std::ostringstream oss;
    oss << '%' << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << static_cast<int>(c);
    return oss.str();
}


std::vector<std::string> StringUtil::split(const std::string& s, char delimiter)
{
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = s.find(delimiter);

    while (end != std::string::npos) {
        tokens.push_back(s.substr(start, end - start));
        start = end + 1;
        end = s.find(delimiter, start);
    }

    tokens.push_back(s.substr(start));

    return tokens;
}

std::string StringUtil::urlEncode(const std::string& str)
{
   
        std::ostringstream oss;
        for (unsigned char c : str) {
            if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
                oss << c;
            }
            else {
                oss << charToHex(c);
            }
        }
        return oss.str();
    
}


