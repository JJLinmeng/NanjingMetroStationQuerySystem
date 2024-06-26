#pragma once
#include<QMainWindow>
#include <QtWidgets>
#include<vector>
#include"User.h"


class CheckAdminWindow :public QMainWindow {
	Q_OBJECT
public:
	CheckAdminWindow(QWidget* parent = nullptr);
	~CheckAdminWindow() noexcept;
private:
	QVBoxLayout* checkAdminLayout;
	QWidget* centralWidget;
	QListWidget* toBeAdminList;
	QHBoxLayout* buttonLayout;
	QPushButton * agreeButton;
	QPushButton * disagreeButton;
	QPushButton * backButton;
	QPushButton* saveButton;

	std::vector<User> users;
	std::vector<User> addUsers;


private slots:

};
#pragma once
