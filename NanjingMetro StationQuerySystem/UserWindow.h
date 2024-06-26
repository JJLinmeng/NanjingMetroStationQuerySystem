#pragma once
#include<QMainWindow>
#include <QtWidgets>


class UserWindow :public QMainWindow {
	Q_OBJECT
public:
	UserWindow(QWidget* parent = nullptr);
	~UserWindow() noexcept;


private slots:

private:
	QVBoxLayout* mainLayout;
	QHBoxLayout* sourceLayout;
	QHBoxLayout* destinationLayout;
	QHBoxLayout* buttonLayout;
	QHBoxLayout* resultLayout;
	QHBoxLayout* openLayout;


	QWidget* centralWidget;
	QLabel *sourceLabel;
    QLabel *destinationLabel;
	

	QLineEdit *sourceLineEdit;
	QLineEdit *destinationLineEdit;
	QPushButton *queryButton;
	QPushButton *exitButton;
	QPushButton *openButton;
	QListWidget *resultListWidget;



};
