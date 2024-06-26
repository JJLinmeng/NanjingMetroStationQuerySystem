#include "stdafx.h"
#include "NanjingMetroStationQuerySystem.h"


NanjingMetroStationQuerySystem::NanjingMetroStationQuerySystem(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::NanjingMetroStationQuerySystemClass())
{
    ui->setupUi(this);
    
}

NanjingMetroStationQuerySystem::~NanjingMetroStationQuerySystem()
{
    delete ui;
}
