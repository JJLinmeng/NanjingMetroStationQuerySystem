#include "stdafx.h"
#include "AddLineWindow.h"
#include"StringUtil.h"
#include"AdminWindow.h"


AddLineWindow::AddLineWindow(QWidget* parent)
{
	centralWidget = new QWidget(this);
	AddLineLayout = new QVBoxLayout;
	
	lineNameLayout = new QHBoxLayout;
	lineNameLabel = new QLabel("线路名称：");
	lineNameLineEdit = new QLineEdit();
	lineNameLineEdit->setPlaceholderText("请输入线路名称");
	lineNameLayout->addWidget(lineNameLabel);
	lineNameLayout->addWidget(lineNameLineEdit);
	
	buttonLayout = new QHBoxLayout;
    addLineButton = new QPushButton("添加");
	saveButton = new QPushButton("保存");
	backButton = new QPushButton("返回");

	buttonLayout->addWidget(addLineButton);
	buttonLayout->addWidget(saveButton);
	buttonLayout->addWidget(backButton);

	AddLineLayout->addLayout(lineNameLayout);
	AddLineLayout->addLayout(buttonLayout);
	centralWidget->setLayout(AddLineLayout);
	this->setCentralWidget(centralWidget);


	connect(addLineButton, &QPushButton::clicked, this, [this]() {
		std::string lineName=(std::string)lineNameLineEdit->text().toLocal8Bit();
		if (lineName.empty()) {
			QMessageBox::warning(this, "警告", "请输入线路名称！");
			return;
		}
		if (!StringUtil::starts_with_digit_or_S(lineName)) {
			QMessageBox::warning(this, "警告", "线路名称必须以数字或S开头！");
			return;
		}
		for (auto line : FileReader::lines) {
			if (lineName == line.getName()) {
				QMessageBox::warning(this, "警告", "该线路已存在！");
				return;
			}
		}
		UndergroundLine line;
		line.setName(lineName);
		FileReader::lines.push_back(line);
	});

	connect(saveButton, &QPushButton::clicked, this, [this]() {
		FileReader::save();
		QMessageBox::information(this, "提示", "保存成功！");
		});

	connect(backButton, &QPushButton::clicked, this, [this]() {
		this->close();
		(new AdminWindow())->show();
	});
}

AddLineWindow::~AddLineWindow() noexcept
{
}
