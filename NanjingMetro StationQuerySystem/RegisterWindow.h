#pragma once
#include<QMainWindow>
#include <QtWidgets>
#include"User.h"



class RegisterWindow :public QMainWindow {
	Q_OBJECT
public:
	RegisterWindow(QWidget* parent = nullptr);
	~RegisterWindow() noexcept;
	
	
private slots:
	void registerAccount();
private:
	QWidget* centralWidget;
	QVBoxLayout* registerLayout;
	QHBoxLayout* usernameLayout;
	QHBoxLayout* passwordLayout;
	QHBoxLayout* confirmPasswordLayout;
	QHBoxLayout* radioButtonLayout;
	QHBoxLayout* buttonLayout;
	QLabel* usernameLabel;
	QLineEdit* usernameText;
	QLabel* passwordLabel;
	QLineEdit* passwordText;
	QLabel* confirmPasswordLabel;
	QLineEdit* confirmPasswordText;
	QRadioButton* userRadioButton;
	QRadioButton* adminRadioButton;
	QPushButton* registerButton;
	QPushButton* backButton;
	QButtonGroup* group;
};
