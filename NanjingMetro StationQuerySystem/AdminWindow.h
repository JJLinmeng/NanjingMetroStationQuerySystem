#pragma once
#include<QMainWindow>
#include <QtWidgets>


class AdminWindow :public QMainWindow {
	Q_OBJECT
public:
	AdminWindow(QWidget* parent = nullptr);
	~AdminWindow() noexcept;
private:
	QVBoxLayout* adminLayout;
	QWidget* centralWidget;
	QPushButton * checkAdminButton;
	QPushButton * addStationButton;
	QPushButton* addLineButton;
	QPushButton* deleteStationButton;
	QPushButton* deleteLineButton;
	QPushButton* modifyStationButton;
	QPushButton* modifyLineButton;
	QPushButton* backButton;

private slots:

};

