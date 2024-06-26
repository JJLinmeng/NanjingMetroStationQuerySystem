#include "stdafx.h"
#include"User.h"

std::ostream& operator<<(std::ostream& os, const User& user)
{
	os << user.username << " " << user.password <<" " << user.role << "\n";
	return os;
}

std::istream& operator>>(std::istream& is,  User& user)
{
	is >> user.username >> user.password>>user.role;
	return is;
}

bool operator==(User& u1, User u2)
{
	return u1.username == u2.username;
}

std::string User::getUsername()
{
	return username;
}

std::string User::getPassword()
{
	return password;
}

std::string User::getRole()
{
	return role;
}

void  User::setUsername(std::string name)
{
	username = name;
}


void  User::setPassword(std::string pass)
{
	password = pass;
}

void  User::setRole(std::string r)
{
	role = r;
}




