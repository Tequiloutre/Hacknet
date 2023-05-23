#pragma once
#include <string>

#include "Port.h"
#include "../FileSystem/Folder.h"

class Node
{
	std::string name = "Node";
	std::string ip = "0.0.0.0";
	Folder* rootFolder = nullptr;
	std::vector<Port*> ports;
	int requiredPorts = 0;

public:

	Node(const std::string& _name, const std::string& _ip, const std::vector<Port*>& _ports, int _requiredPorts);
	~Node();

	std::string GetName() const { return name; }
	std::string GetIP() const { return ip; }
	Folder* GetRoot() const { return rootFolder; }
	std::vector<Port*> GetPorts() const { return ports; }
	int GetRequiredPorts() const { return requiredPorts; }
};
