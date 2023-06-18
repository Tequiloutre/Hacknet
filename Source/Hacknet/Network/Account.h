#pragma once
#include <string>
#include <nlohmann/json.hpp>

class Node;

enum AccountType
{
	Guest,
	User,
	Admin
};

class Account
{
	std::string name = "Name";
	std::string username = "name";
	std::string password = "password";
	std::string originNode = "127.0.0.1";
	AccountType type = Guest;
	
public:

	Account(const std::string& _name, const std::string& _username, const std::string& _password, const std::string& _originNode, AccountType _type = Guest);

	std::string GetName() const { return name; }
	std::string GetUsername() const { return username; }
	std::string GetPassword() const { return password; }
	std::string GetOriginNode() const { return originNode; }
	AccountType GetType() const { return type; }

	nlohmann::json ToJson();
	static Account FromJson(const nlohmann::json& _json);
};
