#include "stdafx.h" // 如果使用预编译头文件，确保在源文件开头包含它
#include "Station.h"
#include "UndergroundLine.h"

std::string Station::getName() const {
    return name;
}

std::unordered_set<std::shared_ptr<Station>> Station::getAdjacentStations() const {
    return adjacentStations;
}

double Station::getLongitude() const {
    return longitude;
}

double Station::getLatitude() const {
    return latitude;
}

std::vector<UndergroundLine> Station::getUndergroundLines() const {
    return undergroundLines;
}

void Station::setName(const std::string& nam) {
    name = nam;
}

void Station::addAdjacentStation(std::shared_ptr<Station> sta) {
    adjacentStations.insert(sta);
}

void Station::addUndergroundLine(UndergroundLine line) {
    if (std::find(undergroundLines.begin(), undergroundLines.end(), line) == undergroundLines.end()) {
        undergroundLines.push_back(line);
    }
    
}

void Station::setLongitude(double longi) {
    longitude = longi;
}

void Station::setLatitude(double lati) {
    latitude = lati;
}

// 复制构造函数
Station::Station(const std::shared_ptr<Station>& other)
    : name(other->name),
    adjacentStations(other->adjacentStations),
    undergroundLines(other->undergroundLines),
    longitude(other->longitude),
    latitude(other->latitude) {}

// 复制赋值运算符
Station& Station::operator=(const Station& other) {
    if (this != &other) {
        name = other.name;
        adjacentStations = other.adjacentStations;
        undergroundLines = other.undergroundLines;
        longitude = other.longitude;
        latitude = other.latitude;
    }
    return *this;
}
