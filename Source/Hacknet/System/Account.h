#pragma once

#include <nlohmann/json.hpp>
#include <string>

class Account
{
	std::string name = "Name";
	std::string username = "name";
	std::string password = "password";
	std::string originNode = "127.0.0.1";
	
public:

	Account(const std::string& _name, const std::string& _username, const std::string& _password, const std::string& _originNode);

	std::string GetName() const { return name; }
	std::string GetUsername() const { return username; }
	std::string GetPassword() const { return password; }
	std::string GetOriginNode() const { return originNode; }

	nlohmann::json ToJson() const;
	static Account FromJson(const nlohmann::json& _json);
};
