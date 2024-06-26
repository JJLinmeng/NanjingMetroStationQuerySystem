#include "stdafx.h"
#include "UserWindow.h"
#include"MapWindow.h"
#include"Calculator.h"
#include"LoginWindow.h"

UserWindow::UserWindow(QWidget* parent)
{
	this->setWindowTitle("用户界面");
	centralWidget = new QWidget(this);
	mainLayout = new QVBoxLayout;
	sourceLayout = new QHBoxLayout;
	destinationLayout = new QHBoxLayout;
	buttonLayout = new QHBoxLayout;
	sourceLabel = new QLabel("出发地：");
	destinationLabel = new QLabel("目的地：");
	sourceLineEdit = new QLineEdit;
	destinationLineEdit = new QLineEdit;
	sourceLineEdit->setPlaceholderText("请输入出发地");
	sourceLayout->addWidget(sourceLabel);
	sourceLayout->addWidget(sourceLineEdit);
	destinationLineEdit->setPlaceholderText("请输入目的地");
	destinationLayout->addWidget(destinationLabel);
	destinationLayout->addWidget(destinationLineEdit);

	queryButton = new QPushButton("查询");
	exitButton = new QPushButton("退出");
	buttonLayout->addWidget(queryButton);
	buttonLayout->addWidget(exitButton);

	resultLayout = new QHBoxLayout;
	resultListWidget = new QListWidget;
	resultLayout->addWidget(resultListWidget);

	openLayout = new QHBoxLayout;
	openButton = new QPushButton("查询地铁线路图");
	openLayout->addWidget(openButton);


 

	mainLayout->addLayout(sourceLayout);
	mainLayout->addLayout(destinationLayout);
	mainLayout->addLayout(buttonLayout);
	mainLayout->addLayout(resultLayout);
	mainLayout->addLayout(openLayout);
	centralWidget->setLayout(mainLayout);

	centralWidget->setLayout(mainLayout);
	setCentralWidget(centralWidget);

	connect(openButton, &QPushButton::clicked, this, []() {
		MapWindow* mapWindow = new MapWindow;
		mapWindow->show();
	});

	connect(queryButton, &QPushButton::clicked, this, [&]() {
		
		resultListWidget->clear();
		std::string source = (std::string)sourceLineEdit->text().toLocal8Bit();
		std::string destination =(std::string) destinationLineEdit->text().toLocal8Bit();
		if (source.empty() || destination.empty()) {
			resultListWidget->addItem("请输入出发地或目的地");
			return;
		}
		
		auto path = Calculator::findShortestPath(source, destination);
		if (path.empty()) {
			resultListWidget->addItem("未找到路径"); 
			return;
		}
		QList<QString> resultList = Calculator::getShortestPathList(path);
		
	
		for (const QString& result : resultList) {
			resultListWidget->addItem(result);
		}
		(new MapWindow(path))->show();
	});

	connect(exitButton, &QPushButton::clicked, this, [this]() {
			(new LoginWindow())->show();
			this->close();	
		});


}

UserWindow::~UserWindow() noexcept
{
}
