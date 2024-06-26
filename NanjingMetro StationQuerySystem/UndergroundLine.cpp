#include "stdafx.h"
#include "UndergroundLine.h"
#include <iostream>

std::string UndergroundLine::getName()const
{
    return name;
}

std::list<std::shared_ptr<Station>> UndergroundLine::getStations()const
{
    return stations;
}

void UndergroundLine::setName(std::string nam)
{
    name = nam;
}

void UndergroundLine::setStations(std::list<std::shared_ptr<Station>> sta)
{
    stations = sta;
}

QColor UndergroundLine::getColor()
{
    //std::cout<< name << std::endl;
    QString name = QString::fromLocal8Bit(this->getName().data());
    
    QString line1Name = "1号线";
    QString line2Name = "2号线";
    QString line3Name = "3号线";
    QString line4Name = "4号线";
    QString line7Name = "7号线";
    QString line10Name = "10号线";
    QString line7southName = "7号线南段";
    QString s1Name = "S1号线";
    QString s3Name = "S3号线";
    QString s6Name = "S6号线";
    QString s7Name = "S7号线";
    QString s8Name = "S8号线";
    QString s9Name = "S9号线";
    QString line5Name = "5号线";


    if (name == line1Name) {
        return Qt::red;
    }
   else if (name == line2Name) {
       return Qt::blue;
   }
   else if (name == line3Name) {
       return Qt::green;
   }
   else if (name == line4Name) {
       return Qt::cyan;
   }
   else if (name == line7Name) {
       return Qt::magenta;
   }
   else if (name == line10Name) {
       return Qt::yellow;
   }
   else if (name == line7southName) {
        return Qt::darkYellow;
    }
   else if (name == s1Name) {
       return Qt::darkYellow;
   }
   else if (name == s3Name) {
       return Qt::darkGreen;
   }
   else if (name == s6Name) {
       return Qt::darkMagenta;
   }
   else if (name == s7Name) {
       return Qt::darkCyan;
   }
   else if (name == s8Name) {
       return Qt::darkBlue;
   }
   else if (name == s9Name) {
       return Qt::darkRed;
    }
   else if (name == line5Name) {
       return Qt::darkGray;
    }
   else {
        int red = QRandomGenerator::global()->bounded(256);
        int green = QRandomGenerator::global()->bounded(256);
        int blue = QRandomGenerator::global()->bounded(256);

        // 创建一个 QColor 对象
        QColor randomColor(red, green, blue);
        return randomColor;
    }
}

