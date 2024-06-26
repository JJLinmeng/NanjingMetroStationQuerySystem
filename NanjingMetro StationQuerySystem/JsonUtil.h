#pragma once
#include<json/json.h>
#include"StringUtil.h"

class JsonUtil {
public:
	static std::pair<double,double> getLocationFromJson(std::string jsonStr);
};
