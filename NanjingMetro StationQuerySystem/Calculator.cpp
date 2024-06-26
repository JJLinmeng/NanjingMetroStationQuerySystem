#include "stdafx.h"
#include "Calculator.h"
#include"JsonUtil.h"
#include"LibcurlUtil.h"
#include<cmath>

std::unordered_map<std::string, std::list<std::pair<std::shared_ptr<Station>, double>>> Calculator::buildAdjacencyList()
{
    std::unordered_map<std::string, std::list<std::pair<std::shared_ptr<Station>, double>>> adjacencyList;
    auto allStations = FileReader::allStations;
    for (const auto& station : allStations) {
        std::list<std::pair<std::shared_ptr<Station>, double>> adjacents;
        for (const auto& adjacent : station->getAdjacentStations()) {
            //double distance = std::sqrt(std::pow(station->getLongitude() - adjacent->getLongitude(), 2) + std::pow(station->getLatitude() - adjacent->getLatitude(), 2));
            double distance = 1;
            adjacents.emplace_back(adjacent, distance);
        }
        adjacencyList[station->getName()] = adjacents;
    }

    return adjacencyList;
}

std::vector<std::shared_ptr<Station>> Calculator::findShortestPath( std::string& start,  std::string& goal)
{
    boolean isFind=false;
    auto adjacencyList = buildAdjacencyList();

    std::unordered_map<std::string, double> distances;
    std::unordered_map<std::string, std::shared_ptr<Station>> previous;
    std::priority_queue<std::pair<double, std::shared_ptr<Station>>, std::vector<std::pair<double, std::shared_ptr<Station>>>, std::greater<>> pq;
    auto allStations = FileReader::allStations;
    for (const auto& station : allStations) {
        distances[station->getName()] = std::numeric_limits<double>::infinity();
    }
    distances[start] = 0;

    boolean isStartExist = false;
    boolean isGoalExist = false;
    std::shared_ptr<Station> startStation = nullptr;
    for (const auto& station : allStations) {
        if (station->getName() == start) {
            startStation = station;
            isStartExist = true;
        }
        if (station->getName() == goal) {
            isGoalExist = true;
        }
    }
   if (isStartExist == false) {
       double distance=std::numeric_limits<double>::infinity();
      
       std::pair<double, double> location = JsonUtil::getLocationFromJson(LibcurlUtil::getJSONStringWithNameInNanJing(QString::fromLocal8Bit(start.data())));
       if (location.first == 0 && location.second == 0) {
           QMessageBox::warning(nullptr, "警告", "不存在该点");
           return std::vector<std::shared_ptr<Station>>();
       }
       for (auto station : FileReader::allStations) {
           double distance2 = std::sqrt(std::pow(location.first - station->getLongitude(), 2) + std::pow(location.second- station->getLatitude(), 2));
           if (distance2 < distance) {
                distance = distance2;
                startStation = station;
                start=station->getName();
           }
       }
     
    }

    if (isGoalExist == false) {
        double distance=std::numeric_limits<double>::infinity();
        std::pair<double, double> location = JsonUtil::getLocationFromJson(LibcurlUtil::getJSONStringWithNameInNanJing(QString::fromLocal8Bit(goal.data())));
        if (location.first == 0 && location.second == 0) {
            QMessageBox::warning(nullptr, "警告", "不存在该点");
            return std::vector<std::shared_ptr<Station>>();
           
        }
        for (auto station : FileReader::allStations) {
            double distance2 = std::sqrt(std::pow(location.first - station->getLongitude(), 2) + std::pow(location.second - station->getLatitude(), 2));
            if (distance2 < distance) {
                distance = distance2;
                goal=station->getName();
            }
        }
    }
    

    pq.emplace(0.0, startStation);  
    std::shared_ptr<Station> currentStation;
    while (!pq.empty()) {

       
        std::pair<double, std::shared_ptr<Station>> top = pq.top();
        double currentDistance = top.first;
         currentStation = top.second;
        pq.pop();

       
        if (currentStation->getName() == goal) {
            isFind = true; break;
        }

        
        const auto& adjacents = adjacencyList[currentStation->getName()];
        for (const auto& adjacent : adjacents) {
            std::shared_ptr<Station> adjacentStation = adjacent.first;
            double distance = adjacent.second;

            double newDistance = currentDistance + distance;
            if (newDistance < distances[adjacentStation->getName()]) {
                distances[adjacentStation->getName()] = newDistance;
                previous[adjacentStation->getName()] = currentStation;
                pq.emplace(newDistance, adjacentStation);
            }
        }
    }
    
    if (isFind) {
        std::vector<std::shared_ptr<Station>> path;
        for (std::shared_ptr<Station> at = currentStation; at != nullptr; at = previous[at->getName()]) {
            path.push_back(at);
            if (at->getName() == start) break;
        }
        std::reverse(path.begin(), path.end());
        return path;
    }
    else {
        
        return std::vector<std::shared_ptr<Station>>();
    }
}

UndergroundLine Calculator::findSame(const std::vector<UndergroundLine>& lines1, const std::vector<UndergroundLine>& lines2)
{
    for (const auto& i : lines1) {
        for (const auto& j : lines2) {
            if (i.getName() == j.getName()) {
                return i;
            }
        }
    }
    return UndergroundLine();
}



QList<QString> Calculator::getShortestPathList(std::vector<std::shared_ptr<Station>> path)
{      
   
    if (path.empty()) {
        return QList<QString>();
    }
    
    QList<QString> lines;
    int cnt = 0;
    std::string currentLine;
    for (int i = 0; i < path.size(); ++i) {
        auto station = path[i];

        if (station->getUndergroundLines().size() > 1) {
            
            if (i == 0) {
                if (i + 1 < path.size()) {
                    auto nextStation = path[i + 1];

                    currentLine = station->getUndergroundLines().front().getName();


                    lines.push_back(QString::fromLocal8Bit(nextStation->getUndergroundLines().front().getName().data()));
                    lines.push_back(QString::fromLocal8Bit(station->getName().data()));
                }

            }
            else {
                if (i + 1 < path.size()) {
                    auto nextStation = path[i + 1];
                    if (nextStation->getUndergroundLines().size() > 1) {
                       
                        UndergroundLine sameLine = Calculator::findSame(station->getUndergroundLines(), nextStation->getUndergroundLines());
                        
                        if (sameLine.getName() != currentLine) {
                            lines.push_back(QString::fromLocal8Bit(station->getName().data()));
                            lines.push_back(QString::fromLocal8Bit(sameLine.getName().data()));
                        }
                      
                        currentLine = sameLine.getName();
                    }
                    else {
                       
                        if (currentLine != nextStation->getUndergroundLines().front().getName()) {
                            lines.push_back(QString::fromLocal8Bit(station->getName().data()));
                            lines.push_back(QString::fromLocal8Bit(nextStation->getUndergroundLines().front().getName().data()));
                       }
                        currentLine = nextStation->getUndergroundLines().front().getName();
                    }
                }
                lines.push_back(QString::fromLocal8Bit(station->getName().data()));
            }

        }
        else {
            if (i == 0) {
                currentLine = station->getUndergroundLines().front().getName();
                lines.push_back(QString::fromLocal8Bit(station->getUndergroundLines().front().getName().data()));
            }
            lines.push_back(QString::fromLocal8Bit(station->getName().data()));
        }
    }
   
    return lines;
}
