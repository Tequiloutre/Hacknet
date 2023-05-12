#pragma once
#include <string>

class Node
{
	std::string name = "Node";
	std::string ip = "0.0.0.0";

public:

	Node(const std::string& _name, const std::string& _ip)
	{
		name = _name;
		ip = _ip;
	}

	std::string GetName() const { return name; }
	std::string GetIP() const { return ip; }
};
