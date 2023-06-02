#pragma once
#include <string>
#include <nlohmann/json.hpp>

class Node;

class Account
{
	std::string name = "Name";
	std::string username = "name";
	std::string password = "password";
	Node* originNode = nullptr;
	
public:

	Account(const std::string& _name, const std::string& _username, const std::string& _password, Node* _originNode);

	std::string GetName() const { return name; }
	std::string GetUsername() const { return username; }
	std::string GetPassword() const { return password; }
	Node* GetOriginNode() const { return originNode; }

	nlohmann::json ToJson();
	static Account FromJson(const nlohmann::json& _json);
};
