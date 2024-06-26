#include"stdafx.h"
#include"DeleteStationWindow.h"
#include"AdminWindow.h"
DeleteStationWindow::DeleteStationWindow(QWidget* parent)
{
	centralWidget = new QWidget(parent);
	mainLayout = new QVBoxLayout();
	
	stationNameLayout = new QHBoxLayout();
	stationNameLabel = new QLabel("站台名");
	stationNameComboBox = new QComboBox();
	for (auto station : FileReader::allStations) {
		stationNameComboBox->addItem(QString::fromLocal8Bit(station->getName().data()));
	}
	stationNameLayout->addWidget(stationNameLabel);
	stationNameLayout->addWidget(stationNameComboBox);

	lineNameLayout = new QHBoxLayout();
	lineNameLabel = new QLabel("线路名");
	lineNameComboBox = new QComboBox();
	for (auto station : FileReader::allStations) {
		if (QString::fromLocal8Bit(station->getName().data()) == stationNameComboBox->currentText()) {
			for (auto line : station->getUndergroundLines()) {
				lineNameComboBox->addItem(QString::fromLocal8Bit(line.getName().data()));
			}
		}
	}
	
	lineNameComboBox->addItem("全部");
	lineNameLayout->addWidget(lineNameLabel);
	lineNameLayout->addWidget(lineNameComboBox);

	buttonLayout = new QHBoxLayout();
	deleteButton = new QPushButton("删除");
	saveButton = new QPushButton("保存");
	backButton = new QPushButton("返回");
	buttonLayout->addWidget(deleteButton);
	buttonLayout->addWidget(saveButton);
	buttonLayout->addWidget(backButton);

	mainLayout->addLayout(stationNameLayout);
	mainLayout->addLayout(lineNameLayout);
	mainLayout->addLayout(buttonLayout);

	centralWidget->setLayout(mainLayout);


	this->setCentralWidget(centralWidget);


	connect(stationNameComboBox, &QComboBox::currentIndexChanged, this, [this]() {
		lineNameComboBox->clear();
		for (auto station : FileReader::allStations) {
			if (QString::fromLocal8Bit(station->getName().data()) == stationNameComboBox->currentText()) {
				for (auto line : station->getUndergroundLines()) {
					lineNameComboBox->addItem(QString::fromLocal8Bit(line.getName().data()));
				}
			}
		}
		lineNameComboBox->addItem("全部");
	});

	connect(deleteButton, &QPushButton::clicked, this, [this]() {
		
	 
		FileReader::deleteStation((std::string)(stationNameComboBox->currentText().toLocal8Bit()), (std::string)(lineNameComboBox->currentText().toLocal8Bit()));
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

DeleteStationWindow::~DeleteStationWindow() noexcept
{
}
