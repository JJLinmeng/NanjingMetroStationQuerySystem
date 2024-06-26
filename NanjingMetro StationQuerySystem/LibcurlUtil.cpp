#include "stdafx.h"
#include "LibcurlUtil.h"
#include <iostream>
#include<QString>
#include"StringUtil.h"

size_t LibcurlUtil::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s)
{
	size_t newLength = size * nmemb;
	    try {
	        s->append((char*)contents, newLength);
	    }
	    catch (std::bad_alloc& e) {
	        // 内存分配失败
	        return 0;
	    }
	    return newLength;
}
std::string LibcurlUtil::getJSONStringWithNameInNanJing(QString name)
{
	
	
	CURL* curl;
	CURLcode res;
	std::string readBuffer;

	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();
	QString qname = QUrl::toPercentEncoding(name);
	std::string url = "https://restapi.amap.com/v5/place/text?keywords=" +(std::string) qname.toLocal8Bit() + "&types=141201&region=025&key=6f482cdf3803c7dfb8eed38fc981fa5a";
	
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);

		if (res != CURLE_OK) {

			return "";
		}
	}
	curl_global_cleanup();


	return readBuffer;
	
}
