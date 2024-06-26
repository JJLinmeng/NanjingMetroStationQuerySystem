#pragma once

#include<QMainWindow>
#include <QtWidgets>
#include "FileReader.h"
#include"UndergroundLine.h"
#include"Station.h"


class DeleteLineWindow :public QMainWindow {
	Q_OBJECT
public:
	DeleteLineWindow(QWidget* parent = nullptr);
	~DeleteLineWindow() noexcept;
private:
	QWidget* centralWidget;
	QVBoxLayout* mainLayout;
	
	QHBoxLayout* lineNameLayout;
	QHBoxLayout* buttonLayout;

	
	QLabel* lineNameLabel;

	QComboBox* lineNameComboBox;
	QPushButton* deleteButton;
	QPushButton* saveButton;
	QPushButton* backButton;


private slots:

};

