#pragma once
#include<string>
#include <iostream>
class User {
private:
	std::string username;
	std::string password;
	std::string role;
public:
	User(){}
	User(std::string un, std::string p) :username(un), password(p){}
	friend std::ostream& operator<<(std::ostream& os, const User& user);
	friend std::istream& operator>> (std::istream & is,  User & user);
	friend bool operator==(User& u1,User u2);
	std::string getUsername();
	std::string getPassword();
	std::string getRole();
	void setUsername(std::string name);
	void setPassword(std::string pass);
	void setRole(std::string r);
};