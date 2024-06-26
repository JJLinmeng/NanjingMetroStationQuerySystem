#pragma once
#include<string>
#include<memory>
#include "Station.h"
#include<fstream>
#include<iostream>
#include<vector>

class FileReader {
public:
	static std::shared_ptr<Station> find_or_create_station(const std::string& name);
	static std::list<std::shared_ptr<Station>> getAllStations();

	static std::list<std::shared_ptr<Station>> allStations;
	static std::vector<UndergroundLine> lines;
	
	static void addStation(std::string name, double longitude, double latitude, std::string stationLine, std::string stationadjacentStationOne, std::string stationadjacentStationTwo);

	static void deleteStation(std::string stationName, std::string stationLine);

	static void deleteLine(std::string lineName);

	static void save();
};