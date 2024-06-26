#pragma once
#include<QMainWindow>
#include <QtWidgets>
#include "FileReader.h"
#include"UndergroundLine.h"
#include"Station.h"
#include<memory>


class ModifyStationWindow :public QMainWindow {
	Q_OBJECT
public:
	ModifyStationWindow(QWidget* parent = nullptr);
	~ModifyStationWindow() noexcept;
private:
	QWidget* centralWidget;
	QVBoxLayout* mainLayout;
	QHBoxLayout* stationNameLayout;
	
	QHBoxLayout * buttonLayout;

	QHBoxLayout* newStationNameLayout;
	QHBoxLayout* newStationLongitudeLayout;
	QHBoxLayout* newStationLatitudeLayout;
	

	QLabel* stationNameLabel;
	

	QComboBox* stationNameComboBox;

	QLabel* newStationNameLabel;
	QLineEdit* newStationNameLineEdit;

	QLabel* newStationLongitudeLabel;
	QLineEdit* newStationLongitudeLineEdit;

	QLabel* newStationLatitudeLabel;
	QLineEdit* newStationLatitudeLineEdit;


	
	QPushButton* searchButton;
	
	QPushButton* modifyButton;
	
	QPushButton* saveButton;
	QPushButton* backButton;




private slots:

};

