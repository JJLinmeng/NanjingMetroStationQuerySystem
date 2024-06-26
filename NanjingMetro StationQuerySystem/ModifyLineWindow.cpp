#include "stdafx.h"
#include "ModifyLineWindow.h"
#include"AdminWindow.h"

ModifyLineWindow::ModifyLineWindow(QWidget* parent)
{
	centralWidget = new QWidget(this);
	mainLayout = new QVBoxLayout(centralWidget);
	oldLineNameLayout = new QHBoxLayout();
	oldLineNameLabel = new QLabel("线路名");
	oldLineNameComboBox = new QComboBox();
	for (auto line : FileReader::lines) {
		oldLineNameComboBox->addItem(QString::fromLocal8Bit(line.getName().data()));
	}
	oldLineNameLayout->addWidget(oldLineNameLabel);
	oldLineNameLayout->addWidget(oldLineNameComboBox);
	newLineNameLayout = new QHBoxLayout();
	newLineNameLabel = new QLabel("新线路名");
	newLineNameLineEdit = new QLineEdit();
	newLineNameLayout->addWidget(newLineNameLabel);
	newLineNameLayout->addWidget(newLineNameLineEdit);
	mainLayout->addLayout(oldLineNameLayout);
	mainLayout->addLayout(newLineNameLayout);
	buttonLayout = new QHBoxLayout();
	modifyButton = new QPushButton("修改");
	saveButton = new QPushButton("保存");
	backButton = new QPushButton("返回");
	buttonLayout->addWidget(modifyButton);
	buttonLayout->addWidget(saveButton);
	buttonLayout->addWidget(backButton);
	mainLayout->addLayout(oldLineNameLayout);
	mainLayout->addLayout(newLineNameLayout);
	mainLayout->addLayout(buttonLayout);
	centralWidget->setLayout(mainLayout);
	this->setCentralWidget(centralWidget);

	connect(modifyButton, &QPushButton::clicked, this, [this]() {
		for (auto line : FileReader::lines) {
			if (newLineNameLineEdit->text() == QString::fromLocal8Bit(line.getName().data())) {
				QMessageBox::warning(this, "警告", "该线路名已存在");
				return;
			}
		}
		if (!StringUtil::starts_with_digit_or_S((std::string)newLineNameLineEdit->text().toLocal8Bit())) {
			QMessageBox::warning(this, "警告", "线路名格式不正确");
			return;
		}
		for (auto it = FileReader::lines.begin(); it != FileReader::lines.end(); ++it) {
			if (oldLineNameComboBox->currentText() == QString::fromLocal8Bit(it->getName().data())) {
				std::cout << "123";
				std::cout << (std::string)newLineNameLineEdit->text().toLocal8Bit();
				it->setName((std::string)newLineNameLineEdit->text().toLocal8Bit());
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

ModifyLineWindow::~ModifyLineWindow() noexcept
{
}
