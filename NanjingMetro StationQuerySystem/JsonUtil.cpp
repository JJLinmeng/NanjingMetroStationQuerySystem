#include "stdafx.h"
#include "JsonUtil.h"
#include<iostream>

std::pair<double, double> JsonUtil::getLocationFromJson(std::string jsonStr)
{
    Json::Value root;
    Json::Reader reader;
    if (!reader.parse(jsonStr, root)) {
       
       return std::pair<double, double>(0, 0);
    }
    Json::Value pois = root["pois"];
    std::string location=pois[0]["location"].asString();
    
    std::vector<std::string> result =StringUtil::split(location, ',');
    if (result.size() == 2) {
        return std::pair<double, double>(std::stod(result[0]), std::stod(result[1]));
    }
    else {
        return std::pair<double, double>(0, 0);
    }

}
