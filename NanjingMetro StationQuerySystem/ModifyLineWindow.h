#pragma once

#include<QMainWindow>
#include <QtWidgets>
#include "FileReader.h"
#include"UndergroundLine.h"
#include"Station.h"
#include"StringUtil.h"


class ModifyLineWindow :public QMainWindow {
	Q_OBJECT
public:
	ModifyLineWindow(QWidget* parent = nullptr);
	~ModifyLineWindow() noexcept;
private:
	QWidget *centralWidget;
	QVBoxLayout *mainLayout;
	QHBoxLayout* oldLineNameLayout;
	QHBoxLayout* newLineNameLayout;
	QHBoxLayout* buttonLayout;

	QLabel *oldLineNameLabel;
	QComboBox *oldLineNameComboBox;
	QLabel *newLineNameLabel;
	QLineEdit *newLineNameLineEdit;
	QPushButton *modifyButton;
	QPushButton* saveButton;
	QPushButton* backButton;



private slots:

};

