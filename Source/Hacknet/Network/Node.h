#pragma once

#include "Network/UserLevel.h"
#include "nlohmann/json.hpp"
#include <string>
#include <vector>

class Folder;
class Port;
class User;

class Node
{
	std::string name = "Node";
	std::string ip = "0.0.0.0";
	std::vector<User*> users;
	Folder* rootFolder = nullptr;
	std::vector<Port*> ports;
	int requiredPorts = 0;

public:

	Node(const std::string& _name, const std::string& _ip, const std::vector<Port*>& _ports, int _requiredPorts);
	Node(const std::string& _name, const std::string& _ip, Folder* _rootFolder, const std::vector<Port*>& _ports, int _requiredPorts);
	Node(const std::string& _name, const std::string& _ip, const std::vector<User*>& _users, const std::vector<Port*>& _ports, int _requiredPorts);
	Node(const std::string& _name, const std::string& _ip, const std::vector<User*>& _users, Folder* _rootFolder, const std::vector<Port*>& _ports, int _requiredPorts);
	~Node();

	std::string GetName() const { return name; }
	std::string GetIP() const { return ip; }
	Folder* GetRoot() const { return rootFolder; }
	std::vector<Port*> GetPorts() const { return ports; }
	Port* GetPort(int _portNumber) const;
	int GetRequiredPorts() const { return requiredPorts; }

	void AddUser(User* _user);
	User* Login(const std::string& _username, const std::string& _password) const;
	UserLevel GetUserLevel(const std::string& _username) const;

	nlohmann::json ToJson();
	static Node* FromJson(const nlohmann::json& _json);
};
