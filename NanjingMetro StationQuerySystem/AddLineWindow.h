
#pragma once
#include<QMainWindow>
#include <QtWidgets>
#include "FileReader.h"
#include"UndergroundLine.h"
#include"Station.h"


class AddLineWindow :public QMainWindow {
	Q_OBJECT
public:
	AddLineWindow(QWidget* parent = nullptr);
	~AddLineWindow() noexcept;
private:
	QVBoxLayout* AddLineLayout;
	QWidget* centralWidget;
	QHBoxLayout* lineNameLayout;
	QHBoxLayout* buttonLayout;


	QLabel* lineNameLabel;
	

	QLineEdit* lineNameLineEdit;
	

	QPushButton* addLineButton;
	QPushButton* backButton;
	QPushButton* saveButton;

	


private slots:

};
