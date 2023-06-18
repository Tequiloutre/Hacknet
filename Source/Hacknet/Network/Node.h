#pragma once
#include <string>

#include "Account.h"
#include "Network/Port.h"
#include "FileSystem/Folder.h"

class Node
{
	std::string name = "Node";
	std::string ip = "0.0.0.0";
	Folder* rootFolder = nullptr;
	std::vector<Port*> ports;
	int requiredPorts = 0;
	std::vector<Account*> accounts;

public:

	Node(const std::string& _name, const std::string& _ip, const std::vector<Port*>& _ports, int _requiredPorts);
	Node(const std::string& _name, const std::string& _ip, Folder* _rootFolder, const std::vector<Port*>& _ports, int _requiredPorts);
	~Node();

	std::string GetName() const { return name; }
	std::string GetIP() const { return ip; }
	Folder* GetRoot() const { return rootFolder; }
	std::vector<Port*> GetPorts() const { return ports; }
	Port* GetPort(int _portNumber) const;
	int GetRequiredPorts() const { return requiredPorts; }
	Account* Login(const std::string& _username, const std::string& _password) const;

	void AddAccount(Account* _account);

	nlohmann::json ToJson();
	static Node FromJson(const nlohmann::json& _json);
};
