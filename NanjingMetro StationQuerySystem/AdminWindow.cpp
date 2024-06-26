#include "stdafx.h"
#include "AdminWindow.h"
#include"CheckAdminWindow.h"
#include "AddStationWindow.h"
#include "AddLineWindow.h"
#include"DeleteStationWindow.h"
#include"DeleteLineWindow.h"
#include"ModifyStationWindow.h"
#include"ModifyLineWindow.h"
#include"LoginWindow.h"

AdminWindow::AdminWindow(QWidget* parent)
{
	centralWidget = new QWidget(this);
	this->setWindowTitle("管理者界面");
	adminLayout=new QVBoxLayout;
	checkAdminButton=new QPushButton("审核管理员注册");
	addStationButton=new QPushButton("添加站点");
	addLineButton=new QPushButton("添加线路");
	deleteStationButton=new QPushButton("删除站点");
	deleteLineButton=new QPushButton("删除线路");
	modifyStationButton=new QPushButton("修改站点信息");
	modifyLineButton=new QPushButton("修改线路信息");
	backButton=new QPushButton("退出登录");
	
	adminLayout->addWidget(checkAdminButton);
	adminLayout->addWidget(addStationButton);
    adminLayout->addWidget(addLineButton);
	adminLayout->addWidget(deleteStationButton);
	adminLayout->addWidget(deleteLineButton);
	adminLayout->addWidget(modifyStationButton);
	adminLayout->addWidget(modifyLineButton);
	adminLayout->addWidget(backButton);
	centralWidget->setLayout(adminLayout);

	this->setCentralWidget(centralWidget);

	connect(checkAdminButton, &QPushButton::clicked, this, [this]() {
		(new CheckAdminWindow())->show();
		this->close();
	});

	connect(addStationButton, &QPushButton::clicked, this, [this]() {
		(new AddStationWindow())->show();
		this->close();
		});
	connect(addLineButton, &QPushButton::clicked, this, [this]() {
		(new AddLineWindow())->show();
		this->close();
	});

	connect(deleteStationButton, &QPushButton::clicked, this, [this]() {
		(new DeleteStationWindow())->show();
		this->close();
		});

	connect(deleteLineButton, &QPushButton::clicked, this, [this]() {
		(new DeleteLineWindow())->show();
		this->close();
		});

	connect(modifyStationButton, &QPushButton::clicked, this, [this]() {
		(new ModifyStationWindow())->show();
		this->close();
		});
	connect(modifyLineButton, &QPushButton::clicked, this, [this]() {
		(new ModifyLineWindow())->show();
		this->close();
		});
	connect(backButton, &QPushButton::clicked, this, [this]() {
		(new LoginWindow())->show();
		this->close();
		});

}
AdminWindow::~AdminWindow() noexcept
{
}