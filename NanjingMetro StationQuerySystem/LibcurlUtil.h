#pragma once
#include <string>
#include <curl/curl.h>
#include <json/json.h>
class LibcurlUtil {
public:
	static  size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s);
	static std::string getJSONStringWithNameInNanJing(QString name);
};
