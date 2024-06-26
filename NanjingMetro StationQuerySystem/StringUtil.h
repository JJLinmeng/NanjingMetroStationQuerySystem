#pragma once
#include "stdafx.h"
#include <vector>
#include <string>

class StringUtil {
public:

    static bool starts_with_digit_or_S(const std::string& str);
    static std::vector<std::string> split(const std::string& s, char delimiter);
    static std::string urlEncode(const std::string& str);
       
};



