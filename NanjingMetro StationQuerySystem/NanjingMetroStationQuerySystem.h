#pragma once
#pragma execution_character_set("utf-8")


#include <QtWidgets/QMainWindow>
#include "ui_NanjingMetroStationQuerySystem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class NanjingMetroStationQuerySystemClass; };
QT_END_NAMESPACE

class NanjingMetroStationQuerySystem : public QMainWindow
{
    Q_OBJECT

public:
    NanjingMetroStationQuerySystem(QWidget *parent = nullptr);
    ~NanjingMetroStationQuerySystem();

private slots:
   
    /*void register();*/
private:
    Ui::NanjingMetroStationQuerySystemClass *ui;

   

};
