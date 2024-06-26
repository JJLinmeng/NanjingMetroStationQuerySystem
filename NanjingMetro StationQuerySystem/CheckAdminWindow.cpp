#include "stdafx.h"
#include "CheckAdminWindow.h"
#include <fstream>
#include"AdminWindow.h"
#include <iostream>

std::vector<User> readToBeAdmin(std::string fileName) {
	std::vector<User> users;
	std::ifstream i;
	i.open(fileName);
	if (i) {
		User user;
		while (i >> user) {
			users.push_back(user);
		}
	}
	i.close();
	return users;
}

CheckAdminWindow::CheckAdminWindow(QWidget* parent)
{
   
	this->setWindowTitle("管理员验证");
	centralWidget = new QWidget(this);
	this->setCentralWidget(centralWidget);
	checkAdminLayout =new QVBoxLayout();
	buttonLayout = new QHBoxLayout();
	centralWidget->setLayout(checkAdminLayout);
	 users = readToBeAdmin("TobeAdmin.txt");
    std::cout << users.size();
	toBeAdminList = new QListWidget;
	for (int i = 0; i < users.size(); i++) {
		toBeAdminList->addItem(QString::fromLocal8Bit(users[i].getUsername().data()));
	}
	agreeButton=new QPushButton("同意");
	disagreeButton = new QPushButton("拒绝");
    backButton=new QPushButton("返回");
	saveButton = new QPushButton("保存");
	buttonLayout->addWidget(agreeButton);
	buttonLayout->addWidget(disagreeButton);
	buttonLayout->addWidget(backButton);
	buttonLayout->addWidget(saveButton);
	checkAdminLayout->addWidget(toBeAdminList);
	checkAdminLayout->addLayout(buttonLayout);

    connect(agreeButton, &QPushButton::clicked, this, [this]() {
       
        QListWidgetItem* currentItem = toBeAdminList->currentItem();
        if (!currentItem) {
            std::cout<< "No item selected!";
            return;
        }
        QString username = currentItem->text();
        std::string str = username.toStdString();
       
      
        delete toBeAdminList->takeItem(toBeAdminList->currentRow());
	   
        User user;
       
        std::cout << users.size();
		for (auto it = users.begin(); it != users.end(); ++it) {
			if (it->getUsername() == str) {
				addUsers.push_back(*it);
				users.erase(it);
				break;
			}
		}
    });

	connect(disagreeButton, &QPushButton::clicked, this, [this]() {
		QListWidgetItem* currentItem = toBeAdminList->currentItem();
		if (!currentItem) {
			std::cout << "No item selected!";
			return;
		}
		QString username = currentItem->text();
		std::string str = username.toStdString();


		delete toBeAdminList->takeItem(toBeAdminList->currentRow());

		User user;
		
		std::cout << users.size();
		for (auto it = users.begin(); it != users.end(); ++it) {
			if (it->getUsername() == str) {
				
				users.erase(it);
				break;
			}
		}
		});

	connect(saveButton, &QPushButton::clicked, this, [this]() {
		std::ofstream o;
		o.open("users.txt", std::ios::app);
		if (o) {
			for (int i = 0; i < addUsers.size(); i++) {
				o << addUsers[i];

			}
		}
		o.close();
		std::ofstream o2;
		o2.open("TobeAdmin.txt");
		if (o2) {
			for (int i = 0; i < users.size(); i++) {
				o2 << users[i];
			}
		}
		QMessageBox::information(this, "提示", "保存成功！");
	});

	connect(backButton, &QPushButton::clicked, this, [this]() {
		(new AdminWindow())->show();
		this->close();
		});

}



CheckAdminWindow::~CheckAdminWindow() noexcept
{

}

