#include "stdafx.h"
#include "AddStationWindow.h"
#include"AdminWindow.h"

AddStationWindow::AddStationWindow(QWidget* parent)
{
	AddStationLayout = new QVBoxLayout;
	centralWidget = new QWidget(this);

	stationNameLayout = new QHBoxLayout;
	stationNameLabel = new QLabel("车站名");
	stationNameLineEdit = new QLineEdit;
	stationNameLayout->addWidget(stationNameLabel);
	stationNameLayout->addWidget(stationNameLineEdit);
	AddStationLayout->addLayout(stationNameLayout);

	stationLongitudeLayout = new QHBoxLayout;
	stationLongitudeLabel = new QLabel("经度");
	stationLongitudeLineEdit = new QLineEdit;
	stationLongitudeLayout->addWidget(stationLongitudeLabel);
	stationLongitudeLayout->addWidget(stationLongitudeLineEdit);
	AddStationLayout->addLayout(stationLongitudeLayout);

	stationLatitudeLayout = new QHBoxLayout;
	stationLatitudeLabel = new QLabel("纬度");
	stationLatitudeLineEdit = new QLineEdit;
	stationLatitudeLayout->addWidget(stationLatitudeLabel);
	stationLatitudeLayout->addWidget(stationLatitudeLineEdit);
	AddStationLayout->addLayout(stationLatitudeLayout);
	
	stationLineLayout = new QHBoxLayout;
	stationLineLabel = new QLabel("所属线路");
	stationLineComboBox = new QComboBox;
	for (int i = 0; i < FileReader::lines.size(); i++) {
		stationLineComboBox->addItem(QString::fromLocal8Bit(FileReader::lines[i].getName().data()));
	}
	stationLineLayout->addWidget(stationLineLabel);
	stationLineLayout->addWidget(stationLineComboBox);
	AddStationLayout->addLayout(stationLineLayout);

	stationadjacentStationOneLayout = new QHBoxLayout;
	stationadjacentStationOneLabel = new QLabel("相邻车站1");
	stationadjacentStationOneLineEdit = new QLineEdit;
	stationadjacentStationOneLayout->addWidget(stationadjacentStationOneLabel);
	stationadjacentStationOneLayout->addWidget(stationadjacentStationOneLineEdit);
	AddStationLayout->addLayout(stationadjacentStationOneLayout);

	stationadjacentStationTwoLayout = new QHBoxLayout;
	stationadjacentStationTwoLabel = new QLabel("相邻车站2");
	stationadjacentStationTwoLineEdit = new QLineEdit;
	stationadjacentStationTwoLayout->addWidget(stationadjacentStationTwoLabel);
	stationadjacentStationTwoLayout->addWidget(stationadjacentStationTwoLineEdit);
	AddStationLayout->addLayout(stationadjacentStationTwoLayout);

	buttonLayout = new QHBoxLayout;


    addStationButton=new QPushButton("添加");
    buttonLayout->addWidget(addStationButton);

	saveButton = new QPushButton("保存");
	buttonLayout->addWidget(saveButton);

	backButton = new QPushButton("返回");
	buttonLayout->addWidget(backButton);
	AddStationLayout->addLayout(buttonLayout);


	centralWidget->setLayout(AddStationLayout);
	this->setCentralWidget(centralWidget);

	connect(addStationButton, &QPushButton::clicked, this, [this]() {
		std::string stationName=(std::string)stationNameLineEdit->text().toLocal8Bit();
		QString stationLongitudeStr = stationLongitudeLineEdit->text();
		QString stationLatitudeStr = stationLatitudeLineEdit->text();
		double stationLongitude=stationLongitudeStr.toDouble();
		double stationLatitude=stationLatitudeStr.toDouble();
		std::string stationLine=(std::string)stationLineComboBox->currentText().toLocal8Bit();
		std::string stationadjacentStationOne=(std::string)stationadjacentStationOneLineEdit->text().toLocal8Bit();
		std::string stationadjacentStationTwo=(std::string)stationadjacentStationTwoLineEdit->text().toLocal8Bit();
		if (stationName.empty() || stationLongitude == 0.0 || stationLatitude == 0.0 || stationLine.empty()) {
			QMessageBox::warning(this, "警告", "请输入完整信息！");
			return;
		}
		FileReader::addStation(stationName, stationLongitude, stationLatitude, stationLine, stationadjacentStationOne, stationadjacentStationTwo);
	});

	connect(saveButton, &QPushButton::clicked, this, [this]() {
		
		
		FileReader::save();
		QMessageBox::information(this, "提示", "保存成功！");
		
	});

	connect(backButton, &QPushButton::clicked, this, [this]() {
		(new AdminWindow())->show();
		this->close();
	});

}

AddStationWindow::~AddStationWindow() noexcept
{
}
