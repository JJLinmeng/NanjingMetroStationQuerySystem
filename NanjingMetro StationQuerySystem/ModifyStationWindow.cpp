#include "stdafx.h"
#include "ModifyStationWindow.h"
#include"AdminWindow.h"

ModifyStationWindow::ModifyStationWindow(QWidget* parent)
{
	centralWidget = new QWidget();
	mainLayout = new QVBoxLayout();
	
	stationNameLayout = new QHBoxLayout();
	stationNameLabel = new QLabel("站点名");
	stationNameComboBox = new QComboBox();

	for (auto station : FileReader::allStations) {
		stationNameComboBox->addItem(QString::fromLocal8Bit(station->getName()));
	}
	stationNameLayout->addWidget(stationNameLabel);
	stationNameLayout->addWidget(stationNameComboBox);

	searchButton = new QPushButton("查询");
	mainLayout->addWidget(searchButton);

	mainLayout->addLayout(stationNameLayout);
	centralWidget->setLayout(mainLayout);
	buttonLayout = new QHBoxLayout();
	modifyButton = new QPushButton("修改");
	saveButton = new QPushButton("保存");
	backButton = new QPushButton("返回");
	newStationNameLayout = new QHBoxLayout();
	newStationNameLabel = new QLabel("站点名");
	newStationNameLineEdit = new QLineEdit();
	newStationLongitudeLayout = new QHBoxLayout();
	newStationLongitudeLabel = new QLabel("站点经度");
	newStationLongitudeLineEdit = new QLineEdit();

	newStationLatitudeLayout = new QHBoxLayout();
	newStationLatitudeLabel = new QLabel("站点纬度");
	newStationLatitudeLineEdit = new QLineEdit();

	this->setCentralWidget(centralWidget);

	connect(searchButton, &QPushButton::clicked, this, [this]() {
		std::shared_ptr<Station> currentStation;
		for (auto station : FileReader::allStations) {
			if (stationNameComboBox->currentText() == QString::fromLocal8Bit(station->getName())) {
				currentStation = station;
			}
		}

		newStationNameLineEdit->setText(QString::fromLocal8Bit(currentStation->getName()));
		newStationNameLayout->addWidget(newStationNameLabel);
		newStationNameLayout->addWidget(newStationNameLineEdit);


		newStationLongitudeLineEdit->setText(QString::number(currentStation->getLongitude()));
		newStationLongitudeLayout->addWidget(newStationLongitudeLabel);
		newStationLongitudeLayout->addWidget(newStationLongitudeLineEdit);

		newStationLatitudeLineEdit->setText(QString::number(currentStation->getLatitude()));
		newStationLatitudeLayout->addWidget(newStationLatitudeLabel);
		newStationLatitudeLayout->addWidget(newStationLatitudeLineEdit);

		
		buttonLayout->addWidget(modifyButton);
		buttonLayout->addWidget(saveButton);
		buttonLayout->addWidget(backButton);
		mainLayout->addLayout(newStationNameLayout);
		mainLayout->addLayout(newStationLongitudeLayout);
		mainLayout->addLayout(newStationLatitudeLayout);
		mainLayout->addLayout(buttonLayout);

	});

	connect(modifyButton, &QPushButton::clicked, this, [this]() {
	
		auto stations=FileReader::allStations;
		if (newStationNameLineEdit->text().isEmpty()|| newStationLongitudeLineEdit->text().isEmpty() || newStationLatitudeLineEdit->text().isEmpty()) {
			QMessageBox::warning(this, "警告", "站点信息不能为空");
			return;
		}

		for (auto it =stations.begin(); it != stations.end(); ++it) {
			if (stationNameComboBox->currentText() == QString::fromLocal8Bit((*it)->getName())) {

				(*it)->setName((std::string)newStationNameLineEdit->text().toLocal8Bit());
				(*it)->setLongitude(newStationLongitudeLineEdit->text().toDouble());
				(*it)->setLatitude(newStationLatitudeLineEdit->text().toDouble());
			}
		}
		

		auto lines = FileReader::lines;

		for (auto lineIt =lines.begin(); lineIt != lines.end(); ++lineIt) {
			auto stations = lineIt->getStations();
			for (auto stationIt = stations.begin(); stationIt != stations.end(); ++stationIt) {
				if ((*stationIt)->getName() == (std::string)stationNameComboBox->currentText().toLocal8Bit()) {
					(*stationIt)->setName((std::string)newStationNameLineEdit->text().toLocal8Bit());
					(*stationIt)->setLongitude(newStationLongitudeLineEdit->text().toDouble());
					(*stationIt)->setLatitude(newStationLatitudeLineEdit->text().toDouble());
				}
			}
			
		}
		
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

ModifyStationWindow::~ModifyStationWindow() noexcept
{

}
