#include "stdafx.h"
#include "DeleteLineWindow.h"
#include"AdminWindow.h"


DeleteLineWindow::DeleteLineWindow(QWidget* parent)
{
	centralWidget = new QWidget(this);
	mainLayout = new QVBoxLayout();
	centralWidget->setLayout(mainLayout);
	lineNameLayout = new QHBoxLayout();
	lineNameLabel = new QLabel("请输入要删除的线路名称：", centralWidget);
	lineNameComboBox = new QComboBox();
	for (auto line : FileReader::lines) {
		lineNameComboBox->addItem(QString::fromLocal8Bit(line.getName().data()));
	}
	lineNameLayout->addWidget(lineNameLabel);
	lineNameLayout->addWidget(lineNameComboBox);

	buttonLayout = new QHBoxLayout();
	deleteButton = new QPushButton("删除", centralWidget);
	saveButton = new QPushButton("保存", centralWidget);
	backButton = new QPushButton("返回", centralWidget);
	buttonLayout->addWidget(deleteButton);
	buttonLayout->addWidget(saveButton);
	buttonLayout->addWidget(backButton);



	mainLayout->addLayout(lineNameLayout);
	mainLayout->addLayout(buttonLayout);
	this->setCentralWidget(centralWidget);

	connect(deleteButton, &QPushButton::clicked, this, [this]() {
		FileReader::deleteLine((std::string)(this->lineNameComboBox->currentText().toLocal8Bit()));
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

DeleteLineWindow::~DeleteLineWindow() noexcept
{
}
