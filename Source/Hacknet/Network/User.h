#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include "UserLevel.h"

class User
{
	std::string name = "Name";
	std::string username = "name";
	std::string password = "password";
	UserLevel level = UserLevel::Guest;
	
public:

	User(const std::string& _name, const std::string& _username, const std::string& _password, UserLevel _level = UserLevel::Guest);

	std::string GetName() const { return name; }
	std::string GetUsername() const { return username; }
	std::string GetPassword() const { return password; }
	UserLevel GetLevel() const { return level; }

	nlohmann::json ToJson() const;
	static User* FromJson(const nlohmann::json& _json);
};
