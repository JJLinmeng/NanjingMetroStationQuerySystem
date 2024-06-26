#include "stdafx.h"
#include"RegisterWindow.h"
#include<fstream>
#include"LoginWindow.h"

RegisterWindow::RegisterWindow(QWidget* parent) : QMainWindow(parent) {
    centralWidget = new QWidget(this);
    this->setWindowTitle("注册");
   
     registerLayout = new QVBoxLayout;
     usernameLayout = new QHBoxLayout;
     passwordLayout = new QHBoxLayout;
     confirmPasswordLayout = new QHBoxLayout;
     radioButtonLayout = new QHBoxLayout;
     buttonLayout = new QHBoxLayout;

    //用户名
    usernameLabel = new QLabel("用户名");
    usernameLabel->setFixedWidth(80);
    usernameLabel->setAlignment(Qt::AlignLeft);

    usernameText = new QLineEdit();

    usernameLayout->addWidget(usernameLabel);
    usernameLayout->addWidget(usernameText);

    //密码
     passwordLabel = new QLabel("密码");
    passwordLabel->setFixedWidth(80);
    passwordLabel->setAlignment(Qt::AlignLeft);

    passwordText = new QLineEdit();
    passwordText->setEchoMode(QLineEdit::Password);

    passwordLayout->addWidget(passwordLabel);
    passwordLayout->addWidget(passwordText);

    //确认密码
    confirmPasswordLabel = new QLabel("确认密码");
    confirmPasswordLabel->setFixedWidth(80);
    confirmPasswordLabel->setAlignment(Qt::AlignLeft);

    confirmPasswordText = new QLineEdit();
    confirmPasswordText->setEchoMode(QLineEdit::Password);

    confirmPasswordLayout->addWidget(confirmPasswordLabel);
    confirmPasswordLayout->addWidget(confirmPasswordText);

    //角色
    userRadioButton = new QRadioButton("普通用户");
    adminRadioButton = new QRadioButton("管理员");
    group = new QButtonGroup();
    group->addButton(userRadioButton);
    group->addButton(adminRadioButton);

    radioButtonLayout->addWidget(userRadioButton);
    radioButtonLayout->addWidget(adminRadioButton);
    
    //按钮
    registerButton = new QPushButton("注册");
    backButton = new QPushButton("返回");
   
    buttonLayout->addWidget(registerButton);
    buttonLayout->addWidget(backButton);

    connect(registerButton, &QPushButton::clicked, this, &RegisterWindow::registerAccount);


    //将水平布局加入垂直布局
    registerLayout->addLayout(usernameLayout);
    registerLayout->addLayout(passwordLayout);
    registerLayout->addLayout(confirmPasswordLayout);
    registerLayout->addLayout(radioButtonLayout);
    registerLayout->addLayout(buttonLayout);

    centralWidget->setLayout(registerLayout); //中心窗口设置布局


    connect(backButton, &QPushButton::clicked, this, [this]() {
        (new LoginWindow())->show();
        this->close();
        });

    this->setCentralWidget(centralWidget); //给主窗口设置中心窗口
}

RegisterWindow::~RegisterWindow() noexcept{
}


void RegisterWindow::registerAccount() {

    std::string username = usernameText->text().toStdString();
    std::string password = passwordText->text().toStdString();
    std::string confirmPassword = confirmPasswordText->text().toStdString();
    if (username.empty() || password.empty() || confirmPassword.empty()|| group->checkedId() == -1) {
        QMessageBox::information(this, "提示", "用户名,密码,角色不能为空");
        return;
    }
    if (password != confirmPassword) {
        QMessageBox::information(this, "提示", "两次密码不一致,请重新输入");
        return;
    }
    User user(username, password);
    //std::vector<User> userList;
    std::ifstream i;
    i.open("users.txt");
    if (i) {
        User user_read;
        while (i >> user_read) {
            if (user == user_read) {
                QMessageBox::information(this, "提示", "已存在该用户");
                i.close();
                return;
            }
        }
    }
    i.close();
    std::ofstream o;
    if (group->checkedButton()->text() == "普通用户") {
        o.open("users.txt", std::ios::app);
        user.setRole("2");
        if (o) {
            o << user;
            QMessageBox::information(this, "提示", QString("尊敬的%1您好,恭喜您成功注册").arg(usernameText->text()));
        }
        o.close();
    }
    else {
        o.open("TobeAdmin.txt", std::ios::app);
        user.setRole("1");
        if (o) {
            o << user;
            QMessageBox::information(this, "提示", QString("尊敬的%1您好,已为你提交注册申请,等待管理员审核").arg(usernameText->text()));
        }
        o.close();
    }
}
