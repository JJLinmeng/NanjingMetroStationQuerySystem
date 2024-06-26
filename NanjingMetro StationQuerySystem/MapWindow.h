#pragma once
#include"UndergroundLine.h"
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <vector>
#include <memory>
#include "Station.h"

class MapWindow : public QGraphicsView
{
    Q_OBJECT

public:
    explicit MapWindow(QWidget* parent = nullptr);
    explicit MapWindow(const std::vector<std::shared_ptr<Station>>& stations, QWidget* parent = nullptr);

protected:
    double calcx(const std::shared_ptr<Station>& station);
    double calcy(const std::shared_ptr<Station>& station);
    void wheelEvent(QWheelEvent* event) override;
    void  addConnectionBetweenTwoStations(const std::shared_ptr<Station>& station1, const std::shared_ptr<Station>& station2);
    void setupInfoLabel();

private:
    QGraphicsScene* scene;
    std::list<std::shared_ptr<Station>> stations;
    QGraphicsScene* infoScene;
    QGraphicsView* infoView;
    void addStationsToScene();
    void addConnection(const std::shared_ptr<Station>& station);
    double scaleFactorX;
    double scaleFactorY;
    double offsetX;
    double offsetY;
    double maxLongitude;
    double minLongitude;
    double maxLatitude;
    double minLatitude;


   
};

