#pragma once
#include<QMainWindow>
#include <QtWidgets>
#include "FileReader.h"
#include"UndergroundLine.h"
#include"Station.h"


class AddStationWindow :public QMainWindow {
	Q_OBJECT
public:
	AddStationWindow(QWidget* parent = nullptr);
	~AddStationWindow() noexcept;
private:
	QVBoxLayout* AddStationLayout;
	QWidget* centralWidget;
	QHBoxLayout * stationNameLayout;
	QHBoxLayout * stationLongitudeLayout;
	QHBoxLayout * stationLatitudeLayout;
	QHBoxLayout * stationLineLayout;
	QHBoxLayout * stationadjacentStationOneLayout;
	QHBoxLayout * stationadjacentStationTwoLayout;
	QHBoxLayout * buttonLayout;


	QLabel* stationNameLabel;
	QLabel* stationLongitudeLabel;
	QLabel* stationLatitudeLabel;
	QLabel* stationLineLabel;
	QLabel* stationadjacentStationOneLabel;
	QLabel* stationadjacentStationTwoLabel;

	QLineEdit* stationNameLineEdit;
	QLineEdit* stationLongitudeLineEdit;
	QLineEdit* stationLatitudeLineEdit;
	QComboBox* stationLineComboBox;
	QLineEdit* stationadjacentStationOneLineEdit;
	QLineEdit* stationadjacentStationTwoLineEdit;

	QPushButton * addStationButton;
	QPushButton * backButton;
	QPushButton* saveButton;


private slots:

};
#pragma once
