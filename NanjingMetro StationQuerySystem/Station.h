#pragma once
#include <string>
#include <unordered_set>
#include <memory>


class UndergroundLine;

class Station {
private:
    std::string name;
    std::unordered_set<std::shared_ptr<Station>> adjacentStations; 
    std::vector<UndergroundLine> undergroundLines;
    double longitude;
    double latitude;
public:
    std::string getName() const;
    std::unordered_set<std::shared_ptr<Station>> getAdjacentStations() const;
    double getLongitude() const;
    double getLatitude() const;
   std::vector<UndergroundLine> getUndergroundLines() const;
    void setName(const std::string& nam);
    void addAdjacentStation(std::shared_ptr<Station> sta);
    //void setAdjacentStation(std::unordered_set<std::shared_ptr<Station>> ass);
    void addUndergroundLine(UndergroundLine line);
    void setLongitude(double longi);
    void setLatitude(double lati);

    // 重载 == 运算符
    bool operator==(const Station& other) const {
        return name == other.name; 
    }

    Station() : undergroundLines(), longitude(0.0), latitude(0.0) {}
    Station(const std::shared_ptr<Station>& other);
    Station& operator=(const Station& other);
};


namespace std {
    template <>
    struct hash<Station> {
        std::size_t operator()(const Station& station) const {
            return std::hash<std::string>()(station.getName());
        }
    };
}
