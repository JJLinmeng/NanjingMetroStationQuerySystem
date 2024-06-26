#pragma once
#include<QMainWindow>
#include <QtWidgets>
#include"User.h"



class LoginWindow :public QMainWindow {
	Q_OBJECT
public:
	LoginWindow(QWidget* parent = nullptr);
	~LoginWindow() noexcept;
	

private slots:
	void login();
	
private:
	QWidget* centralWidget;
	QVBoxLayout* loginLayout;
	QHBoxLayout* usernameLayout;
	QHBoxLayout* passwordLayout;
	QHBoxLayout* buttonLayout;
	QLabel* usernameLabel;
	QLineEdit* usernameText;
	QLabel* passwordLabel;
	QLineEdit* passwordText;
	QPushButton* loginButton;
	QPushButton* registerButton;
	
};
