#pragma once
#include <string>

#include "../FileSystem/Folder.h"

class Node
{
	std::string name = "Node";
	std::string ip = "0.0.0.0";
	Folder* rootFolder = nullptr;

public:

	Node(const std::string& _name, const std::string& _ip);
	~Node();

	std::string GetName() const { return name; }
	std::string GetIP() const { return ip; }
	Folder* GetRoot() const { return rootFolder; }
};
