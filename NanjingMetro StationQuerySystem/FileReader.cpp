#include "stdafx.h"
#include "FileReader.h"
#include "StringUtil.h"
#include"UndergroundLine.h"
std::list<std::shared_ptr<Station>> FileReader::allStations;
std::vector<UndergroundLine> FileReader::lines;


std::shared_ptr<Station> FileReader::find_or_create_station(const std::string& name)
{

    auto it = std::find_if(allStations.begin(), allStations.end(),[&name](const std::shared_ptr<Station>& station) {
            return station->getName() == name;
        });
    if (it != allStations.end()) {
        return *it;
    }
    else {
        auto newStation = std::make_shared<Station>();
        newStation->setName(name);
        allStations.push_back(newStation);
        return newStation;
    }
}

std::list<std::shared_ptr<Station>>  FileReader:: getAllStations() {

   
    std::ifstream file("NJDT.txt");
    if (!file) {
        std::cerr << "Failed to open file NJDT.txt" << std::endl;
        return allStations;
    }

    std::string words;

    std::list<std::shared_ptr<Station>> tempStations;
    int cnt = -1;

    while (std::getline(file, words)) {
        if (words.empty()) {
            continue;
        }
        if (StringUtil::starts_with_digit_or_S(words)) {
            if (cnt >= 0) {
                lines[cnt].setStations(tempStations);
                tempStations.clear();
            }
            UndergroundLine line;
            line.setName(words);
            lines.push_back(line);
            cnt++;
        }
        else {
            std::vector<std::string> firstSplit = StringUtil::split(words, ' ');
            if (firstSplit.size() < 2) {
                std::cerr << "Invalid format: " << words << std::endl;
                continue;
            }
            auto station = find_or_create_station(firstSplit.at(0));
            station->addUndergroundLine(lines.at(cnt));
            std::vector<std::string> secondSplit = StringUtil::split(firstSplit.at(1), ',');
            if (secondSplit.size() < 2) {
                std::cerr << "Invalid format: " << firstSplit.at(1) << std::endl;
                continue;
            }
            try {
                double longitude = std::stod(secondSplit.at(0));
                double latitude = std::stod(secondSplit.at(1));
                station->setLongitude(longitude);
                station->setLatitude(latitude);
            }
            catch (const std::invalid_argument& e) {
                std::cerr << "Invalid argument: " << e.what() << std::endl;
                continue;
            }
            tempStations.push_back(station);
        }
    }

    if (cnt >= 0) {
        lines[cnt].setStations(tempStations);
    }

    for (const auto& line : lines) {
        auto stations = line.getStations();
        for (auto it = stations.begin(); it != stations.end(); ++it) {
            if (it != stations.begin()) {
                auto prevIt = it;
                --prevIt;
                (*it)->addAdjacentStation(*prevIt);
            }
            auto nextIt = it;
            ++nextIt;
            if (nextIt != stations.end()) {
                (*it)->addAdjacentStation(*nextIt);
            }
        }

    }
   

    return allStations;
}

void FileReader::addStation(std::string name, double longitude, double latitude, std::string stationLine, std::string stationadjacentStationOne, std::string stationadjacentStationTwo)
{
    UndergroundLine currentLine;
    int index=-1;
    for (int i = 0;i<FileReader::lines.size();i++) {
        if (FileReader::lines[i].getName() == stationLine) {
            currentLine = FileReader::lines[i];
            index = i;
        }
    }
    std::list<std::shared_ptr<Station>> tempStations=currentLine.getStations();
    auto station=find_or_create_station(name);
    auto it =tempStations.begin();
    station->addUndergroundLine(currentLine);
    station->setLongitude(longitude);
    station->setLatitude(latitude);
    if (stationadjacentStationOne == "" && stationadjacentStationTwo == "") {
        tempStations.push_front(station);
    }
    else {
        for (; it != tempStations.end(); ++it) {
            if ((*it)->getName() == stationadjacentStationOne || (*it)->getName() == stationadjacentStationTwo) {
                break;
            }
        }
        tempStations.insert(++it, station);
    }
    
    currentLine.setStations(tempStations);
    FileReader::lines[index]=currentLine;
    for (auto station : FileReader::lines[index].getStations()) {
        std::cout<<station->getName()<<" ";
    }
}

void FileReader::deleteStation(std::string stationName, std::string stationLine)
{
    std::cout << stationLine << std::endl;
    
    if (!StringUtil::starts_with_digit_or_S(stationLine)) {
        std::cout << "123456";
        for (auto& line : FileReader::lines) {
            auto  stations = line.getStations();
            for (auto it = stations.begin(); it != stations.end();) {
                if ((*it)->getName() == stationName) {
                    it = stations.erase(it);
                }
                else {
                    ++it;
                }
            }
            line.setStations(stations);
        }
    }
    else {
        for (auto& line : FileReader::lines) {
            if (line.getName() == stationLine) {
                auto stations = line.getStations();
                for (auto it = stations.begin(); it != stations.end();) {
                    if ((*it)->getName() == stationName) {
                        it = stations.erase(it);
                    }
                    else {
                        ++it;
                    }
                }
                line.setStations(stations);
            }
        }
    }
}

void FileReader::deleteLine(std::string lineName)
{
    for (auto it = FileReader::lines.begin(); it != FileReader::lines.end(); ) {
        if (it->getName() == lineName) {
            it = FileReader::lines.erase(it); 
        }
        else {
            ++it; 
        }
    }
}

void FileReader::save()
{
    std::ofstream file("NJDT.txt");
    if (file) {
        for (const auto& line : lines) {
            file << line.getName() << std::endl;
            for (const auto& station : line.getStations()) {
                file << station->getName() << " " << station->getLongitude() << "," << station->getLatitude() << std::endl;
            }
        }
    }
    file.close();

}
