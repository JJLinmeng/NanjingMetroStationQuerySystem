#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include <Station.h>
#include "FileReader.h"
#include "UndergroundLine.h"
#include <queue>



class Calculator {
public:
	static std::unordered_map<std::string, std::list<std::pair<std::shared_ptr<Station>, double>>>buildAdjacencyList();
	static std::vector<std::shared_ptr<Station>> findShortestPath( std::string& start,  std::string& goal);
	static UndergroundLine findSame(const std::vector<UndergroundLine>& lines1, const std::vector<UndergroundLine>& lines2);
	static QList<QString> getShortestPathList(std::vector<std::shared_ptr<Station>> path);
};