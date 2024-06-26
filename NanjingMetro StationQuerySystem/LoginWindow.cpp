#include "stdafx.h"
#include "LoginWindow.h"
#include"RegisterWindow.h"
#include"UserWindow.h"
#include"AdminWindow.h"
#include<fstream>

LoginWindow::LoginWindow(QWidget* parent)
{
	centralWidget = new QWidget(this);
	
    this->setWindowTitle("登录");
	loginLayout = new QVBoxLayout;
	usernameLayout = new QHBoxLayout;
	passwordLayout = new QHBoxLayout;
	buttonLayout = new QHBoxLayout;

    //用户名
    usernameLabel = new QLabel("用户名");
    usernameLabel->setFixedWidth(50);
    usernameLabel->setAlignment(Qt::AlignLeft);

    usernameText = new QLineEdit();

    usernameLayout->addWidget(usernameLabel);
    usernameLayout->addWidget(usernameText);

    //密码
    passwordLabel = new QLabel("密码");
    passwordLabel->setFixedWidth(50);
    passwordLabel->setAlignment(Qt::AlignLeft);

    passwordText = new QLineEdit();
    passwordText->setEchoMode(QLineEdit::Password);

    passwordLayout->addWidget(passwordLabel);
    passwordLayout->addWidget(passwordText);

    //按钮
    loginButton = new QPushButton("登录");
    registerButton = new QPushButton("立即注册");

    connect(registerButton, &QPushButton::clicked, this, [this]() {
        (new RegisterWindow())->show();
        this->close();
        });
    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::login);

    buttonLayout->addWidget(loginButton);
    buttonLayout->addWidget(registerButton);

    loginLayout->addLayout(usernameLayout);
    loginLayout->addLayout(passwordLayout);
    loginLayout->addLayout(buttonLayout);

    centralWidget->setLayout(loginLayout); //中心窗口设置布局
    this->setCentralWidget(centralWidget); //给主窗口设置中心窗口

}

void LoginWindow::login() {
    std::string username = usernameText->text().toStdString();
    std::string password = passwordText->text().toStdString();
    std::ifstream i;
    i.open("users.txt");
    if (i) {
        User user;
        while (i >> user) {
           /* qDebug() << user.getUsername() << user.getPassword();*/
            if (username == user.getUsername() && password == user.getPassword()) {
                i.close();
                if (user.getRole() == "2") {
                    (new UserWindow())->show();
                    this->close();
                    return;
                }
                else if (user.getRole() == "1") {
                    (new AdminWindow())->show();
                    this->close();
                    return;
                }
                
            }
        }
        QMessageBox::information(this, "提示", "账号或密码错误!");
        i.close();
    }
}


LoginWindow::~LoginWindow() noexcept
{
}
