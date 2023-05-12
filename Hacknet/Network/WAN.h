#pragma once
#include <map>

#include "Node.h"

class WAN
{
	inline static std::map<std::string, Node*> nodes;

public:

	static Node* CreateNode();
	
	static bool GetNode(const std::string& _targetIP, Node** _outNode);

private:
	
	static std::string GetRandomIP();
};
