#include<stdafx.h>
#include "MapWindow.h"
#include "FileReader.h"
#include"Calculator.h"
#include"UndergroundLine.h"
#include"Calculator.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QWheelEvent>
#include <QDebug>


MapWindow::MapWindow(QWidget* parent)
    : QGraphicsView(parent), scene(new QGraphicsScene(this))
{
    
   
   
    scene->setSceneRect(0, 0, 4000, 3000);

    setScene(scene);
    scaleFactorX = scene->width() * 0.8;
    scaleFactorY = scene->height() * 0.8;
    offsetX = scene->width() * 0.1;
    offsetY = scene->height() * 0.1;
   
    setRenderHint(QPainter::Antialiasing);

    
    setDragMode(QGraphicsView::ScrollHandDrag);

   infoScene = new QGraphicsScene(this);
    infoView = new QGraphicsView(infoScene, this);
    stations = FileReader::allStations;

    
    addStationsToScene();
   
    QRectF initialRect(0, 0, 1000, 800);
    fitInView(initialRect, Qt::KeepAspectRatio);
    centerOn(scene->sceneRect().center());
    setupInfoLabel();
}

MapWindow::MapWindow(const std::vector<std::shared_ptr<Station>>& stations, QWidget* parent):MapWindow(parent)
{
    for (int i = 0; i < stations.size()-1; i++) {
      


        addConnectionBetweenTwoStations(stations[i], stations[i + 1]);
      
    }
}

void MapWindow::addStationsToScene()
{

    maxLongitude = -180.0;
     minLongitude = 180.0;
     maxLatitude = -90.0;
    minLatitude = 90.0;

    for (auto& station : stations) {
        double longitude = station->getLongitude();
        double latitude = station->getLatitude();
        if (longitude > maxLongitude) maxLongitude = longitude;
        if (longitude < minLongitude) minLongitude = longitude;                
        if (latitude > maxLatitude) maxLatitude = latitude;
        if (latitude < minLatitude) minLatitude = latitude;
    }
   
    

    for (auto& station : stations) {
        double x= calcx(station);
        double y= calcy(station);
        

        addConnection(station);
        QGraphicsEllipseItem* ellipse = scene->addEllipse(x, y, 5, 5, QPen(Qt::black), QBrush(Qt::red));
        QGraphicsTextItem* text = scene->addText(QString::fromLocal8Bit(station->getName().c_str()));
        text->setPos(x + 10, y);
    }
}

void MapWindow::addConnection(const std::shared_ptr<Station>& station) {
    
    
        auto adjacentStations = station->getAdjacentStations();
        for (const auto& adjacentStation : adjacentStations) {
            double x1 = calcx(station);
            double y1 = calcy(station);
            double x2 = calcx(adjacentStation);
            double y2 = calcy(adjacentStation);
            auto line = Calculator::findSame(station->getUndergroundLines(), adjacentStation->getUndergroundLines());
            //std::cout << line.getName()<<"   ";
            scene->addLine(x1, y1, x2, y2, QPen(line.getColor()));
        }
    
   
    
    
   
}

double MapWindow:: calcx(const std::shared_ptr<Station>& station) {
    
   
    double normalizedLongitude = (station->getLongitude() - minLongitude) / (maxLongitude - minLongitude) * scaleFactorX;
    double x= normalizedLongitude + offsetX;
    return x;
}

double MapWindow::calcy(const std::shared_ptr<Station>& station) {
    double normalizedLatitude = (station->getLatitude() - minLatitude) / (maxLatitude - minLatitude) * scaleFactorY;
    double y = normalizedLatitude + offsetY;
    return y;
}

void MapWindow::wheelEvent(QWheelEvent* event)
{
    
    const double scaleFactor = 1.15;
    if (event->angleDelta().y() > 0) {
        scale(scaleFactor, scaleFactor);
    }
    else {
        scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }
}
void MapWindow::addConnectionBetweenTwoStations(const std::shared_ptr<Station>& station1, const std::shared_ptr<Station>& station2)
{
    double x1= calcx(station1);
    double y1= calcy(station1);
    double x2= calcx(station2);
    double y2= calcy(station2);
    auto line = Calculator::findSame(station1->getUndergroundLines(), station2->getUndergroundLines());
    QPen pen(line.getColor());
    pen.setWidth(10);
    scene->addLine(x1, y1, x2, y2, pen);
}

void MapWindow::setupInfoLabel()
{
    infoView->setStyleSheet("background-color: white; border: 1px solid black;");
    infoView->setAlignment(Qt::AlignTop | Qt::AlignRight);
   

    // 获取所有线路信息
    auto lines = FileReader::lines;

    // 使用 QGraphicsScene 来显示带颜色的圆圈和文本
    int yOffset = 10;
    for (auto& line : lines) {
        QString lineName = QString::fromLocal8Bit(line.getName().data());
        QColor color = line.getColor();

        // 添加圆圈
        QGraphicsEllipseItem* ellipse = infoScene->addEllipse(10, yOffset, 10, 10, QPen(color), QBrush(color));

        // 添加文本
        QGraphicsTextItem* text = infoScene->addText(lineName);
        text->setPos(30, yOffset - 5);  // 调整文本位置

        yOffset += 20;  // 调整垂直间距
    }

    
}