#pragma once
#include<list>
#include"Station.h"
class Station;
class UndergroundLine {
private:
	std::string name;
	std::list<std::shared_ptr<Station>> stations;
public:
	std::string getName()const ;
	std::list<std::shared_ptr<Station>> getStations()const ;
	void setName( std::string name);
	void setStations(std::list<std::shared_ptr<Station>> sta);
	bool operator== (const UndergroundLine & other) {
		return this->name == other.name;
	}
	QColor getColor();
};

