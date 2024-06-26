#pragma once
#pragma once
#include<QMainWindow>
#include <QtWidgets>
#include "FileReader.h"
#include"UndergroundLine.h"
#include"Station.h"


class DeleteStationWindow :public QMainWindow {
	Q_OBJECT
public:
	DeleteStationWindow(QWidget* parent = nullptr);
	~DeleteStationWindow() noexcept;
private:
	QWidget* centralWidget;
	QVBoxLayout* mainLayout;
	QHBoxLayout * stationNameLayout;
	QHBoxLayout*lineNameLayout;
	QHBoxLayout * buttonLayout;

	QLabel* stationNameLabel;
	QLabel* lineNameLabel;
	QComboBox* stationNameComboBox;
	QComboBox* lineNameComboBox;
	QPushButton* deleteButton;
	QPushButton* saveButton;
	QPushButton* backButton;


private slots:

};
#pragma once
